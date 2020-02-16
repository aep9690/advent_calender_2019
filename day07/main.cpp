#include <iostream>
#include "intcodelib.h"

using namespace std;

int main()
{
    intcode program("ut_09.txt");
    int arr[7] = {0, 1, 2, 3, 4, 5, 6};
    program.set_input(arr, 7);
    program.print_input();
    program.run_code();
    return 0;
}