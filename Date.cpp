#include "Date.h"

Date::Date()
{
    m_year = 0;
    m_month = 0;
    m_day = 0;
}

Date::Date(int year, int month, int day)
{
    m_year = year;
    m_month = month;
    m_day = day;
}

// Getters
int Date::GetYear() const
{
    return m_year;
}

int Date::GetMonth() const
{
    return m_month;
}

int Date::GetDay() const
{
    return m_day;
}

// Setters
void Date::SetYear(const int year)
{
    m_year = year;
}

void Date::SetMonth(const int month)
{
    m_month = month;
}

void Date::SetDay(const int day)
{
    m_day = day;
}

bool Date::operator<(const Date& other) const
{
    if (m_year < other.m_year)
    {
        return true;
    }
    else if (m_year > other.m_year)
    {
        return false;
    }

    if (m_month < other.m_month)
    {
        return true;
    }
    else if (m_month > other.m_month)
    {
        return false;
    }

    return m_day < other.m_day;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.GetDay() << "/"
       << date.GetMonth() << "/"
       << date.GetYear();

    return os;
}
