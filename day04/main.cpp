#include <iostream>
#include <math.h>

using namespace std;

int getNumDigits(int input)
{
    int count = 0;
    while (input != 0)
    {
        input = input / 10;
        count++;
    }
    return count;
}

int getDigit(int input, int n)
{
    for (int i = 0; i < n; i++)
    {
        input = input / 10;
    }
    int output = input % 10;
    return output;
}

int* getDigits(int input, int n)
{
    int *digits = new int[n];
    for (int i = 0; i < n; i++)
    {
        digits[n - i - 1] = getDigit(input, i);
    }

    return digits;
}

bool doesRepeat(int input[], int n)
{
    bool repeat = false;
    int valuePP, valueP, value;
    for(int i = 2; i < n; i++)
    {
        valuePP = input[i - 2];
        valueP = input[i - 1];
        value = input[i];
        if(valuePP == valueP)
        {
            if(valueP == value)
            {
                repeat = false;
            }
            else
            {
                return true;
            }
            
            repeat = true;
        }
    }

    // for(int i = 0; i < n; i++)
    // {
    //     cout << input[i];
    // }
    // cout << " " << repeat << "\n";

    return repeat;
}

bool doesIncrease(int input[], int n)
{
    bool increase = true;
    int value = 0;
    int prevValue = 0;
    for(int i = 1; i < n; i++)
    {
        value = input[i];
        prevValue = input[i - 1];
        if(input[i] < input[i - 1])
        {
            increase = false;
        }
    }

    return increase;
}

bool isValid(int input)
{
    int n = getNumDigits(input);
    int *digits = getDigits(input, n);
    bool repeats = doesRepeat(digits, n);
    bool increases = doesIncrease(digits, n);
    if(repeats & increases)
    {
        return true;
    }

     return false;
}

int main()
{
    int minPassword = 234208;
    int maxPassword = 765869;
    // int minPassword = 11111;
    // int maxPassword = 12000;

    int count = 0;
    for(int password = minPassword;
            password < maxPassword + 1;
            password++)
    {
        if(isValid(password))
        {
            count++;
        }
    }

    cout << count;

    return 0;
}