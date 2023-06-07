#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#ifndef DEFS_HPP
#define DEFS_HPP

typedef struct State {
    char** s;
    unsigned int row_size;

    ostream& operator<<(ostream& os) {
        for (int i = 0; i < 5; ++i) {
            os << "x" << i << ": ";
            for(int j = 0; j < 8; ++j) {
                os << (char) this->s[i][j];
            }
            os << endl;
        }
        return os;
    }
};


#endif