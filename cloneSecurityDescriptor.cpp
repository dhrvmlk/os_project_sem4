#include <iostream>
#include <windows.h>
#include <string>
#include "securityDescriptors.hpp"
using namespace std;

bool cloneSecurityDescriptor(const wchar_t *filePath, const wchar_t *clonePath)
{
    SECURITY_INFORMATION secInfo = OWNER_SECURITY_INFORMATION |
                                   GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;

    HANDLE hFile = CreateFileW(filePath, READ_CONTROL, FILE_SHARE_READ, NULL,
                               OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        wcout << L"Failed to open the file: " << filePath << L"\n";
        return false;
    }

    PSECURITY_DESCRIPTOR pSD = NULL;
    DWORD dwLength = 0;
    BOOL bResult = GetFileSecurityW(filePath, secInfo, NULL, 0, &dwLength);
    if (!bResult && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
        pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, dwLength);
        if (!pSD)
        {
            wcout << L"Failed to allocate memory for security descriptor.\n";
            CloseHandle(hFile);
            return false;
        }
        bResult = GetFileSecurityW(filePath, secInfo, pSD, dwLength, &dwLength);
        if (!bResult)
        {
            wcout << L"Failed to retrieve file security information.\n";
            LocalFree(pSD);
            CloseHandle(hFile);
            return false;
        }
    }
    else
    {
        wcout << L"Failed to retrieve required buffer size for security descriptor.\n";
        CloseHandle(hFile);
        return false;
    }

    HANDLE hBackup = CreateFileW(clonePath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                                 FILE_ATTRIBUTE_NORMAL, NULL);

    if (hBackup == INVALID_HANDLE_VALUE)
    {
        wcout << L"Failed to create backup file: " << clonePath << L"\n";
        LocalFree(pSD);
        CloseHandle(hFile);
        return false;
    }

    DWORD bytesWritten = 0;
    bResult = WriteFile(hBackup, pSD, dwLength, &bytesWritten, NULL);
    if (!bResult || bytesWritten != dwLength)
    {
        wcout << L"Failed to write security descriptor to backup file.\n";
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
