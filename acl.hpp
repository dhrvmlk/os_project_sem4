#ifndef ACL_HPP
#define ACL_HPP

#include <string>
#include "aclBase.hpp"

// Implementation class for ACL operations
class ACL : public ACLBase
{
public:
    std::string ReadACL() override;
    void GrantPermission() override;
    void RemovePermission() override;
    void DenyPermission() override;
    void ResetPermissions() override;
    void DisableInheritance() override;
};

#endif
