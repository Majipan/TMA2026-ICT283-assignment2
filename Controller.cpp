#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "Controller.h"
#include "Vector.h"
#include "Bst.h"
#include "Map.h"
#include "MergeSort.h"

using namespace std;

Controller::Controller()
{

}

// ----------------------------------------------
// initiates the controller and operations
void Controller::Run(istream& input, ostream& output)
{
    // attempt to load all data files listed in data_source.txt
    if(!LoadSources())
    {
        m_view.ShowMessage(output, "Error loading one or more data files!");
        return;
    }

    // console logging for records loaded
    stringstream message;
    message << "Loaded records: " << m_weatherData.Size();
    m_view.ShowMessage(output, message.str());

    BuildWeatherTrees();
    TestWeatherTreeMap(output);

    // Menu operations
    int option = 0;

    while(option != 5)
    {
        // Show the menu and enter the main menu loop
        m_view.ShowMenu(output);

        // Request for user input
        MenuRequest request = m_view.GetMenuRequest(input, output);
        option = request.option;

        // Request handling based on user input
        if(option != 5)
        {
            MenuResult result = ProcessRequest(request);
            m_view.ShowResult(output, result);
        }
    }

    m_view.ShowMessage(output, "Goodbye~");
}

// ----------------------------------------------
// Loading of the data_source file
bool Controller::LoadSources()
{
    // Load the data source file
    ifstream infile("data/data_source.txt");

    if(!infile)
    {
        return false;
    }

    // Load the individual data files from data source
    string source;
    bool loadedAtLeastOneFile = false;

    while(getline(infile, source))
    {
        source = Trim(source);

        if(source != "")
        {
            if(!Load("data/" + source))
            {
                return false;
            }

            loadedAtLeastOneFile = true;
        }
    }

    return loadedAtLeastOneFile;
}

// ----------------------------------------------
// load the datafile and store the data into the wind record
bool Controller::Load(string source)
{
    // loads the data file
    ifstream infile(source);

    // checks if the file is loaded
    if(!infile)
    {
        return false;
    }

    // column header data from csv
    string headerLine;
    getline(infile, headerLine);

    // get index of all column headers of interest
    int wastIndex = GetColumnIndex(headerLine, "WAST");
    int speedIndex = GetColumnIndex(headerLine, "S");
    int aatempIndex = GetColumnIndex(headerLine, "T");
    int soradIndex = GetColumnIndex(headerLine, "SR");


    // error handling, if any of the column header is missing
    if(wastIndex == -1 || speedIndex == -1 || aatempIndex == -1 || soradIndex == -1)
    {
        return false;
    }

    // start feeding individual rows into the m_weatherData (WeatherRecord class)
    string line;
    Vector<string> row;

    while(getline(infile, line))
    {
        if(GetLineRecord(line, row))
        {
            int year = 0;
            int month = 0;
            int day = 0;
            int hour = 0;
            int minute = 0;
            float speed = 0;
            float aatemp = 0;
            float sorad = 0;

            // convert WAST into int date and time
            // if WAST is invalid, the whole record is unusable
            bool validWast = ConvertWast(row[wastIndex], year, month, day, hour, minute);

            // checks if the translation succeeded, else skip record
            if (validWast)
            {
                // checks if each of these attributes are present
                bool hasSpeed = TryParseFloat(row[speedIndex], speed);
                bool hasAATemp = TryParseFloat(row[aatempIndex], aatemp);
                bool hasSoRad = TryParseFloat(row[soradIndex], sorad);

                //cout << year << "/" << month << "/" << day << " " << hour << ":" << minute << endl;
                WeatherRecord dataRow(year, month, day, hour, minute, speed, aatemp, sorad,
                                      hasSpeed, hasAATemp, hasSoRad);

                // insert record into vector
                m_weatherData.Insert(m_weatherData.Size(), dataRow);

            }
            else
            {
                // skip this faulty record
            }

        }
    }

    return true;
}

