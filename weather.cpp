#include "weather.h"

using namespace std;

Weather::Weather(QObject* parent): QObject(parent)
{
    this->cls_dAirTemp = 0;
    this->cls_dWindSpeed = 0;
    this->cls_iWindDirection = 0;
    this->cls_dTrackTemp = 0;
    this->cls_iIsRaining = 0;
}

Weather::~Weather()
{

}

void Weather::SetData(double p_dAirTemp, double p_dWindSpeed, int p_iWindDirection, double p_dTrackTemp, int p_iIsRaining, int p_iHumidity)
{
    if (this->cls_dAirTemp != p_dAirTemp)
    {
        this->cls_dAirTemp = p_dAirTemp;
        emit AirTempChanged(this->cls_dAirTemp);
    }
    if (this->cls_dWindSpeed != p_dWindSpeed)
    {
        this->cls_dWindSpeed = p_dWindSpeed;
        emit WindSpeedChanged(this->cls_dWindSpeed);
    }
    if (this->cls_iWindDirection != p_iWindDirection)
    {
        this->cls_iWindDirection = p_iWindDirection;
        emit WindDirectionChanged(this->cls_iWindDirection);
    }
    if (this->cls_dTrackTemp != p_dTrackTemp)
    {
        this->cls_dTrackTemp = p_dTrackTemp;
        emit TrackTempChanged(this->cls_dTrackTemp);
    }
    if (this->cls_iIsRaining != p_iIsRaining)
    {
        this->cls_iIsRaining = p_iIsRaining;
        emit IsRainingChanged(this->cls_iIsRaining);
    }
    if (this->cls_iHumidity != p_iHumidity)
    {
        this->cls_iHumidity = p_iHumidity;
        emit HumidityChanged(this->cls_iHumidity);
    }
}

int Weather::GetAirTemp()
{
    return this->cls_dAirTemp;
}

int Weather::GetWindSpeed()
{
    return this->cls_dWindSpeed;
}

int Weather::GetWindDirection()
{
    return this->cls_iWindDirection;
}

int Weather::GetTrackTemp()
{
    return this->cls_dTrackTemp;
}

bool Weather::GetIsRaining()
{
    return this->cls_iIsRaining;
}
