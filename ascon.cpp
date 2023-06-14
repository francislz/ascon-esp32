#include<iostream>
#include<cstring>
#include "ascon.hpp"
#include "ascon_permutation.hpp"

using namespace std;

Ascon::Ascon(char* key, char* iv, char* nonce) {
    key = key;

    State* state = new State;

    state->s = new int64[5];
    
    cout << "Addr s: " << state->s << endl;
    cout << "Addr s++: " << state->s++ << endl;
    cout << "Addr s[0]: " << &state->s[0] << endl;
    cout << "Addr s[1]: " << &state->s[1] << endl;
    cout << "Addr s[1]: " << &state->s[2] << endl;
    
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

void Ascon::initialization() {
    // TODO
}

void Ascon::associated_data() {
    // TODO
}

void Ascon::plaintext() {
    this->print_state();
    AsconPermutation* permutation = new AsconPermutation(this->state);
    permutation->permutate(12);
    this->print_state();
}

void Ascon::cypher() {
    // TODO
}

void Ascon::finalization() {
    // TODO
}

char* Ascon::encrypt(char* message) {
    this->plaintext();
    // this->qty_blocks = strlen(message) / 8;
    // TODO
    return message;
}

char* Ascon::decrypt(char* message) {
    // TODO
    return message;
}
