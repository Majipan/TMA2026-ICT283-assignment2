#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

//---------------------------------------------------------------------------------

#include <iostream>

//---------------------------------------------------------------------------------

/**
 * @class Date
 * @brief Date class to store date information in a modular form
 *
 * Keeps track of the Year, Month and Day in a suitable data structure such that it is modular
 *
 * @author Li Weihao
 * @version 01
 * @date 30/05/2026 Weihao Started
 */

class Date
{
public:
    Date();
    Date(int year, int month, int day);

    // Getters ----------
    /**
     * @brief   Retrieves the Year this unit is marked
     * @return  int - Year this unit is marked
     */
    int GetYear() const;

    /**
     * @brief   Retrieves the Month this unit is marked
     * @return  int - Month this unit is marked
     */
    int GetMonth() const;

    /**
     * @brief   Retrieves the Day this unit is marked
     * @return  int - Day this unit is marked
     */
    int GetDay() const;

    // Setters ----------
    /**
     * @brief   Sets the Year this unit is marked
     * @param   year - the Year this unit is marked
     * @return  void
     */
    void SetYear(const int year);

    /**
     * @brief   Sets the Month this unit is marked
     * @param   month - the Month this unit is marked
     * @return  void
     */
    void SetMonth(const int month);

    /**
     * @brief   Sets the Day this unit is marked
     * @param   day - the Day this unit is marked
     * @return  void
     */
    void SetDay(const int day);

    /**
     * @brief   Operator < override to compare dates
     * @param   other - the other date to compare with
     */
    bool operator<(const Date& other) const;

private:
    /// Year when the Unit was marked
    int m_year;
    /// Month when the Unit was marked
    int m_month;
    /// Day when the Unit was marked
    int m_day;
};

std::ostream& operator<<(std::ostream& os, const Date& date);

#endif // DATE_H_INCLUDED