// ----------------------------------------------
// Trims leading & trailing spaces / return / line break
string Controller::Trim(const string& value)
{
    string result = value;

    // trims trailing characters
    while(result.length() > 0 &&                        // value is not empty
            (result[result.length() - 1] == '\r' ||     // trailing return
             result[result.length() - 1] == '\n' ||     // trailing line break
             result[result.length() - 1] == ' '))       // trailing space
    {
        result.erase(result.length() - 1);              // remove any undesirable trailing chars
    }

    // trims leading space
    while(result.length() > 0 && result[0] == ' ')
    {
        result.erase(0, 1);
    }

    return result;
}

// ----------------------------------------------
// get the index of the column of interest
int Controller::GetColumnIndex(const string& headerLine, const string& columnName)
{
    stringstream ss(headerLine);
    string field;
    int index = 0;

    while (getline(ss, field, ','))
    {
        field = Trim(field);        // remove unwanted characters

        if (field == columnName)    // column header found
        {
            return index;           // return column index
        }

        ++index;
    }

    return -1;
}

// ----------------------------------------------
// extract value from a single data row
bool Controller::GetLineRecord(const string& line, Vector<string>& row)
{
    // empties the vector size to start anew
    row.Clear();

    stringstream ss(line);
    string field;

    // iterates each field to save into the Vector Array
    while(getline(ss, field, ','))
    {
        field = Trim(field);
        row.Insert(row.Size(), field);
    }

    return row.Size() > 0;
}

// ----------------------------------------------
// Convert WAST to int date and time
bool Controller::ConvertWast(
    const string& wast,
    int& year,
    int& month,
    int& day,
    int& hour,
    int& minute)
{
    stringstream ss(wast);

    char slash1;
    char slash2;
    char colon;

    // 31/3/2016 9:00
    ss >> day >> slash1 >> month >> slash2 >> year >> hour >> colon >> minute;

    if(ss.fail())
    {
        return false;
    }

    if(slash1 != '/' || slash2 != '/' || colon != ':')
    {
        return false;
    }

    return true;
}

// ----------------------------------------------
// Checks for empty values or anything that isn't a number
bool Controller::TryParseFloat(const string& value, float& number)
{
    // removes leading/trailing spaces
    string trimmed = Trim(value);

    if(trimmed == "")
    {
        return false;
    }

    // checks if it is successfully converted into a float
    stringstream ss(trimmed);

    ss >> number;

    if(ss.fail())
    {
        return false;
    }

    // checks if there are extra chars after the float. 123abc would have extra chars
    char extra;

    if(ss >> extra)
    {
        return false;
    }

    // passed every test
    return true;
}

// ----------------------------------------------
// Generate an int for the year-month key to be used on the map
YearMonthKey Controller::CreateYearMonthKey(int year, int month) const
{
    return year * 100 + month;
}

// ----------------------------------------------
// Find the index based on the key in the bucket listing
int Controller::FindMonthBucketIndex(const Vector<MonthBucket>& buckets, YearMonthKey key) const
{
    for(int i = 0; i < buckets.Size(); ++i)
    {
        if(buckets[i].key == key)
        {
            return i;
        }
    }

    return -1;
}

// ----------------------------------------------
// Add a record to its correct bucket based on the year-month key
/*
Vector<MonthBucket>
    [201503, Vector<WeatherRecord>]
    [201504, Vector<WeatherRecord>]
    [201505, Vector<WeatherRecord>]
*/
void Controller::AddRecordToMonthBucket(Vector<MonthBucket>& buckets, const WeatherRecord& record) const
{
    // get the year-month key for this record
    YearMonthKey key = CreateYearMonthKey(record.GetYear(), record.GetMonth());

    // look for the key in the bucket index listing
    int index = FindMonthBucketIndex(buckets, key);

    // if this key is not found, create a new bucket and add it to the bucket index listing
    if(index == -1)
    {
        MonthBucket bucket;
        bucket.key = key;
        bucket.records.Insert(bucket.records.Size(), record);

        buckets.Insert(buckets.Size(), bucket);
    }
    // if this key is found, add this record to the back of the vector
    else
    {
        buckets[index].records.Insert(buckets[index].records.Size(), record);
    }
}

