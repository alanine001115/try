/*
 * COMP2011 (Spring 2021) Programming Assignment 1
 *
 * Student name: FILL YOUR NAME HERE
 * Student ID: FILL YOUR STUDENT ID NUMBER HERE
 * Student email: FILL YOUR EMAIL HERE
 *
 */

#include <iostream>
#include <limits>
using namespace std;

// Global Constants
// You cannot modify these global constants
// You cannot use your own global variables
const int LONGLONG_SIZE = 64;
const long long ONE = 1;
// End of Global Constants

// Helper Functions
// Declare additional helper functions below when necessary

// End of Helper Functions

// Tasks
// Please write your code under the TODO tag
// You cannot change the function declarations

// Task 1
int initialize(int numSeats, unsigned long long &bitmap)
{
    // Task 1 TODO
    char c;
    bitmap=0;
    if (numSeats<ONE||numSeats>LONGLONG_SIZE)
    {
        cout << "Error: Number of seats out of range." << endl;
        return -1;
    }
    else
    {
        for (int i = 0; i < numSeats; i++)
        {
            cin>>c;
            if (c=='1') bitmap=(bitmap<<1)|1;
            else if (c=='0') bitmap=(bitmap<<1);
            else
            {
                cout<<"Error: Illegal state input."<<endl;
                return -1;
            }
        }
        return 0;
    }
    // End of Task 1 TODO
}

// Task 2
int getSeatState(int numSeats, unsigned long long bitmap, int seatIndex)
{
    // Task 2 TODO
    if (seatIndex<0||seatIndex>=numSeats) return -1;
    else return ((bitmap>>(numSeats-seatIndex-1))&1);
    // End of Task 2 TODO
}

// Task 3
void printSeats(int numSeats, unsigned long long bitmap)
{
    // Task 3 TODO
    for (int i = 0; i < numSeats; i++)
    cout << getSeatState(numSeats,bitmap,i);
    cout << endl;
    // End of Task 3 TODO
}

// Task 4
int setSeatOccupied(int numSeats, unsigned long long &bitmap, int seatIndex)
{
    // Task 4 TODO
    if (seatIndex<0||seatIndex>=numSeats) return -1;
    else if (getSeatState(numSeats,bitmap,seatIndex)) return -1;
    else bitmap=bitmap|(ONE<<(numSeats-seatIndex-1));
    return 0;
    // End of Task 4 TODO
}

// Task 5
int setSeatEmpty(int numSeats, unsigned long long &bitmap, int seatIndex)
{
    // Task 5 TODO
    if (seatIndex<0||seatIndex>=numSeats) return -1;
    else if (!getSeatState(numSeats,bitmap,seatIndex)) return -1;
    else bitmap=bitmap&(~(ONE<<(numSeats-seatIndex-1)));
    return 0;
    // End of Task 5 TODO
}

// Task 6
int getSeatDistance(int numSeats, unsigned long long bitmap, int seatIndex)
{
    // Task 6 TODO
    int leftdist=numSeats,rightdist=numSeats;
    if (seatIndex<0||seatIndex>=numSeats) return -1;
    else
    {
        for (int i = 0; seatIndex-i >=0 ; i++)
        {
            if (getSeatState(numSeats,bitmap,seatIndex-i))
            {
                leftdist=i;
                break;
            }
        }
        for (int i = 0; seatIndex+i < numSeats ; i++)
        {
            if (getSeatState(numSeats,bitmap,seatIndex+i))
            {
                rightdist=i;
                break;
            }
        }
        return (leftdist<rightdist)?leftdist:rightdist;
    }
    // End of Task 6 TODO
}

