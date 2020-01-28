#include "intcodelib.h"

int main()
{
    // Part One
    intcode program("code_part01.csv");
    program.run_code();
    program.print_memory();

    // Part Two
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            intcode program("code_part01.csv");
            program.set_memory(1, i);
            program.set_memory(2, j);
            program.run_code();
            
            vector<string> result = program.get_memory();
            if (stoi(result[0]) == 19690720)
            {
                program.print_memory();
                cout << "Noun = " << i << "\n";
                cout << "Verb = " << j << "\n";
                return 0;

            }
        }
    }

    return 0;
}