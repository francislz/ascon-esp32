#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#ifndef DEFS_HPP
#define DEFS_HPP

typedef unsigned long long int64;

struct State {
    int64* s;
    unsigned int row_size;

    ostream& operator<<(ostream& os) {
        for (int i = 0; i < 5; ++i) {
            os << "x" << i << ": ";
            os << (char) this->s[i];
            os << endl;
        }
        return os;
    }
};


#endif