#include "intcodelib.h"

using namespace std;

int main()
{
    // intcode program("ut_01.txt");
    // intcode program("ut_02.txt");
    intcode program("part_1.txt");
    program.run_code();
    
    return 0;
}