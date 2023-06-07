#include <iostream>
#include "ascon_permutation.hpp"
#include "defs.hpp"

const unsigned char SBOX[256] = {

};

void AsconPermutation::print_state() {
    for (int i = 0; i < 5; ++i) {
        cout << "x" << i << ": ";
        for(int j = 0; j < 8; ++j) {
            cout << (char) this->state->s[i][j];
        }
        cout << endl;
    }
    //cout << *this->state << endl;
}

AsconPermutation::AsconPermutation(State* state) {
    this->state = state;
}

AsconPermutation::~AsconPermutation() {
    this->state = NULL;
}

/** 
 * Calculates the round constant and adds it to the state
 * Round constant is the 4-bit value 0xf - round, deslocated 4 bits to the left and or'ed with the round value
 * E.g: 0xf - 1 = 0xe, 0xe << 4 = 0xe0, 0xe0 | 1 = 0xe1
 * NOTE: Is it vulnerable to timing attacks?
 * NOTE: Is it vulnerable to side channel attacks?
 * TODO: Create Debug logic if debug flag is set
*/
void AsconPermutation::add_round_constant(int round) {
    // cout << "======================================" << endl;
    // cout << "Round: " << round << endl;
    // cout << "Before: " << this->state->s[2] << endl;
    const long round_const = ((long) ((0xf - round) << 4) | round);
    // cout << "Round const: " << hex << round_const << endl;
    this->state->s[2] = (char*) ((long) this->state->s[2] ^ round_const);
    // cout << "After: " << this->state->s[2] << endl;
    // cout << "======================================" << endl;
}

void AsconPermutation::sub_bytes(State* state) {
    // TODO
}

void AsconPermutation::shift_rows(State* state) {
    // TODO
}

void AsconPermutation::permutate(int rounds) {
    for (int i = 0; i < rounds; ++i) {
        this->add_round_constant(i);
        // this->sub_bytes(this->state);
        // this->shift_rows(this->state);
    }
}
