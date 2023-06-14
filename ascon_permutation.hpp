#include<string>
#include "defs.hpp"
using namespace std;

#ifndef ASCON_PERMUTATION_HPP
#define ASCON_PERMUTATION_HPP

class AsconPermutation {
    private:
        State* state;
        void add_round_constant(int round);
        void sub_bytes();
        void shift_rows();
        int64 rotate(int64 x, int n);
        void print_state();
    public:
        AsconPermutation(State* state);
        ~AsconPermutation(); 
        void permutate(int rounds);
};

#endif