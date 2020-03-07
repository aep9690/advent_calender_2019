#include <iostream>
#include "intcodelib.h"

using namespace std;

bool hasDuplicate(int data[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            int x = data[i];
            int y = data[j];
            if ((x == y) & (i != j))
            {
                return true;
            }
        }
    }
    return false;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main()
{
    // Make Amplifiers
    string filename = "part_one.txt";
    int output = 0;
    int input = 0;
    int numAmps = 5;
    for (int i = 0; i < numAmps; i++)
    {
        for (int j = 0; j < numAmps; j++)
        {
            for (int k = 0; k < numAmps; k++)
            {
                for (int l = 0; l < numAmps; l++)
                {
                    for (int m = 0; m < numAmps; m++)
                    {
                        int phases[] = {i, j, k, l, m};
                        if (!hasDuplicate(phases, numAmps))
                        {
                            intcode ampA(filename);
                            intcode ampB(filename);
                            intcode ampC(filename);
                            intcode ampD(filename);
                            intcode ampE(filename);
                            
                            int temp[] = {i, input};
                            ampA.set_input(temp, 2);
                            ampA.run_code();
                            
                            temp[0] = j;
                            temp[1] = ampA.get_output();
                            ampB.set_input(temp, 2);
                            ampB.run_code();
                            
                            temp[0] = k;
                            temp[1] = ampB.get_output();
                            ampC.set_input(temp, 2);
                            ampC.run_code();
                            
                            temp[0] = l;
                            temp[1] = ampC.get_output();
                            ampD.set_input(temp, 2);
                            ampD.run_code();
                            
                            temp[0] = m;
                            temp[1] = ampD.get_output();
                            ampE.set_input(temp, 2);
                            ampE.run_code();

                            if(ampE.get_output() > output)
                            {
                                output = ampE.get_output();
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "Max Output: " << output << "\n";
    return EXIT_SUCCESS;
}