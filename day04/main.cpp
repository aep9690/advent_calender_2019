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
    bool consec = false;
    bool prev = false;
    bool next = false;
    for (int i = 0; i < n - 1; i++)
    {
        // Check if there are two numbers in a row
        if (input[i] == input [i + 1])
        {
            consec = true;
        }
        else
        {
            consec = false;
        }
        
        // Check the i and i - 1 value
        if (i > 0)
        {
            if (input[i - 1] == input[i])
            {
                prev = true;
            }
            else
            {
                prev = false;
            }
        }
        else
        {
            prev = false;
        }
        

        // Check the i + 1 and i + 2 value
        if (i < n - 2)
        {
            if (input[i + 1] == input[i + 2])
            {
                next = true;
            }
            else
            {
                next = false;
            }
        }
        else
        {
            next = false;
        }

        // Check consecutive values
        if (consec & !prev & !next)
        {
            return true;
        }
    }

    return false;
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
    bool increases = doesIncrease(digits, n);
    bool repeats = doesRepeat(digits, n);
    if (increases & repeats)
    {
        return true;
    }

     return false;
}

int main()
{
    int minPassword = 234208;
    int maxPassword = 765869;

    int count = 0;
    for(int password = minPassword;
            password < maxPassword + 1;
            password++)
    {
        if(isValid(password))
        {
            count++;
            // cout << password << ": True\n";
        }
        else
        {
            // cout << password << ": False\n";
        }
    }

    cout << count;

    return 0;
}