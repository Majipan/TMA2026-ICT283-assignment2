#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

//---------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include "View.h"
#include "Vector.h"
#include "Bst.h"
#include "Map.h"
#include "WeatherRecord.h"

//---------------------------------------------------------------------------------

typedef Vector<WeatherRecord> WeatherData;
typedef float (WeatherRecord::*WeatherGetter)() const;
typedef bool (WeatherRecord::*WeatherValidGetter)() const;
typedef int YearMonthKey;
typedef Bst<WeatherRecord> WeatherTree;
typedef Map<YearMonthKey, WeatherTree> WeatherTreeMap;

//---------------------------------------------------------------------------------

/**
 * @class Controller
 * @brief Controller for the application
 *
 * @author Li Weihao
 * @version 01
 * @date 14/06/2026 Weihao Started
 */


class Controller
{
public:
    Controller();

    /**
     * @brief
     * @param   input - Input stream
     * @param   output - Output stream
     */
    void Run(istream& input, ostream& output);

private:
    /// Collection of weather records loaded from the data file
    WeatherData m_weatherData;
    /// Map that stores one balanced BST for each year-month key
    WeatherTreeMap m_weatherTrees;
    /// MVC; Console for input and output
    View m_view;

    /**
     * @brief   Loads all CSV files listed in data/data_source.txt
     * @return  bool - true if all listed files were loaded successfully
     */
    bool LoadSources();

    /**
     * @brief   Loads the data file
     * @param   source - directory to the csv data file
     */
    bool Load(string source);

    /**
     * @brief   Helper method that trims leading & trailing spaces / return / line break
     * @param   value - String to be trimmed
     * @return  string - trimmed value
     */
    string Trim(const string& value);

    /**
     * @brief   Helper method to find the column index based on column name
     * @param   headerLine - entire row of the column header from csv
     * @param   columnName - name of the column header whose index this method is locating
     * @return  int - column index
     */
    int GetColumnIndex(const string& headerLine, const string& columnName);

    /**
     * @brief   Helper method to extract the value from the data row
     * @param   line - single row of data from csv
     * @param   targetIndex - index of the column to extract data from
     * @param   row - a vector used to store a row of data from the CSV
     * @return  int - column index
     */
    bool GetLineRecord(const string& line, Vector<string>& row);

    /**
     * @brief   Helper method to check if the parsing from string to float will work and if the result is a number
     * @param   value - the original string to parse
     * @param   number - the result to be saved into the original var
     * @return  bool - pass/fail
     */
    bool TryParseFloat(const string& value, float& number);

    /**
     * @brief   Helper method to extract the value from the data row
     * @param   wast - raw date and time string
     * @param   year - Year reference
     * @param   month - Month reference
     * @param   day - Day reference
     * @param   hour - Hour reference
     * @param   minute - Minute reference
     * @return  bool - success / fail
     */
    bool ConvertWast(
        const string& wast,
        int& year,
        int& month,
        int& day,
        int& hour,
        int& minute);

    /**
     * @brief   A single record to be inserted into the map
     * @param   key - YYYYMM
     * @param   records - WeatherData class for a single weather record
     */
    struct MonthBucket
    {
        YearMonthKey key;
        WeatherData records;
    };

    /**
     * @brief   Creates a year-month key in YYYYMM format
     * @param   year The record year
     * @param   month The record month
     * @return  Integer key in YYYYMM format
     */
    YearMonthKey CreateYearMonthKey(int year, int month) const;

    /**
     * @brief   Finds the index of a month bucket
     * @param   buckets - a collection of month buckets
     * @param   key - the year-month key to find
     * @return  Index of the bucket if found, otherwise -1
     */
    int FindMonthBucketIndex(const Vector<MonthBucket>& buckets,
                             YearMonthKey key) const;

    /**
     * @brief   Adds a weather record into the correct temporary month bucket
     * @param   buckets The temporary month buckets
     * @param   record The weather record to add
     */
    void AddRecordToMonthBucket(Vector<MonthBucket>& buckets,
                                const WeatherRecord& record) const;

    /**
     * @brief   Removes duplicate weather records from a sorted WeatherData vector
     * @param   records The sorted weather records
     */
    void RemoveDuplicateRecords(WeatherData& records) const;

    /**
     * @brief   Builds all balanced monthly BSTs and stores them in the Map
     */
    void BuildWeatherTrees();

    /**
     * @brief   Inserts sorted records into a BST in balanced order
     * @param   records The sorted unique records
     * @param   left Left index
     * @param   right Right index
     * @param   tree The BST being built
     */
    void BalancedInsert(const WeatherData& records,
                        int left,
                        int right,
                        WeatherTree& tree) const;

    /**
     * @param   output Output stream
     * @brief   Temporary test to check that records were inserted into Map and BST
     */
    void TestWeatherTreeMap(ostream& output) const;

    /**
     * @brief   Main method to process a request from the user input
     * @param   request - Struct for the request
     * @return  MenuResult - Result from the user input
     */
    MenuResult ProcessRequest(const MenuRequest& request);

    /**
     * @brief   Helper method to count how many rows of data would there be based on user's inputs
     * @param   data - reference of m_weatherData
     * @param   month - Chosen month
     * @param   year - Chosen year
     * @return  int - Total valid counts
     */
    int CountValidRecords(WeatherData& data, WeatherValidGetter validGetter, int month, int year);

    /**
     * @brief   Helper method to count how many rows of data would there be based on user's inputs
     * @param   data - reference of m_weatherData
     * @param   month - Chosen month
     * @param   year - Chosen year
     * @return  int - Total valid counts
     */
    int CountValidSolarRecords(WeatherData& data, int month, int year);

    /**
     * @brief   Helper method to find the Total of a column in WeatherRecord
     * @param   data - reference of m_weatherData
     * @param   getter - pointer to a Getter function
     * @return  float - Total of a column in WeatherRecord
     */
    float Total(WeatherData& data, WeatherGetter getter, WeatherValidGetter validGetter, int month, int year);

    /**
     * @brief   Helper method to find the Average of a column in WeatherRecord
     * @param   data - reference of m_weatherData
     * @param   getter - pointer to a Getter function
     * @return  float - Average of a column in WeatherRecord
     */
    float Average(WeatherData& data, WeatherGetter getter, WeatherValidGetter validGetter, int month, int year);

    /**
     * @brief   Helper method to find the standard deviation of a column in WeatherRecord
     * @param   data - reference of m_weatherData
     * @param   getter - pointer to a Getter function
     * @param   mean - average of a column in WeatherRecord
     * @return  float - Standard Deviation of a column in WeatherRecord
     */
    float StdDev(WeatherData& data, WeatherGetter getter, WeatherValidGetter validGetter, float mean, int month, int year);

    /**
     * @brief   Helper method to find the total Solar Radiation in WeatherRecord
     * @param   data - reference of m_weatherData
     * @param   month - month chosen to lookup
     * @param   year - year chosen to lookup
     * @return  float - total solar radiation
     */
    float SolarRadiationTotal(WeatherData& data, int month, int year);
};

#endif // CONTROLLER_H_INCLUDED
