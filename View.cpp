#include <sstream>
#include <fstream>
#include <iomanip>
#include "View.h"

// Constructor
View::View()
{

}

// ----------------------------------------------
// Display the menu in console
void View::ShowMenu(ostream& output) const
{
    output << endl << endl;
    output << "========== Weather Data Menu ==========" << endl;
    output << "[1] Average wind speed and sample standard deviation for a month/year" << endl;
    output << "[2] Average ambient air temperature and sample standard deviation for each month of a year" << endl;
    output << "[3] Sample Pearson Correlation Coefficient for a month" << endl;
    output << "[4] Output WindTempSolar.csv for a year" << endl;
    output << "[5] Exit" << endl;
    output << "=======================================" << endl;
}

// ----------------------------------------------
// Request for user input and filter
MenuRequest View::GetMenuRequest(istream& input, ostream& output) const
{
    // Create the struct to store the information
    MenuRequest request;

    request.option = 0;
    request.date.month = 0;
    request.date.year = 0;

    // Loops request for option input
    while(!ReadIntLine(input, output, "Enter option: ", request.option))
    {
        output << "Invalid option. Please enter a number." << endl;
    }

    // option 1; if not out of bounds, ask for month and year
    if(request.option == 1)
    {
        // Loop request for month input
        while(!ReadIntLine(input, output, "Enter month: ", request.date.month) ||
                request.date.month < 1 ||
                request.date.month > 12)
        {
            output << "Invalid month. Please enter a value from 1 to 12." << endl;
        }

        // Loop request for year input
        while(!ReadIntLine(input, output, "Enter year: ", request.date.year))
        {
            output << "Invalid year. Please enter a valid year." << endl;
        }
    }

    // option 2 & 4; if not out of bounds, ask for year
    else if(request.option == 2 || request.option == 4)
    {
        // Loop request for year input
        while(!ReadIntLine(input, output, "Enter year: ", request.date.year))
        {
            output << "Invalid year. Please enter a valid year." << endl;
        }
    }
    // option 3; if not out of bounds, ask for month
    else if(request.option == 3)
    {
        // Loop request for month input
        while(!ReadIntLine(input, output, "Enter month: ", request.date.month) ||
                request.date.month < 1 ||
                request.date.month > 12)
        {
            output << "Invalid month. Please enter a value from 1 to 12." << endl;
        }
    }

    return request;
}

// ----------------------------------------------
// Show result of user's inputs and filters
void View::ShowResult(ostream& output, const MenuResult& result) const
{
    // invalid option chosen by user
    if(!result.validOption)
    {
        output << "Invalid option." << endl;
        return;
    }

    if(result.option == 1)
    {
        ShowWindResult(output, result);
    }
    else if(result.option == 2)
    {
        ShowTemperatureYearResult(output, result);
    }
    else if(result.option == 3)
    {
        ShowSPCCResult(output, result);
    }
    else if(result.option == 4)
    {

        if(WriteWindTempSolarFile(result, "WindTempSolar.csv"))
        {
            output << "WindTempSolar.csv has been generated." << endl;
        }
        else
        {
            output << "Error writing WindTempSolar.csv." << endl;
        }

    }
}

// ----------------------------------------------
// Generic show console message
void View::ShowMessage(ostream& output, const string& message) const
{
    output << message << endl;
}

// ----------------------------------------------
// checks input to ensure it is an integer
bool View::ReadIntLine(istream& input, ostream& output, const string& prompt, int& value) const
{
    string line;

    output << prompt;
    getline(input, line);

    stringstream ss(line);

    ss >> value;

    if(ss.fail())
    {
        return false;
    }

    char extra;

    if(ss >> extra)
    {
        return false;
    }

    return true;
}

// ----------------------------------------------
// helper method to convert month in int to string
string View::MonthName(int month) const
{
    switch(month)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "September";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    default:
        return "Invalid";
    }
}

