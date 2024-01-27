#include "../include/pass_protect.h"

const std::string pass_protect::encrypt(std::string password) {
    for (int i = 0; (i < 100 && password[i] != '\0'); i++) {
        password[i] = password[i] + 2;
    }
    return password;
}

const std::string  pass_protect::decrypt(std::string encrypted_password) {
    for (int i = 0; (i < 100 && encrypted_password[i] != '\0'); i++) {
        encrypted_password[i] = encrypted_password[i] - 2;
    }

    return encrypted_password;
}
