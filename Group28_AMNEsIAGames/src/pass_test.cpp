#include "../include/pass_protect.h"

int main(){
    std::cout << pass_protect::encrypt("ilovecandy") << std::endl;
    std::cout << pass_protect::decrypt(pass_protect::encrypt("ilovecandy")) << std::endl;
    return 0;
}