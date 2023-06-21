#include <iostream>
#include <cstring>
#include "ascon.hpp"
#include "ascon_permutation.hpp"
#include "defs.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cout << "Usage: ./a.out <message>" << endl;
        return 1;
    }
    
    const int message_size = strlen(argv[1]);
    
    // 128 bit key
    char* key = "+KbPeShVkYp3s6v9"; 
    char* iv = "12345678";
    char* nonce = "1234567887654321";
    char* message = new char[message_size];
    strcpy(message, argv[1]);

    Ascon* ascon = new Ascon(key, iv, nonce);
    char* cyphertext = ascon->encrypt(message);
    cout << endl;
    ascon->decrypt(cyphertext);
    return 0;
}
