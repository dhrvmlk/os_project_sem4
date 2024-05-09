#ifndef SEC_DESCRIPTORS_HPP
#define SEC_DESCRIPTORS_HPP

/*
    Function declaration for cloning the security descriptor of a file to a
    specified location.
*/
bool cloneSecurityDescriptor(const wchar_t *, const wchar_t *);

/*
    Function declaration for restoring the security descriptor of a specified
    file from the specified location.
*/
bool restoreSecurityDescriptor(const wchar_t *, const wchar_t *);

/*
    Utility function for cloning and restoring file security descriptor, using
    the file paths specified by the user.
*/
void getInfo();

#endif
