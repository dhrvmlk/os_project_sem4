#include <iostream>
#include <string>
#include <stdexcept>
#include <Windows.h>
#include "acl.hpp"
#include "securityDescriptors.hpp"
using namespace std;
// #include <cstdio>

int main()
{
    ACL_impl acl;

    do
    {
        try
        {
            cout << "\n*****MENU*****\n";
            cout << "1) Manage File Permissions\n";
            cout << "2) Read ACL\n";
            cout << "3) Grant Permission\n";
            cout << "4) Remove Permission\n";
            cout << "5) Deny Permission\n";
            cout << "6) Reset Permissions\n";
            cout << "7) DisableInheritance\n";
            cout << "8) Exit\n";

            // Get user's choice
            int choice;
            cout << "\nEnter your choice here: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                getInfo();
                break;
            }
            case 2:
            {
                acl.ReadACL();
                break;
            }
            case 3:
            {
                acl.GrantPermission();
                break;
            }
            case 4:
            {
                acl.RemovePermission();
                break;
            }
            case 5:
            {
                acl.DenyPermission();
                break;
            }
            case 6:
            {
                acl.ResetPermissions();
                break;
            }
            case 7:
            {
                acl.DisableInheritance();
                break;
            }
            case 8:
            {
                cout << "\nExiting the program...\n\n";
                return 0;
            }
            default:
                // Throw an exception if the user enters an invalid choice
                throw invalid_argument("Invalid choice entered");
            }
        }
        catch (const exception &e)
        {
            // Print error message to console
            cerr << e.what() << endl;
        }
    } while (1);

    return 0;
}
