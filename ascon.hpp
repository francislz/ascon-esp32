#include<string>
#include "defs.hpp"
#include "ascon_permutation.hpp"
using namespace std;

#ifndef ASCON_HPP
#define ASCON_HPP

class Ascon {
    private:
        int64* key;
        State* state;
        int64* message;
        char* tag;
        unsigned int qty_blocks;
        void initialization();
        void associated_data();
        void plaintext();
        void finalization();
        void print_state();
   public:
        Ascon(char* key, char* iv, char* nonce);
        ~Ascon(); 
        char* encrypt(char* message);
        char* decrypt(char* message);
        char* get_tag();
};

#endif