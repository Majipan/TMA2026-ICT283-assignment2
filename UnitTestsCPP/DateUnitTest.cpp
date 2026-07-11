#include "../Date.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "-- Test 1: Construct default Date --" << endl << endl;
    Date date;

    cout << "-- Test 2: Display default Date --" << endl;
    cout << " Year: " << date.GetYear() << endl
         << "Month: " << date.GetMonth() << endl
         << "  Day: " << date.GetDay() << endl << endl;


    cout << "-- Test 3: Construct Date with params --" << endl << endl;
    Date date2(2026, 10, 5);

    cout << "-- Test 4: Display with params --" << endl;
    cout << " Year: " << date2.GetYear() << endl
         << "Month: " << date2.GetMonth() << endl
         << "  Day: " << date2.GetDay() << endl << endl;

    cout << "-- Test 5: Test Setters --" << endl;
    cout << "Set date to day 21, month 6, year 2026" << endl;
    date2.SetYear(2026);
    date2.SetMonth(6);
    date2.SetDay(21);
    cout << " Year: " << date2.GetYear() << endl
         << "Month: " << date2.GetMonth() << endl
         << "  Day: " << date2.GetDay() << endl;
}
