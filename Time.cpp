#include "Time.h"

Time::Time()
{
    m_hour = 0;
    m_minute = 0;
}

Time::Time(int h, int m)
{
    m_hour = h;
    m_minute = m;
}

int Time::GetHour() const
{
    return m_hour;
}

int Time::GetMinute() const
{
    return m_minute;
}

void Time::SetHour(int h)
{
    m_hour = h;
}

void Time::SetMinute(int m)
{
    m_minute = m;
}
