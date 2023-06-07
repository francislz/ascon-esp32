#include <iostream>
#include <string>
#include "ascon.hpp"
#include "ascon_permutation.hpp"
#include "defs.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    // if (argc < 3) {
    //     cout << "Usage: ./a.out <key> <message>" << endl;
    //     return 1;
    // }
    // cout << "Key: " << argv[1] << endl;
    // cout << "Message: " << argv[2] << endl;
    
    // 128 bit key
    char* key = "+KbPeShVkYp3s6v9";
    char* iv = "12345678";
    char* nonce = "1234567887654321";
    char* message = (char*) argv[2];

    Ascon* ascon = new Ascon(key, iv, nonce);
    ascon->encrypt(message);
    return 0;
}
