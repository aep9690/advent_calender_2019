#include <iostream>

using namespace std;

int getNumDigits(int input)
{
    int count = 0;
    while(input != 0)
    {
        input = input/10;
        count++;
    }
    return count;
}

int getDigit(int input, int n)
{
    for(int i = 0; i < n; i++)
    {
        input = input / 10;
    }
    int output = input % 10;
    return output;
}

int* getDigits(int input)
{
    int n = getNumDigits(input);
    int* digits = new int[n];
    for(int i = 0; i < n; i++)
    {
        digits[n - i - 1] = getDigit(input, i);
    }

    return digits;
}

int main()
{
    int minPassword = 234208;
    int* digits = getDigits(minPassword);
    int n = getNumDigits(minPassword);

    for(int i = 0; i < n; i++)
    {
        cout << digits[i] << ", ";
    }
    cout << "\n";

    return 0;
}