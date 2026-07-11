#include "../Time.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "-- Test 1: Construct default Time --" << endl << endl;
    Time time;

    cout << "-- Test 2: Display default Time --" << endl;
    cout << "  Hour: " << time.GetHour() << endl
         << "Minute: " << time.GetMinute() << endl << endl;


    cout << "-- Test 3: Construct Date with params --" << endl;
     Time time2(23, 59);

    cout << "-- Test 4: Display with params --" << endl;
    cout << "  Hour: " << time2.GetHour() << endl
         << "Minute: " << time2.GetMinute() << endl << endl;

    cout << "-- Test 5: Test Setters --" << endl;
    cout << "Set time to hour: 4, minute: 6" << endl;
    time2.SetHour(4);
    time2.SetMinute(6);
    cout << "  Hour: " << time2.GetHour() << endl
         << "Minute: " << time2.GetMinute() << endl;
}
