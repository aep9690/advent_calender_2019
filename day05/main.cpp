#include "intcodelib.h"

using namespace std;

int main()
{
    intcode program("ut_01.txt");
    program.run_code();
    
    return 0;
}