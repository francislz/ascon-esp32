#include <iostream>
#include "ascon_permutation.hpp"
#include "defs.hpp"

void AsconPermutation::print_state() {
    for (int i = 0; i < 5; ++i) {
        cout << "x" << i << ": ";
        cout << (char) this->state->s[i];
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
    const long round_const = ((long) ((0xf - round) << 4) | round);
    this->state->s[2] = (this->state->s[2] ^ round_const);
}

/**
 * Rotates the bits of a 64-bit integer to the left
 * @param x: 64-bit integer to be rotated
 * @param n: number of bits to rotate
 * @return: rotated 64-bit integer
*/
int64 AsconPermutation::rotate(int64 x, int n) {
    int64 temp = (x >> n) ^ (x << (64 - n));
    return temp;
}

/**
 * Applies the substitution layer to the state by applying the following operations:
 * x0 ^= x4;    x4 ^= x3;    x2 ^= x1;
 * t0  = x0;    t1  = x1;    t2  = x2;    t3  = x3;    t4  = x4;
 * t0 =~ t0;    t1 =~ t1;    t2 =~ t2;    t3 =~ t3;    t4 =~ t4;
 * x0 &= t1;    x1 &= t2;    x2 &= t3;    x3 &= t4;    x4 &= t0;
 * x1 ^= x0;    x2 ^= x1;    x3 ^= x2;    x4 ^= x3;    x0 ^= x4;
 * TODO: Can it be optimized ?
*/
void AsconPermutation::sub_bytes() {
    int64 t[5];
    // x0 ^= x4;    x4 ^= x3;    x2 ^= x1;
    this->state->s[0] ^= this->state->s[4];
    this->state->s[4] ^= this->state->s[3];    
    this->state->s[2] ^= this->state->s[1];
    // t0  = x0;    t1  = x1;    t2  = x2;    t3  = x3;    t4  = x4;
    t[0]  = this->state->s[0];
    t[1]  = this->state->s[1];    
    t[2]  = this->state->s[2];
    t[3]  = this->state->s[3];    
    t[4]  = this->state->s[4];
    // t0 =~ t0;    t1 =~ t1;    t2 =~ t2;    t3 =~ t3;    t4 =~ t4;
    t[0] =~ t[0]; t[1] =~ t[1]; t[2] =~ t[2]; t[3] =~ t[3]; t[4] =~ t[4];
    // t0 &= x1;    t1 &= x2;    t2 &= x3;    t3 &= x4;    t4 &= x0;
    t[0] &= this->state->s[1];
    t[1] &= this->state->s[2];    
    t[2] &= this->state->s[3];    
    t[3] &= this->state->s[4];    
    t[4] &= this->state->s[0];
    // x0 ^= t1;    x1 ^= t2;    x2 ^= t3;    x3 ^= t4;    x4 ^= t0;
    this->state->s[0] ^= t[1];    
    this->state->s[1] ^= t[2];    
    this->state->s[2] ^= t[3];    
    this->state->s[3] ^= t[4];    
    this->state->s[4] ^= t[0];
    // x1 ^= x0;    x0 ^= x4;    x3 ^= x2;    x2 =~ x2;
    this->state->s[1] ^= this->state->s[0];    
    this->state->s[0] ^= this->state->s[4];    
    this->state->s[3] ^= this->state->s[2];    
    this->state->s[2] =~ this->state->s[2];
}

/***
 * Shifts the rows of the state
*/
void AsconPermutation::shift_rows() {
    this->state->s[0] ^= this->rotate(this->state->s[0], 19) ^ this->rotate(this->state->s[0], 28);
    this->state->s[1] ^= this->rotate(this->state->s[1], 61) ^ this->rotate(this->state->s[1], 39);
    this->state->s[2] ^= this->rotate(this->state->s[2], 1) ^ this->rotate(this->state->s[2], 6);
    this->state->s[3] ^= this->rotate(this->state->s[3], 10) ^ this->rotate(this->state->s[3], 17);
    this->state->s[4] ^= this->rotate(this->state->s[4], 7) ^ this->rotate(this->state->s[4], 41);
}

void AsconPermutation::permutate(int rounds) {
    for (int i = 0; i < rounds; ++i) {
        this->add_round_constant(i);
        this->sub_bytes();
        this->shift_rows();
    }
}
