#ifndef PASS_PROTECT_H
#define PASS_PROTECT_H

//#include <stdio.h>
#include <iostream>

class pass_protect{
    public:

    /**
     * @brief Encrypt the user's password for added security. 
     * 
     * @param password The user's (unencrypted) password. 
     * @return The user's encrypted password.  
     */
    static const std::string encrypt(std::string password); 

    /**
     * @brief Decrypt the user's encrypted password back to its original form. 
     * 
     * @param encrypted_password The encrypted password that must be reverted.  
     * @return The orginal password (decrypted password).  
     */
    static const std::string decrypt(std::string encrypted_password);
}; 

#endif 
