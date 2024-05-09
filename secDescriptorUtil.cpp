#include <iostream>
#include <windows.h>
#include "securityDescriptors.hpp"
using namespace std;

void getInfo()
{
    wstring path;
    wstring backupPath;

    // Prompt the user to enter the path and backup path
    cout << "Enter the file path: ";
    getline(wcin, path);
    cout << "Enter the backup file path: ";
    getline(wcin, backupPath);

    // Prompt the user to select an option
    cout << "Select an option:\n";
    cout << "1. Backup file permissions\n";
    cout << "2. Restore file permissions from backup\n";
    int option;
    cin >> option;

    bool success = false;

    switch (option)
    {
    case 1:
    {
        // Backup file permissions
        if (cloneSecurityDescriptor(path.c_str(), backupPath.c_str()))
        {
            wcout << L"Permissions backup created successfully.\n";
        }
        else
        {
            wcout << L"Error creating permissions backup.\n";
        }
        break;
    }
    case 2:
    {
        // Restore Security Descriptor from backup file
        if (restoreSecurityDescriptor(backupPath.c_str(), path.c_str()))
        {
            wcout << L"File permissions restored from backup successfully.\n";
        }
        else
        {
            wcout << L"Error restoring file permissions from backup.\n";
        }
        break;
    }
    default:
        cout << "Invalid option selected.\n";
    }
}