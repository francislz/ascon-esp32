#include<string>
#include "defs.hpp"
using namespace std;

#ifndef ASCON_PERMUTATION_HPP
#define ASCON_PERMUTATION_HPP

class AsconPermutation {
    private:
        State* state;
        void add_round_constant(int round);
        void sub_bytes(State* state);
        void shift_rows(State* state);
        void print_state();
    public:
        AsconPermutation(State* state);
        ~AsconPermutation(); 
        void permutate(int rounds);
};

#endif