// ----------------------------------------------
// Helper method for displaying Wind Result
void View::ShowWindResult(ostream& output, const MenuResult& result) const
{
    const MonthlyResult& monthResult = result.months[result.month - 1];

    output << endl << MonthName(result.month) << " " << result.year << ":" << endl;

    if(!monthResult.hasWind)
    {
        output << "No Data" << endl;
        return;
    }

    output << "Average speed: " << monthResult.windAverage << " km/h" << endl;
    output << "Sample stdev: " << monthResult.windStdDev << endl;
}

// ----------------------------------------------
// Helper method for displaying Ambient Air Temperature
void View::ShowTemperatureYearResult(ostream& output, const MenuResult& result) const
{
    output << endl << result.year << endl;

    for(int i = 0; i < 12; ++i)
    {
        const MonthlyResult& monthResult = result.months[i];

        output << MonthName(monthResult.month) << ": ";

        if(!monthResult.hasTemp)
        {
            output  << "No Data" << endl;
        }
        else
        {
            output << "average: "
                   << monthResult.tempAverage
                   << " degrees C, stdev: "
                   << monthResult.tempStdDev
                   << endl;
        }
    }
}

// ----------------------------------------------
// Helper method for displaying Solar Radiation (Deprecated)
/*void View::ShowSolarYearResult(ostream& output, const MenuResult& result) const
{
    output<< result.year << endl;

    for(int i = 0; i < 12; ++i)
    {
        const MonthlyResult& monthResult = result.months[i];

        output << MonthName(monthResult.month) << ": ";

        if(!monthResult.hasSolar)
        {
            output << endl << "No Data" << endl;
        }
        else
        {
            output << endl << monthResult.solarTotal << " kWh/m2" << endl;
        }
    }
}*/

// ----------------------------------------------
// Helper method to show SPCC result
void View::ShowSPCCResult(ostream& output, const MenuResult& result) const
{
    output << endl
           << "Sample Pearson Correlation Coefficient for "
           << MonthName(result.month) << endl;

    // std::fixed tells the stream that setprecision only applies after the decimal
    if(result.hasST)
    {
        output << "S_T: " << fixed << setprecision(2) << result.spccST << endl;
    }
    else
    {
        output << "S_T: No Data" << endl;
    }

    if(result.hasSR)
    {
        output << "S_R: " << fixed << setprecision(2) << result.spccSR << endl;
    }
    else
    {
        output << "S_R: No Data" << endl;
    }

    if(result.hasTR)
    {
        output << "T_R: " << fixed << setprecision(2) << result.spccTR << endl;
    }
    else
    {
        output << "T_R: No Data" << endl;
    }
}

// ----------------------------------------------
// Helper method to write into output file
bool View::WriteWindTempSolarFile(const MenuResult& result, const string& filename) const
{
    ofstream ofile(filename.c_str());

    if(!ofile)
    {
        return false;
    }

    ofile << result.year << '\n';
    ofile << fixed << setprecision(1);      // one decimal as per assignment 1 docs

    bool wroteAnyMonth = false;

    for(int i = 0; i < 12; ++i)
    {
        const MonthlyResult& monthResult = result.months[i];

        if(!monthResult.hasWind &&
                !monthResult.hasTemp &&
                !monthResult.hasSolar)
        {
            continue;
        }

        wroteAnyMonth = true;

        ofile << MonthName(monthResult.month) << ",";

        if(monthResult.hasWind)
        {
            ofile << monthResult.windAverage
                  << "("
                  << monthResult.windStdDev
                  << ", "
                  << monthResult.windMad
                  << ")";
        }
        else
        {
            ofile << " ";
        }

        ofile << ",";

        if(monthResult.hasTemp)
        {
            ofile << monthResult.tempAverage
                  << "("
                  << monthResult.tempStdDev
                  << ", "
                  << monthResult.tempMad
                  << ")";
        }
        else
        {
            ofile << " ";
        }

        ofile << ",";

        if(monthResult.hasSolar)
        {
            ofile << monthResult.solarTotal;
        }
        else
        {
            ofile << " ";
        }

        ofile << '\n';
    }

    if(!wroteAnyMonth)
    {
        ofile << "No Data" << '\n';
    }

    return true;
}
