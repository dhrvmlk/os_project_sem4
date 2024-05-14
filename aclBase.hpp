#ifndef ACL_BASE_HPP
#define ACL_BASE_HPP

#include <string>

// Abstract Base class for ACL operations
class ACLBase
{
public:
    // Data members
    std::string filename;   // File path
    std::string username;   // Username for permission
    std::string permission; // Permission type
    char buffer[128];       // Buffer for command output

    // Virtual Methods
    virtual std::string ReadACL() = 0;
    virtual void GrantPermission() = 0;
    virtual void RemovePermission() = 0;
    virtual void DenyPermission() = 0;
    virtual void ResetPermissions() = 0;
    virtual void DisableInheritance() = 0;
};

#endif
