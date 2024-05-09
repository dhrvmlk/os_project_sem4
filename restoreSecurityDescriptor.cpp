#include <iostream>
#include <string>
#include <windows.h>
#include "securityDescriptors.hpp"
using namespace std;

bool restoreSecurityDescriptor(const wchar_t *filePath, const wchar_t *restorePath)
{
    HANDLE hFile = CreateFileW(restorePath, GENERIC_WRITE, FILE_SHARE_WRITE,
                               NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        wcout << L"Failed to open file: " << restorePath << L"\n";
        return false;
    }

    HANDLE hBackup = CreateFileW(filePath, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                                 FILE_ATTRIBUTE_NORMAL, NULL);
    if (hBackup == INVALID_HANDLE_VALUE)
    {
        wcout << L"Failed to open backup file: " << filePath << L"\n";
        CloseHandle(hFile);
        return false;
    }

    DWORD dwLength = GetFileSize(hBackup, NULL);
    if (dwLength == INVALID_FILE_SIZE)
    {
        wcout << L"Failed to retrieve backup file size.\n";
        CloseHandle(hBackup);
        CloseHandle(hFile);
        return false;
    }

    PSECURITY_DESCRIPTOR pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, dwLength);
    if (!pSD)
    {
        wcout << L"Failed to allocate memory for security descriptor.\n";
        CloseHandle(hBackup);
        CloseHandle(hFile);
        return false;
    }

    DWORD bytesRead = 0;
    BOOL bResult = ReadFile(hBackup, pSD, dwLength, &bytesRead, NULL);
    if (!bResult || bytesRead != dwLength)
    {
        wcout << L"Failed to read security descriptor from backup file.\n";
        LocalFree(pSD);
        CloseHandle(hBackup);
        CloseHandle(hFile);
        return false;
    }

    bResult = SetFileSecurityW(restorePath,
                               DACL_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION,
                               pSD);
    if (!bResult)
    {
        wcout << L"Failed to restore file security.\n";
        LocalFree(pSD);
        CloseHandle(hBackup);
        CloseHandle(hFile);
        return false;
    }

    LocalFree(pSD);
    CloseHandle(hBackup);
    CloseHandle(hFile);
    return true;
}