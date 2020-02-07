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
        HALT = 99
    };

    public:
        intcode(string);
        intcode::OP get_op_code(int);
        intcode::MODE get_param_mode(int, int);
        vector<int> get_memory();
        void set_memory(int, int);
        void print_memory();
        void print_vector(vector<int>);
        void run_code();
        int get_value(int, intcode::MODE);
};

intcode::intcode(string filename)
{
    // Open the file
    ifstream file(filename);

    // Read the file and store it in a string variable 'line'
    string line;
    getline(file, line);
    stringstream s(line);
    
    // Read column data of a row and store it in a string variable, 'word'
    vector<int> row;
    string word;
    while (getline(s, word, ','))
    {
        // Add all the column data of a row to a vector
        row.push_back(stoi(word));
    }

    code = row;
}

// Use this to print a string vector
void intcode::print_vector(vector<int> input)
{
    for (int i = 0; i < input.size(); i++)
    {
        cout << input.at(i) << ',';
    }

    cout << "\n";
}

intcode::OP intcode::get_op_code(int inst)
{
    int op_code = inst % 100;
    return static_cast<OP>(op_code);
}

intcode::MODE intcode::get_param_mode(int inst, int param)
{
    int divisor = 10;;
    for (int i = 0; i < param; i++)
    {
        divisor *= 10;
    }

    int mode = (inst / divisor) % 10;
    return static_cast<MODE>(mode);
}

int intcode::get_value(int addr, intcode::MODE mode)
{
    int value = code[addr];
    if (mode == MODE::IMMEDIATE)
    {
        return value;
    }
    else if (mode == MODE::POSITION)
    {
        return code[value];
    }
    else
    {
        cout << "Mode Invalid\n";
        return 99;
    }
    
}

void intcode::set_memory(int addr, int value)
{
    code[addr] = value;
}

vector<int> intcode::get_memory()
{
    return code;
}

void intcode::print_memory()
{
    print_vector(code);

}

// Runs int code
void intcode::run_code()
{
    int length = code.size();
    int index = 0;
    int val1, val2, result;
    int input, op_code, addr;
    intcode::MODE mode1, mode2;
    for (int i = 0; i < length; i++)
    {
        op_code = get_op_code(code[index]);
        mode1 = get_param_mode(code[index], 1);
        mode2 = get_param_mode(code[index], 2);
        switch (op_code)
        {
            case OP::ADD:
                val1 = get_value(index + 1, mode1);
                val2 = get_value(index + 2, mode2);
                result = val1 + val2;
                set_memory(code[index + 3], result);
                index += 4;
                break;

            case OP::MULT:
                val1 = get_value(index + 1, mode1);
                val2 = get_value(index + 2, mode2);
                result = val1 * val2;
                set_memory(code[index + 3], result);
                index += 4;
                break;

            case OP::INPUT:
                cout << "Enter integer input: ";
                cin >> val1;
                addr = code[index + 1];
                set_memory(addr, val1);
                index += 2;
                break;

            case OP::OUTPUT:
                val1 = get_value(index + 1, mode1);
                cout << "Output: " << val1 << "\n";
                index += 2;
                break;

            case OP::HALT:
                return;

            default:
                cout << "Invalid op code: " << code[index] << "\n";
                return;
        }
    }
    return;
}