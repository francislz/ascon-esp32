#include<iostream>
#include<cstring>
#include "ascon.hpp"
#include "ascon_permutation.hpp"

using namespace std;

Ascon::Ascon(char* key, char* iv, char* nonce) {
    key = key;

    State* state = new State;

    state->s = new char*[5];
    for(int i = 0; i < 5; i++) {
        state->s[i] = new char[8];
    }
    
    strcpy(state->s[0], iv);
    strcpy(state->s[1], key);
    strcpy(state->s[2], key + 8);
    strcpy(state->s[3], nonce);
    strcpy(state->s[4], nonce + 8);

    this->state = state;
}

Ascon::~Ascon() {
    for (int i = 0; i < 8; ++i){
        delete[] this->state->s[i];
    }
    delete[] this->state->s;
    delete this->state;
}

void Ascon::print_state() {
    for (int i = 0; i < 5; ++i) {
        cout << "x" << i << ": ";
        for(int j = 0; j < 8; ++j) {
            cout << (char) this->state->s[i][j];
        }
        cout << endl;
    }
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
    // TODO
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
