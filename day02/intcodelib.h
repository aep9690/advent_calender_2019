#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

class intcode
{
    vector<string> code;

    public:
        intcode(string);
        void print_vector(vector<string>);
        void run_code();
        void set_memory(int, int);
        vector<string> get_memory();
        void print_memory();
};

intcode::intcode(string filename)
{
    // Open the file
    ifstream file(filename);

    // Read the file and store it in a string variable 'line'
    string line;
    getline(file, line);
    stringstream s(line);
    
    // Read every column data of a row and store it in a string variable, 'word'
    vector<string> row;
    string word;
    while (getline(s, word, ','))
    {
        // Add all the column data of a row to a vector
        row.push_back(word);
    }

    code = row;
}

// Use this to print a string vector
void intcode::print_vector(vector<string> input)
{
    for (int i = 0; i < input.size(); i++)
    {
        cout << input.at(i) << ',';
    }

    cout << "\n";
}

// Runs int code
void intcode::run_code()
{
    int length = code.size();
    int index = 0;
    int loc_1, loc_2, loc_result;
    for (int i = 0; i < length; i++)
    {
        switch (stoi(code[index]))
        {
        // Addition
        case 1:
            loc_1 = stoi(code[index + 1]);
            loc_2 = stoi(code[index + 2]);
            loc_result = stoi(code[index + 3]);
            code[loc_result] = to_string(stoi(code[loc_1]) + stoi(code[loc_2]));
            index += 4;
            break;

        // Multiplication
        case 2:
            loc_1 = stoi(code[index + 1]);
            loc_2 = stoi(code[index + 2]);
            loc_result = stoi(code[index + 3]);
            code[loc_result] = to_string(stoi(code[loc_1]) * stoi(code[loc_2]));
            index += 4;
            break;

        // Exit
        case 99:
            return;
            break;

        // Errors
        default:
            cout << "Invalid op code: " << stoi(code[index]) << "\n";
            return;
            break;
        }
    }
    return;
}

void intcode::set_memory(int addr, int value)
{
    code[addr] = to_string(value);
}

vector<string> intcode::get_memory()
{
    return code;
}

void intcode::print_memory()
{
    print_vector(code);

}