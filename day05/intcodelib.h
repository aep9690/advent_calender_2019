#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

class intcode
{
    vector<int> code;

    enum mode
    {
        position = 0,
        immediate = 1
    };

    public:
        intcode(string);
        void print_vector(vector<int>);
        void run_code();
        void set_memory(int, int);
        vector<int> get_memory();
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

// Runs int code
void intcode::run_code()
{
    int length = code.size();
    int index = 0;
    int loc_1, loc_2, loc_result;
    int input;
    for (int i = 0; i < length; i++)
    {
        switch (code[index])
        {
        // Addition
        case 1:
            loc_1 = code[index + 1];
            loc_2 = code[index + 2];
            loc_result = code[index + 3];
            code[loc_result] = code[loc_1] + code[loc_2];
            index += 4;
            break;

        // Multiplication
        case 2:
            loc_1 = code[index + 1];
            loc_2 = code[index + 2];
            loc_result = code[index + 3];
            code[loc_result] = code[loc_1] * code[loc_2];
            index += 4;
            break;

        // Input
        case 3:
            loc_result = code[index + 1];
            cout << "Enter integer input: ";
            cin >> code[loc_result] ;
            index += 2;
            break;

        // Output
        case 4:
            loc_result = code[index + 1];
            cout << "Output: " << code[loc_result] << "\n";
            index += 2;
            break;

        // Exit
        case 99:
            return;

        // Errors
        default:
            cout << "Invalid op code: " << code[index] << "\n";
            return;
        }
    }
    return;
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