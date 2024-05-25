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