#include "WeatherRecord.h"
#include "Date.h"
#include "Time.h"

WeatherRecord::WeatherRecord()
{
    m_speed = 0;
    m_aatemp = 0;
    m_sorad = 0;

    m_hasWindSpeed = false;
    m_hasAATemp = false;
    m_hasSoRad = false;
}

WeatherRecord::WeatherRecord(int year, int month, int day, int hour, int minute,
                             float windspeed, float temp, float rad,
                             bool hasWindSpeed, bool hasAATemp, bool hasSoRad)
{
    m_date.SetYear(year);
    m_date.SetMonth(month);
    m_date.SetDay(day);

    m_time.SetHour(hour);
    m_time.SetMinute(minute);

    m_speed = windspeed * 3.6;
    m_aatemp = temp;
    m_sorad = rad;

    m_hasWindSpeed = hasWindSpeed;
    m_hasAATemp = hasAATemp;
    m_hasSoRad = hasSoRad;
}

int WeatherRecord::GetYear() const
{
    return m_date.GetYear();
}

int WeatherRecord::GetMonth() const
{
    return m_date.GetMonth();
}

int WeatherRecord::GetDay() const
{
    return m_date.GetDay();
}

int WeatherRecord::GetHour() const
{
    return m_time.GetHour();
}

int WeatherRecord::GetMinute() const
{
    return m_time.GetMinute();
}

float WeatherRecord::GetWindSpeed() const
{
    return m_speed;
}

float WeatherRecord::GetAATemp() const
{
    return m_aatemp;
}

float WeatherRecord::GetSoRad() const
{
    return m_sorad;
}

bool WeatherRecord::HasWindSpeed() const
{
    return m_hasWindSpeed;
}

bool WeatherRecord::HasAATemp() const
{
    return m_hasAATemp;
}

bool WeatherRecord::HasSoRad() const
{
    return m_hasSoRad;
}

void WeatherRecord::SetDate(int year, int month, int day)
{
    m_date.SetYear(year);
    m_date.SetMonth(month);
    m_date.SetDay(day);
}

void WeatherRecord::SetTime(int hour, int minute)
{
    m_time.SetHour(hour);
    m_time.SetMinute(minute);
}

void WeatherRecord::SetWindSpeed(float ws)
{
    m_speed = ws * 3.6;
    m_hasWindSpeed = true;
}

void WeatherRecord::SetAatemp(float aatemp)
{
    m_aatemp = aatemp;
    m_hasAATemp = true;
}

void WeatherRecord::SetSoRad(float sorad)
{
    m_sorad = sorad;
    m_hasSoRad = true;
}
