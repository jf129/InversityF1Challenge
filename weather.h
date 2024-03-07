#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>

class Weather : public QObject
{
    Q_OBJECT
private:
    double cls_dAirTemp;
    double cls_dWindSpeed;
    int cls_iWindDirection;
    double cls_dTrackTemp;
    int cls_iIsRaining;
    int cls_iHumidity;
public:
    explicit Weather(QObject *parent = nullptr);
    ~Weather();
    int GetAirTemp();
    int GetWindSpeed();
    int GetWindDirection();
    int GetTrackTemp();
    bool GetIsRaining();
    void SetData(double p_dAirTemp, double p_dWindSpeed, int p_iWindDirection, double p_dTrackTemp, int p_iIsRaining, int p_iHumidity);

signals:
    void AirTempChanged(double p_dAirTemp);
    void WindSpeedChanged(double p_dWindSpeed);
    void WindDirectionChanged(int p_iWindDirection);
    void TrackTempChanged(double p_dTrackTemp);
    void IsRainingChanged(int p_iIsRaining);
    void HumidityChanged(int p_iHumidity);
};

#endif // WEATHER_H
