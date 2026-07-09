#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

//---------------------------------------------------------------------------------

#include <iostream>

//---------------------------------------------------------------------------------

/**
 * @class Time
 * @brief Time class to store time information in a modular form
 *
 * Keeps track of the Hour and Mins in a suitable data structure such that it is modular
 *
 * @author Li Weihao
 * @version 01
 * @date 14/06/2026 Weihao Started
 */

 class Time
 {
 public:
    Time();
    Time(int h, int m);

    // Getters ----------
    /**
     * @brief   Retrieves the Hour
     * @return  int - Hour
     */
    int GetHour() const;

    /**
     * @brief   Retrieves the Minutes
     * @return  int - Minutes
     */
    int GetMinute() const;

    // Setters ----------
    /**
     * @brief   Sets the Hour
     * @return  int - Hour
     */
    void SetHour(int h);

    /**
     * @brief   Sets the Minutes
     * @return  int - Minutes
     */
    void SetMinute(int m);

 private:
    /// Hour
    int m_hour;
    /// Minutes
    int m_minute;
 };

#endif // TIME_H_INCLUDED