// Task 7
int findSeat(int numSeats, unsigned long long bitmap)
{
    // Task 7 TODO
    int dist=0,desireseat;
    for (int i = 0; i < numSeats; i++)
    {
        dist=(dist<getSeatDistance(numSeats,bitmap,i))?getSeatDistance(numSeats,bitmap,i):dist;
    }
    if (dist==0) return -1;
    for (int i = 0; i < numSeats; i++)
    {
        if (dist==getSeatDistance(numSeats,bitmap,i))
        {
            desireseat = i;
            break;
        }
    }
    return desireseat;
    // End of Task 7 TODO
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED

void run_init(int &numSeats, unsigned long long &bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Initializing" << endl;
    cout << endl;
    int initResult = 0;
    do
    {
        cout << "? Enter the total number of seats:";
        cin >> numSeats;
        cout << "? Enter the initial state of seats:" << endl;
        initResult = initialize(numSeats, bitmap);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (initResult < 0);
    cout << "! Initialization succeeded!" << endl;
}

void run_getSeatState(int numSeats, unsigned long long bitmap)
{

    int seatIndex;
    int seatState;
    cout << "##################################################" << endl;
    cout << "# Query the current state of a seat" << endl;
    cout << endl;
    cout << "? Enter the index of queried seat:";
    cin >> seatIndex;
    seatState = getSeatState(numSeats, bitmap, seatIndex);
    if (seatState < 0)
    {
        cout << "! Error: Seat index out of bounds. Query failed." << endl;
    }
    else if (seatState == 0)
    {
        cout << "! The queried seat is empty." << endl;
    }
    else if (seatState == 1)
    {
        cout << "! The queried seat is occupied." << endl;
    }
}

void run_printSeats(int numSeats, unsigned long long bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Printing the current state" << endl;
    cout << endl;
    printSeats(numSeats, bitmap);
    cout << endl;
}

void run_setSeatOccupied(int numSeats, unsigned long long &bitmap)
{

    cout << "##################################################" << endl;
    cout << "# Marking a seat as occupied" << endl;
    cout << endl;
    int seatIndex;
    int result;
    cout << "? Enter the index of target seat:";
    cin >> seatIndex;
    result = setSeatOccupied(numSeats, bitmap, seatIndex);
    if (result < 0)
    {
        cout << "! Error: Failed to set seat state, seat index out of bounds or seat already occupied." << endl;
    }
    else
    {
        cout << "! Seat state set." << endl;
    }
}

void run_setSeatEmpty(int numSeats, unsigned long long &bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Marking a seat as empty" << endl;
    cout << endl;
    int seatIndex;
    int result;
    cout << "? Enter the index of target seat:";
    cin >> seatIndex;
    result = setSeatEmpty(numSeats, bitmap, seatIndex);
    if (result < 0)
    {
        cout << "! Error: Failed to set seat state, seat index out of bounds or seat is already empty." << endl;
    }
    else
    {
        cout << "! Seat state set." << endl;
    }
}

void run_getSeatDist(int numSeats, unsigned long long bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Calculating the closest distance to occupied seats" << endl;
    cout << endl;
    int seatIndex;
    int distance;
    cout << "? Enter the index of queried seat:";
    cin >> seatIndex;
    distance = getSeatDistance(numSeats, bitmap, seatIndex);
    if (distance < 0)
    {
        cout << "! Error: Seat index out of bounds. Query failed." << endl;
    }
    else
    {
        cout << "! The distance to closest occupied seat is " << distance << "." << endl;
    }
}

void run_findSeat(int numSeats, unsigned long long bitmap)
{
    cout << "##################################################" << endl;
    cout << "# Finding an empty seat" << endl;
    cout << endl;
    int seatIndex = findSeat(numSeats, bitmap);
    if (seatIndex == -1)
    {
        cout << "! No empty seats left" << endl;
    }
    else
    {
        cout << "! The empty seat with maximum distance to closest person is at " << seatIndex << "." << endl;
    }
}

void run_option()
{
    int numSeats = 0;
    unsigned long long bitmap = 0;
    int option;
    cout << "==================================================" << endl;
    cout << "= Welcome to COMP2011 PA1 Seat Management System =" << endl;
    cout << "==================================================" << endl;

    run_init(numSeats, bitmap);

    while (true)
    {
        cout << "##################################################" << endl;
        cout << "# Main Menu" << endl;
        cout << endl;
        cout << "1 Initialize" << endl;
        cout << "2 Query the current state of a seat" << endl;
        cout << "3 Print the bitmap to screen" << endl;
        cout << "4 Change the state of a seat to OCCUPIED" << endl;
        cout << "5 Change the state of a seat to EMPTY" << endl;
        cout << "6 Calculate the closest distance from a seat to occupied seats" << endl;
        cout << "7 Find the empty seat with maximum distance to closest occupied seat" << endl;
        cout << "0 Exit" << endl;
        cout << endl;
        cout << "? Please enter an option (0-7): ";
        cin >> option;
        switch (option)
        {
        case 0:
            cout << "! Bye Bye." << endl;
            return;
        case 1:
            run_init(numSeats, bitmap);
            break;
        case 2:
            run_getSeatState(numSeats, bitmap);
            break;
        case 3:
            run_printSeats(numSeats, bitmap);
            break;
        case 4:
            run_setSeatOccupied(numSeats, bitmap);
            break;
        case 5:
            run_setSeatEmpty(numSeats, bitmap);
            break;
        case 6:
            run_getSeatDist(numSeats, bitmap);
            break;
        case 7:
            run_findSeat(numSeats, bitmap);
            break;
        default:
            cout << "Illegal Choice, please try again." << endl;
            break;
        }
        cout << "! Returning to main menu." << endl;
    }
}

int main()
{
    run_option();
    return 0;
}