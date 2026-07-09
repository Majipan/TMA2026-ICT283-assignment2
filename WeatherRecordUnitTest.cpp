#include "WeatherRecord.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "-- Test 1: Weather Record default constructor --" << endl << endl;
    WeatherRecord defaultWeatherRecord;

    cout << "-- Test 2: Weather Record parameterised constructor --" << endl << endl;
    WeatherRecord wr(2026, 06, 21, 23, 59, 404, 100, 200, true, true, true);


    cout << "-- Test 3: Print parameterised WeatherRecord --" << endl << endl;
    cout << "Date: " << wr.GetDay() << "/"
                     << wr.GetMonth() << "/"
                     << wr.GetYear() << endl
         << "Time: " << wr.GetHour() << ":"
                     << wr.GetMinute() << endl
         << "WindSpeed: " << wr.GetWindSpeed() << endl
         << "Ambient Air Temperature: " << wr.GetWindSpeed() << endl
         << "Solar Radiation: " << wr.GetSoRad() << endl;
}
