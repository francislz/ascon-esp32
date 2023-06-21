#include<iostream>
#include<cstring>
#include "ascon.hpp"
#include "ascon_permutation.hpp"

using namespace std;

Ascon::Ascon(char* key, char* iv, char* nonce) {
    this->key = new int64[2];

    State* state = new State;

    state->s = new int64[5];
    
    // Saving key in long format to later use it in the permutation
    memcpy(&this->key[0], key, 8);
    memcpy(&this->key[1], key + 8, 8);
    // NOTE: Why pointer arithmetic is not working?
    // e.g: memcpy(&state->s + 8, iv, 8); gives this->state->s[1] = 0x0
    // God I hate pointers
    memcpy(&state->s[0], iv, 8);
    memcpy(&state->s[1], key, 8);
    memcpy(&state->s[2], key + 8, 8);
    memcpy(&state->s[3], nonce, 8);
    memcpy(&state->s[4], nonce + 8, 8);

    this->state = state;
}

Ascon::~Ascon() {
    delete[] this->state->s;
    delete this->state;
}

void Ascon::print_state() {
    for (int i = 0; i < 5; ++i) {
        cout << "x" << i << ": " << hex << this->state->s[i] << endl;
    }
    cout << endl;
    //cout << *this->state << endl;
}

char* Ascon::get_tag() {
    return this->tag;
}

void Ascon::initialization() {
    AsconPermutation* permutation = new AsconPermutation(this->state);
    permutation->permutate(12);
    this->state->s[3] ^= this->key[0];
    this->state->s[4] ^= this->key[1];
    // this->print_state();
}

void Ascon::associated_data() {
    // TODO
}

void Ascon::plaintext() {
    AsconPermutation* permutation = new AsconPermutation(this->state);
    for (int i = 0; i < this->qty_blocks; ++i) {
        this->message[i] ^= this->state->s[0];
        this->state->s[0] = this->message[i];
        permutation->permutate(6);
    }
}

void Ascon::finalization() {
    this->state->s[0] ^= this->key[0];
    this->state->s[1] ^= this->key[1];

    AsconPermutation* permutation = new AsconPermutation(this->state);
    permutation->permutate(12);

    this->tag = new char[16];
    memcpy(this->tag, &this->state->s[3], 8);
    memcpy(this->tag + 8, &this->state->s[4], 8);
    cout << "Tag: " << hex << this->tag << endl;
}

char* Ascon::encrypt(char* message) {
    this->qty_blocks = strlen(message) / 8;
    this->message = new int64[this->qty_blocks];

    cout << "Original message blocks: " << endl;
    for (unsigned int i = 0; i < this->qty_blocks; ++i) {
        memcpy(&this->message[i], message + (i * 8), 8);
        cout << "Block " << i << ": " << hex << this->message[i] << endl;
    }

    this->initialization();
    // this->associated_data();
    this->plaintext();

    cout << endl;
    cout << "Encrypted message blocks: " << endl;
    char* encrypted_message = new char[this->qty_blocks * 8];
    for (unsigned int i = 0; i < this->qty_blocks; ++i) {
        cout << "Block " << i << ": " << hex << this->message[i] << endl;
        memcpy(encrypted_message + (i * 8), &this->message[i], 8);
    }
    this->finalization();
    return encrypted_message;
}

char* Ascon::decrypt(char* cyphertext) {
    this->qty_blocks = strlen(cyphertext) / 8;
    this->message = new int64[this->qty_blocks];

    for (unsigned int i = 0; i < this->qty_blocks; ++i) {
        memcpy(&this->message[i], cyphertext + (i * 8), 8);
    }
    this->initialization();
    this->plaintext();
    // this->associated_data();

    cout << "Decrypted message blocks: " << endl;
    char* message = new char[this->qty_blocks * 8];
    for (unsigned int i = 0; i < this->qty_blocks; ++i) {
        cout << "Block " << i << ": " << hex << this->message[i] << endl;
        memcpy(message + (i * 8), &this->message[i], 8);
    }
    this->finalization();
    return message;
}