// ----------------------------------------------
// Remove duplicates from Vector
void Controller::RemoveDuplicateRecords(WeatherData& records) const
{
    // Safety check for when vector has only 1 or less record
    if(records.Size() <= 1)
    {
        return;
    }

    int writeIndex = 1;

    // iterate through the vector to look for duplicates
    for(int readIndex = 1; readIndex < records.Size(); ++readIndex)
    {
        if(!(records[readIndex] == records[writeIndex - 1]))
        {
            if(writeIndex != readIndex)
            {
                records[writeIndex] = records[readIndex];
            }

            ++writeIndex;
        }
    }

    while(records.Size() > writeIndex)
    {
        records.Delete(records.Size() - 1);
    }
}

// ----------------------------------------------
// Insert into a BST record by record
void Controller::BalancedInsert(const WeatherData& records,
                                int left,
                                int right,
                                WeatherTree& tree) const
{
    if(left > right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    tree.Insert(records[mid]);

    BalancedInsert(records, left, mid - 1, tree);
    BalancedInsert(records, mid + 1, right, tree);
}

// ----------------------------------------------
// Main function form the dataset
// temp month bucket  ->  sort  ->  remove duplicates  ->  create balance tree  ->  Map
void Controller::BuildWeatherTrees()
{
    Vector<MonthBucket> buckets;

    for(int i = 0; i < m_weatherData.Size(); ++i)
    {
        AddRecordToMonthBucket(buckets, m_weatherData[i]);
    }

    for(int i = 0; i < buckets.Size(); ++i)
    {
        MergeSort(buckets[i].records);
        RemoveDuplicateRecords(buckets[i].records);

        WeatherTree tree;

        BalancedInsert(buckets[i].records,
                       0,
                       buckets[i].records.Size() - 1,
                       tree);

        m_weatherTrees.Insert(buckets[i].key, tree);
    }
}


// ----------------------------------------------
// Main method to process the request from View
MenuResult Controller::ProcessRequest(const MenuRequest& request)
{
    MenuResult result;
    result.option = request.option;
    result.month = request.date.month;
    result.year = request.date.year;
    result.validOption = true;


    // Initialise all 12 months before processing any menu option
    // This prevents random/uninitialised values from being printed by View
    for(int i = 0; i < 12; ++i)
    {
        result.months[i].month = i + 1;

        result.months[i].hasWind = false;
        result.months[i].windAverage = 0;
        result.months[i].windStdDev = 0;

        result.months[i].hasTemp = false;
        result.months[i].tempAverage = 0;
        result.months[i].tempStdDev = 0;

        result.months[i].hasSolar = false;
        result.months[i].solarTotal = 0;
    }

    // ---------------------------------------------------------------------------------------
    // This point on, handles all menu option data processing
    if(request.option == 1)
    {
        int month = request.date.month;
        int year = request.date.year;
        int index = month - 1;

        int windCount = CountValidRecords(
                            m_weatherData,
                            &WeatherRecord::HasWindSpeed,
                            month,
                            year);

        if(windCount > 0)
        {
            result.months[index].hasWind = true;

            result.months[index].windAverage = Average(
                                                   m_weatherData,
                                                   &WeatherRecord::GetWindSpeed,
                                                   &WeatherRecord::HasWindSpeed,
                                                   month, year);

            result.months[index].windStdDev = StdDev(
                                                  m_weatherData,
                                                  &WeatherRecord::GetWindSpeed,
                                                  &WeatherRecord::HasWindSpeed,
                                                  result.months[index].windAverage,
                                                  month, year);
        }
    }
    else if(request.option == 2)
    {
        int year = request.date.year;

        for(int month = 1; month <= 12; ++month)
        {
            int index = month - 1;

            int tempCount = CountValidRecords(
                                m_weatherData,
                                &WeatherRecord::HasAATemp,
                                month,
                                year);

            if(tempCount > 0)
            {
                result.months[index].hasTemp = true;

                result.months[index].tempAverage = Average(
                                                       m_weatherData,
                                                       &WeatherRecord::GetAATemp,
                                                       &WeatherRecord::HasAATemp,
                                                       month, year);

                result.months[index].tempStdDev = StdDev(
                                                      m_weatherData,
                                                      &WeatherRecord::GetAATemp,
                                                      &WeatherRecord::HasAATemp,
                                                      result.months[index].tempAverage,
                                                      month, year);
            }
        }
    }

    // ---------------------------------------------------------------------------------------
    else if(request.option == 3)
    {
        int year = request.date.year;

        for(int month = 1; month <= 12; ++month)
        {
            int index = month - 1;

            int solarCount = CountValidSolarRecords(
                                 m_weatherData,
                                 month,
                                 year);

            if(solarCount > 0)
            {
                result.months[index].hasSolar = true;

                result.months[index].solarTotal = SolarRadiationTotal(
                                                      m_weatherData,
                                                      month, year);
            }
        }
    }

    // ---------------------------------------------------------------------------------------
    else if(request.option == 4)
    {
        int year = request.date.year;

        for(int month = 1; month <= 12; ++month)
        {
            int index = month - 1;

            int windCount = CountValidRecords(
                                m_weatherData,
                                &WeatherRecord::HasWindSpeed,
                                month,
                                year);

            if(windCount > 0)
            {
                result.months[index].hasWind = true;

                result.months[index].windAverage = Average(
                                                       m_weatherData,
                                                       &WeatherRecord::GetWindSpeed,
                                                       &WeatherRecord::HasWindSpeed,
                                                       month,
                                                       year);

                result.months[index].windStdDev = StdDev(
                                                      m_weatherData,
                                                      &WeatherRecord::GetWindSpeed,
                                                      &WeatherRecord::HasWindSpeed,
                                                      result.months[index].windAverage,
                                                      month,
                                                      year);
            }

            int tempCount = CountValidRecords(
                                m_weatherData,
                                &WeatherRecord::HasAATemp,
                                month,
                                year);

            if(tempCount > 0)
            {
                result.months[index].hasTemp = true;

                result.months[index].tempAverage = Average(
                                                       m_weatherData,
                                                       &WeatherRecord::GetAATemp,
                                                       &WeatherRecord::HasAATemp,
                                                       month,
                                                       year);

                result.months[index].tempStdDev = StdDev(
                                                      m_weatherData,
                                                      &WeatherRecord::GetAATemp,
                                                      &WeatherRecord::HasAATemp,
                                                      result.months[index].tempAverage,
                                                      month,
                                                      year);
            }

            int solarCount = CountValidSolarRecords(
                                 m_weatherData,
                                 month,
                                 year);

            if(solarCount > 0)
            {
                result.months[index].hasSolar = true;

                result.months[index].solarTotal = SolarRadiationTotal(
                                                      m_weatherData,
                                                      month,
                                                      year);
            }
        }
    }

    // ---------------------------------------------------------------------------------------
    else
    {
        result.validOption = false;
    }

    return result;
}

// ----------------------------------------------
// Helper method that simply counts the number of WeatherRecords that fits the requested month+year combination
int Controller::CountValidRecords(WeatherData& data,
                                  WeatherValidGetter validGetter,
                                  int month, int year)
{
    int count = 0;

    for(int i = 0; i < data.Size(); ++i)
    {
        if(data[i].GetMonth() == month &&
                data[i].GetYear() == year &&
                (data[i].*validGetter)())
        {
            ++count;
        }
    }

    return count;
}

// ----------------------------------------------
// Helper method that simply counts the number of valid SolarRadiation WeatherRecords that fits the requested month+year combination
int Controller::CountValidSolarRecords(WeatherData& data, int month, int year)
{
    int count = 0;

    for(int i = 0; i < data.Size(); ++i)
    {
        if(data[i].GetMonth() == month &&   // chosen month
                data[i].GetYear() == year &&     // chosen year
                data[i].HasSoRad() &&            // has valid records
                data[i].GetSoRad() >= 100)       // above 100w/m2
        {
            ++count;
        }
    }

    return count;
}

// ----------------------------------------------
// helper method to find the total of a certain attribute in WeatherRecord
float Controller::Total(WeatherData& data,
                        WeatherGetter getter,
                        WeatherValidGetter validGetter,
                        int month, int year)
{
    float sum = 0;                  // total sum value

    // add all together
    for (int i = 0; i < data.Size(); ++i)
    {
        // filters for month and year
        if(data[i].GetMonth() == month &&
                data[i].GetYear() == year &&
                (data[i].*validGetter)())
        {
            sum += (data[i].*getter)();
        }
    }

    return sum;
}

// ----------------------------------------------
// helper method to find the average of a certain attribute in WeatherRecord
float Controller::Average(WeatherData& data,
                          WeatherGetter getter,
                          WeatherValidGetter validGetter,
                          int month, int year)
{
    int count = CountValidRecords(data, validGetter, month, year);

    // terminate if vector is empty
    if (count == 0)
    {
        return 0;
    }

    return Total(data, getter, validGetter, month, year) / count;
}

// ----------------------------------------------
// helper method to calculate for standard deviation
float Controller::StdDev(WeatherData& data,
                         WeatherGetter getter,
                         WeatherValidGetter validGetter,
                         float mean, int month, int year)
{

    // terminate if vector is empty or has only one element
    int count = CountValidRecords(data, validGetter, month, year);

    if (count <= 1)
    {
        return 0;
    }

    // calculate the Standard Deviation
    float sum = 0;

    for (int i = 0; i < data.Size(); ++i)
    {
        if(data[i].GetMonth() == month &&
                data[i].GetYear() == year &&
                (data[i].*validGetter)())
        {
            float value = (data[i].*getter)();
            sum += (value - mean) * (value - mean);
        }
    }

    return sqrt(sum / (count - 1));
}

// ----------------------------------------------
// Helper method to find the total Solar Radiation in WeatherRecord
float Controller::SolarRadiationTotal(WeatherData& data, int month, int year)
{
    float total = 0;

    for(int i = 0; i < data.Size(); ++i)
    {
        if(data[i].GetMonth() == month &&
                data[i].GetYear() == year &&
                data[i].HasSoRad() &&
                data[i].GetSoRad() >= 100)               // ignore everything below 100 w/m2
        {
            total += data[i].GetSoRad() / 6000.0;   // metric conversion
        }
    }

    return total;
}


// ----------------------------------------------
// TESTING PURPOSES ONLY
void Controller::TestWeatherTreeMap(ostream& output) const
{
    output << endl << "-- BST/Map Load Test --" << endl;
    output << "Number of year-month BSTs: " << m_weatherTrees.Size() << endl;

    if(m_weatherData.Size() > 0)
    {
        YearMonthKey key = CreateYearMonthKey(m_weatherData[0].GetYear(),
                                              m_weatherData[0].GetMonth());

        const WeatherTree* tree = m_weatherTrees.GetValue(key);

        if(tree != 0)
        {
            output << "First record year-month key: " << key << endl;
            output << "First record found in BST: ";

            if(tree->Search(m_weatherData[0]))
            {
                output << "true" << endl;
            }
            else
            {
                output << "false" << endl;
            }
        }
        else
        {
            output << "Could not retrieve BST for first record." << endl;
        }
    }

    output << "-- End BST/Map Load Test --" << endl << endl;
}
