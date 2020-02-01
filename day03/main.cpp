#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <numeric>

#define partOne False

using namespace std;

int get_size(string filename)
{
    // Open the file
    ifstream file(filename);
    if(file.fail())
    {
        cout << "No suck file.\n";
        return 0;
    }

    // Read the file and store it in a string variable 'line'
    string line;
    getline(file, line);

    // Determine number of instructions
    int size = 0;
    string word;
    stringstream s(line);
    while (getline(s, word, ','))
    {
        size++;
    }

    file.close();

    return size;
}

int* get_deltas(string filename, int size)
{
    ifstream file(filename);
    if(file.fail())
    {
        cout << "No suck file.\n";
        return 0;
    }
    string line;
    getline(file, line);

    // Read through the files and put the directions into the array
    // The directions are the first element of each CSV value
    int* deltas = new int[size];
    int i = 0;
    string word;
    stringstream s(line);
    while (getline(s, word, ','))
    {
        deltas[i] = stoi(word.substr(1, word.length() - 1));
        i++;
    }

    file.close();

    return deltas;
}

char* get_directions(string filename, int size)
{
    ifstream file(filename);
    if(file.fail())
    {
        cout << "No suck file.\n";
        return 0;
    }
    string line;
    getline(file, line);

    // Read through the files and put the directions into the array
    // The directions are the first element of each CSV value
    char* directions = new char[size];
    int i = 0;
    string word;
    stringstream s(line);
    while (getline(s, word, ','))
    {
        directions[i] = word.at(0);
        i++;
    }

    file.close();

    return directions;
}

int get_length(int deltas[], int size)
{
    // Find total path length
    int length = 0;
    for(int i = 0; i < size; i++)
    {
        length += deltas[i];
    }

    return length;
}

int** get_path(char directions[], int deltas[], int size)
{
    // Create an array of pointers of size length
    int length = get_length(deltas, size);
    int** path = new int*[length];

    // Iterate through directions and find all coordinates the wire passes through
    int delta;
    char direct;
    int X = 0;
    int Y = 0;
    int k = 0;
    for(int i = 0; i < size; i++)
    {
        // For each direction
        direct = directions[i];
        delta = deltas[i];
        for(int j = 0; j < delta; j++)
        {
            // Move the specified number of spaces in the specified direction
            switch (direct)
            {
                case 'R':
                {
                    X += 1;
                    break;
                }
                case 'L':
                {
                    X -= 1;
                    break;
                }
                case 'U':
                {
                    Y += 1;
                    break;
                }
                case 'D':
                {
                    Y -= 1;
                    break;
                }
                default:
                {
                    cout << "Invalid direction: " << direct << "\n";
                    break;
                }
            }

            // And record it in the array path
            path[k] = new int[2];
            path[k][0] = X;
            path[k][1] = Y;
            k++;
        }
    }

    return path;
}

bool is_same_point(int arr1[], int arr2[])
{
    if((arr1[0] == arr2[0]) && (arr1[1] == arr2[1]))
    {
        return true;
    }

    return false;
}

int main()
{
    string filename1 = "wire_01_part1.csv";
    string filename2 = "wire_02_part2.csv";

    // Parse wiring diagrams to directions for wire 1 then get the path the wire takes
    int size1 = get_size(filename1);
    char* directions = get_directions(filename1, size1);
    int* deltas = get_deltas(filename1, size1);
    int** wire1 = get_path(directions, deltas, size1);
    int length1 = get_length(deltas, size1);

    // Do the same for wire 2
    int size2 = get_size(filename2);
    directions = get_directions(filename2, size2);
    deltas = get_deltas(filename2, size2);
    int** wire2 = get_path(directions, deltas, size2);
    int length2 = get_length(deltas, size2);

    // Find closest crossover location
    int dist = 0;
    int minDist = INT_MAX;
    for(int i = 0; i  < length1; i++)
    {
        for(int j = 0; j < length2; j++)
        {
            // Find common coordinates between the two wires
            if(is_same_point(wire1[i], wire2[j]))
            {
                // For each point calculate the length of the wire
                #if partOne
                    dist = abs(wire1[i][0]) + abs(wire1[i][1]);        
                #else
                    // Additional plus two is to account for i and j starting at 0
                    dist = i + j + 2;
                #endif
                
                // If the new distance is less than the old min then update
                if(dist < minDist)
                {
                    minDist = dist;
                }
            }
        }
    }

    cout << "\nMinimum distance is: " << minDist << "\n";

    return 0;
}