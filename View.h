#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

//---------------------------------------------------------------------------------

#include <iostream>
#include <string>

//---------------------------------------------------------------------------------

using namespace std;

//---------------------------------------------------------------------------------

struct MonthYear
{
    int month;
    int year;
};

struct MenuRequest
{
    int option;
    MonthYear date;
};

struct MonthlyResult
{
    int month;

    bool hasWind;
    float windAverage;
    float windStdDev;
    float windMad;

    bool hasTemp;
    float tempAverage;
    float tempStdDev;
    float tempMad;

    bool hasSolar;
    float solarTotal;
};

struct MenuResult
{
    int option;
    int month;
    int year;

    MonthlyResult months[12];

    bool hasST;
    bool hasSR;
    bool hasTR;

    double spccST;
    double spccSR;
    double spccTR;

    bool validOption;
};

//---------------------------------------------------------------------------------

/**
 * @class View
 * @brief View for the application
 *
 * @author Li Weihao
 * @version 01
 * @date 16/06/2026 Weihao Started
 */

class View
{
public:
    View();

    /**
     * @brief   Shows the user menu
     * @param   output - cout to the ostream
     */
    void ShowMenu(ostream& output) const;

    /**
     * @brief   Requests for input
     * @param   input - Input stream to request for input
     * @param   output - output stream
     * @return  MenuRequest - Struct that contains the user inputs
     */
    MenuRequest GetMenuRequest(istream& input, ostream& output) const;

    /**
     * @brief   Shows results based on the user's inputs
     * @param   output - The output stream
     * @param   result - Result from the WeatherRecords based on the user's filters
     */
    void ShowResult(ostream& output, const MenuResult& result) const;

    /**
     * @brief   Generic output function
     * @param   output - The output stream
     * @param   message - The message to be printed into console
     */
    void ShowMessage(ostream& output, const string& message) const;

private:
    /**
     * @brief   Checks whether the input is an integer
     * @param   input - The input stream
     * @param   output - The output stream
     * @param   prompt - The message
     * @param   value - Saved value from the input
     * @return  bool - To indicate pass or fail
     */
    bool ReadIntLine(istream& input, ostream& output, const string& prompt, int& value) const;

    /**
     * @brief   Helper method to convert month in int to string
     * @param   month - Int for the month to be converted
     * @return  string - The month converted to string
     */
    string MonthName(int month) const;

    /**
     * @brief   Helper method for displaying Wind Result
     * @param   output - The output stream
     * @param   result - result from the controller class to be formatted
     */
    void ShowWindResult(ostream& output, const MenuResult& result) const;

    /**
     * @brief   Helper method for displaying Ambient Air Temperature
     * @param   output - The output stream
     * @param   result - result from the controller class to be formatted
     */
    void ShowTemperatureYearResult(ostream& output, const MenuResult& result) const;

    /**
     * @brief   Helper method for displaying Solar Radiation (deprecated)
     * @param   output - The output stream
     * @param   result - result from the controller class to be formatted
     */
    //void ShowSolarYearResult(ostream& output, const MenuResult& result) const;

    /**
     * @brief   Helper method for displaying the SPCC result
     * @param   output - The output stream
     * @param   result - result from the controller class to be formatted
     */
    void ShowSPCCResult(ostream& output, const MenuResult& result) const;

    /**
     * @brief   Writes option 4 result to WindTempSolar.csv
     * @param   result - calculated monthly result from Controller
     * @param   filename - output CSV file name
     * @return  bool - true if file was written successfully
     */
    bool WriteWindTempSolarFile(const MenuResult& result, const string& filename) const;
};

#endif // VIEW_H_INCLUDED
