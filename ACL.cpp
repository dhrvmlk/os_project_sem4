#include <iostream>
#include <string>
#include "acl.hpp"

// Function to read ACL
std::string ACL::ReadACL()
{
    // Get file path from user
    std::cout << "Enter the file path: ";
    std::cin.ignore();
    std::getline(std::cin, filename);

    // Construct command for icacls and execute it using popen
    std::string command = "icacls \"" + filename + "\"";
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        // Throw an exception if command execution fails
        throw std::runtime_error("Error executing icacls command");
    }

    // Read command output into result string
    std::string result = "";
    while (fgets(buffer, 128, pipe))
    {
        result += buffer;
    }

    // Close pipe and check the status
    int status = pclose(pipe);
    if (status != 0)
    {
        // Throw an exception if command execution fails
        throw std::runtime_error("icacls command failed with error code " + std::to_string(status));
    }

    // Print result and return the command
    std::cout << result << std::endl;
    return command;
}

// Function to grant permission
void ACL::GrantPermission()
{
    // Get file/folder path, username, and permission type from user
    std::cout << "Enter the file or folder path: ";
    std::cin.ignore();
    std::getline(std::cin, filename);

    std::cout << "Enter the username to grant permission: ";
    std::getline(std::cin, username);

    std::cout << "Enter the permission to grant (F, M, RX): ";
    std::getline(std::cin, permission);

    // Construct command for icacls and execute it using popen
    std::string command = "icacls \"" + filename + "\" /grant \"" + username + "\":" + permission;
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        // Throw an exception if command execution fails
        throw std::runtime_error("Error executing icacls command");
    }

    // Read command output and print it to console
    while (fgets(buffer, 128, pipe))
    {
        std::cout << buffer;
    }

    // Close the pipe and check the status
    int result = pclose(pipe);
    if (result != 0)
    {
        // Throw an exception if command execution fails
        throw std::runtime_error("icacls command failed with error code " + std::to_string(result));
    }

    // Print success message
    std::cout << "Permission granted successfully!" << std::endl;
}

// Function to remove permission
void ACL::RemovePermission()
{
    // Get file/folder path, username, and permission type from user
    std::cout << "Enter the file or folder path: ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    std::cout << "Enter the username to remove permission: ";
    std::getline(std::cin, username);

    std::cout << "Enter the permission to remove (F, M, RX): ";
    std::getline(std::cin, permission);

    // Construct command for icacls and execute it using popen
    std::string command = "icacls \"" + filename + "\" /remove \"" + username + "\":" + permission;
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        // Throw an exception if command execution fails
        throw std::runtime_error("Error executing icacls command");
    }

    // Read command output and print it to console
    while (fgets(buffer, 128, pipe))
    {
        std::cout << buffer;
    }

    // Close the pipe and check the status
    int result = pclose(pipe);
    if (result != 0)
    {
        // Throw an exception if command execution fails
        throw std::runtime_error("icacls command failed with error code " + std::to_string(result));
    }

    // Print success message
    std::cout << "Permission removed successfully!" << std::endl;
}

// Function to deny permission
void ACL::DenyPermission()
{
    // Get file/folder path, username, and permission type from user
    std::cout << "Enter the file or folder path: ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    std::cout << "Enter the username to deny permission: ";
    std::getline(std::cin, username);

    std::cout << "Enter the permission to deny (F, M, RX): ";
    std::getline(std::cin, permission);

    // Construct command for icacls and execute it using popen
    std::string command = "icacls \"" + filename + "\" /deny \"" + username + "\":" + permission;
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        // Throw an exception if command execution fails
        throw std::runtime_error("Error executing icacls command");
    }

    // Read command output and print it to console
    while (fgets(buffer, 128, pipe))
    {
        std::cout << buffer;
    }

    // Close the pipe and check the status
    int result = pclose(pipe);
    if (result != 0)
    {
        // Throw an exception if command execution fails
        throw std::runtime_error("icacls command failed with error code " + std::to_string(result));
    }

    // Print success message
    std::cout << "Permission denied successfully!" << std::endl;
}

// Function to reset permissions to default
void ACL::ResetPermissions()
{
    // Get file/folder path from user
    std::cout << "Enter the file or folder path: ";
    std::cin.ignore();
    std::getline(std::cin, filename);
    // Construct command for icacls and execute it using popen
    std::string command = "icacls \"" + filename + "\" /reset";
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        // Throw an exception if command execution fails
        throw std::runtime_error("Error executing icacls command");
    }

    // Read command output and print it to console
    while (fgets(buffer, 128, pipe))
    {
        std::cout << buffer;
    }

    // Close the pipe and check the status
    int result = pclose(pipe);
    if (result != 0)
    {
        // Throw an exception if command execution fails
        throw std::runtime_error("icacls command failed with error code " + std::to_string(result));
    }

    // Print success message
    std::cout << "Permissions reset successfully!" << std::endl;
}

void ACL::DisableInheritance()
{
    // Get file/folder path from user
    std::cout << "Enter the file or folder path: ";
    std::string path;
    std::getline(std::cin >> std::ws, path);

    // Construct command to check inheritance status and execute it using popen
    std::string checkCommand = "icacls \"" + path + "\"";
    FILE *checkPipe = popen(checkCommand.c_str(), "r");
    if (!checkPipe)
    {
        throw std::runtime_error("Error executing icacls command");
    }

    // Read command output and check if inheritance is enabled or disabled
    std::string checkOutput;
    char checkBuffer[128];
    while (fgets(checkBuffer, 128, checkPipe))
    {
        checkOutput += checkBuffer;
    }
    bool inheritanceEnabled = checkOutput.find("(OI)(CI)(IO)") != std::string::npos;

    // Close the check pipe and check the status
    int checkResult = pclose(checkPipe);
    if (checkResult != 0)
    {
        throw std::runtime_error("icacls command failed with error code " + std::to_string(checkResult));
    }

    // Display current inheritance status and prompt user to enable or disable it
    std::cout << "Current inheritance status: " << (inheritanceEnabled ? "Enabled" : "Disabled") << std::endl;
    std::cout << "Do you want to enable or disable inheritance? (e/d): ";
    char choice;
    std::cin >> choice;

    // Construct command to enable/disable inheritance and execute it using popen
    std::string command;
    switch (choice)
    {
    case 'e':
    case 'E':
        command = "icacls \"" + path + "\" /inheritance:e";
        break;
    case 'd':
    case 'D':
        command = "icacls \"" + path + "\" /inheritance:d";
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
        return;
    }
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        throw std::runtime_error("Error executing icacls command");
    }

    // Read command output and print it to console
    char buffer[128];
    while (fgets(buffer, 128, pipe))
    {
        std::cout << buffer;
    }

    // Close the pipe and check the status
    int result = pclose(pipe);
    if (result != 0)
    {
        throw std::runtime_error("icacls command failed with error code " + std::to_string(result));
    }

    // Print success message
    std::cout << "Permissions inheritance " << (choice == 'd' || choice == 'D' ? "disabled" : "enabled")
              << " successfully!" << std::endl;
}
