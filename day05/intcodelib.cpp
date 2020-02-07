#include "intcodelib.h"

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

// Parse op code operator
intcode::OP intcode::get_op_code(int index)
{
    int inst = code[index];
    int op_code = inst % 100;
    return static_cast<OP>(op_code);
}

// Get parameter modes from op code
intcode::MODE intcode::get_param_mode(int index, int param)
{
    int divisor = 10;;
    for (int i = 0; i < param; i++)
    {
        divisor *= 10;
    }
    int inst = code[index];
    int mode = (inst / divisor) % 10;
    return static_cast<MODE>(mode);
}

// Get value stored in memory
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

// Set value in memory
void intcode::set_memory(int index, int value)
{
    int addr = code[index];
    code[addr] = value;
}

// Print entire memory
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
    int input, op_code;
    intcode::MODE mode1, mode2;
    for (int i = 0; i < length; i++)
    {
        op_code = get_op_code(index);
        mode1 = get_param_mode(index, 1);
        mode2 = get_param_mode(index, 2);
        switch (op_code)
        {
            case OP::ADD:
                val1 = get_value(index + 1, mode1);
                val2 = get_value(index + 2, mode2);
                result = val1 + val2;
                set_memory(index + 3, result);
                index += 4;
                break;

            case OP::MULT:
                val1 = get_value(index + 1, mode1);
                val2 = get_value(index + 2, mode2);
                result = val1 * val2;
                set_memory(index + 3, result);
                index += 4;
                break;

            case OP::INPUT:
                cout << "Enter integer input: ";
                cin >> val1;
                set_memory(index + 1, val1);
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
};