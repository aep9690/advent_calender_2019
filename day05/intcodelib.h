#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

class intcode
{
    vector<int> code;

    enum MODE
    {
        POSITION = 0,
        IMMEDIATE = 1,
        INVALID = 99
    };

    enum OP
    {
        ADD = 1,
        MULT = 2,
        INPUT = 3,
        OUTPUT = 4,
        JUMP_TRUE = 5,
        JUMP_FALSE = 6,
        LESS = 7,
        EQUAL = 8,
        HALT = 99
    };

    public:
        intcode(string);
        intcode::OP get_op_code(int);
        intcode::MODE get_param_mode(int, int);
        void set_memory(int, int);
        void print_memory();
        void print_vector(vector<int>);
        void run_code();
        int get_value(int, intcode::MODE);
};