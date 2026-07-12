#ifndef WEATHERRECORD_H_INCLUDED
#define WEATHERRECORD_H_INCLUDED
#include "Date.h"
#include "Time.h"

using namespace std;


// ----------------------------------------------

/**
 * @class WeatherRecord
 * @brief Class to hold a single weather record
 *
 * @author Li Weihao
 * @version 01
 * @date 15/06/2026 Weihao Started
 */

class WeatherRecord
{
public:
    /**
     * @brief   Constructor
     */
    WeatherRecord();

    /**
     * @brief   Constructor Overload
     * @param   year - Date year
     * @param   month - Date month
     * @param   day - Date day
     * @param   hour - Time hour
     * @param   minute - Time minute
     * @param   windspeed - Wind Speed
     * @param   aatemp - Ambient Air Temperature
     * @param   sorad - Solar Radiation
     */
    WeatherRecord(int year, int month, int day, int hour, int minute,
                  float windspeed, float aatemp, float sorad,
                  bool hasWindSpeed, bool hasAATemp, bool hasSoRad);

    /**
     * @brief   Getter for Year
     * @return  int - Year in int format
     */
    int GetYear() const;

    /**
     * @brief   Getter for Month
     * @return  int - Month in int format
     */
    int GetMonth() const;

    /**
     * @brief   Getter for Day
     * @return  int - Day in int format
     */
    int GetDay() const;

    /**
     * @brief   Getter for Hour
     * @return  int - Hour in int format
     */
    int GetHour() const;

    /**
     * @brief   Getter for Minute
     * @return  int - Minute in int format
     */
    int GetMinute() const;

    /**
     * @brief   Getter for Wind Speed in float
     * @return  float - Wind Speed (km/h) in float
     */
    float GetWindSpeed() const;

    /**
     * @brief   Getter for Ambient Air Temperature in int
     * @return  int - Ambient Air Temperature in float
     */
    float GetAATemp() const;

    /**
     * @brief   Getter for Solar Radiation in float
     * @return  float - Solar Radiation in float
     */
    float GetSoRad() const;

    /**
     * @brief   Getter for Wind Speed present in record
     * @return  bool - Wind Speed (km/h) present in record
     */
    bool HasWindSpeed() const;

    /**
     * @brief   Getter for Ambient Air Temperature present in record
     * @return  int - Ambient Air Temperature present in record
     */
    bool HasAATemp() const;

    /**
     * @brief   Getter for Solar Radiation present in record
     * @return  float - Solar Radiation present in record
     */
    bool HasSoRad() const;

    /**
     * @brief   Setter for Date type
     * @param   year - int containing year
     * @param   month - int containing month
     * @param   day - int containing day
     */
    void SetDate(int year, int month, int day);

    /**
     * @brief   Setter for Date type
     * @param   hour - int containing hour
     * @param   minute - int containing minute
     */
    void SetTime(int hour, int minute);

    /**
     * @brief   Setter for Wind Speed in float
     * @param   ws - float containing Wind Speed
     */
    void SetWindSpeed(float ws);

    /**
     * @brief   Setter for Ambient Air Temperature in float
     * @param   aatemp - float containing Ambient Air Temperature
     */
    void SetAatemp(float aatemp);

    /**
     * @brief   Setter for Solar Radiation in float
     * @param   sorad - float containing Solar Radiation
     */
    void SetSoRad(float sorad);

    /**
     * @brief   To help compare between records used for sorting
     * @param   other - other weather record
     * @return  return true if this record is larger than the other
     */
    bool operator<(const WeatherRecord& other) const;

    /**
     * @brief   To help compare between records used for sorting
     * @param   other - other weather record
     * @return  return true if this record the same as the other
     */
    bool operator==(const WeatherRecord& other) const;

    /**
     * @brief   To help compare between records used for sorting
     * @return  return YYYYMMDDHHMM (202603310930)
     */
    long long GetDateTimeKey() const;


private:
    /// Date class to store a single date in int
    Date m_date;
    /// Time class to store a single time in int
    Time m_time;
    /// Windspeed
    float m_speed;
    /// Ambient Air Temperature
    float m_aatemp;
    /// Solar Radiation
    float m_sorad;
    /// Indicator if theres wind speed in this record
    bool m_hasWindSpeed;
    /// Indicator if theres ambient air temperature in this record
    bool m_hasAATemp;
    /// Indicator if theres solar radiation in this record
    bool m_hasSoRad;
};

#endif // WEATHERRECORD_H_INCLUDED
