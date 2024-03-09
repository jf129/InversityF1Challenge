#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>

class Weather : public QObject
{
    Q_OBJECT
private:
    double cls_dAirTemp;                                                        // Air temperature (oC)
    double cls_dWindSpeed;                                                      // Wind speed
    int cls_iWindDirection;                                                     // Wind direction (bearing)
    double cls_dTrackTemp;                                                      // Track temperature (oC)
    int cls_iIsRaining;                                                         // 1 if raining, 0 if not
    int cls_iHumidity;                                                          // Humidity (%)
public:
    explicit Weather(QObject *parent = nullptr);                                // Default constructor
    int GetAirTemp();                                                           // Returns air temperature
    int GetWindSpeed();                                                         // Returns wind speed
    int GetWindDirection();                                                     // Returns wind direction
    int GetTrackTemp();                                                         // Returns track temperature
    bool GetIsRaining();                                                        // Returns true if raining, false if not
    void SetData(double p_dAirTemp, double p_dWindSpeed, int p_iWindDirection,  // Sets data relating the the weather
                 double p_dTrackTemp, int p_iIsRaining, int p_iHumidity);

signals:                                                                        // Emitted when specific value changes
    void AirTempChanged(double p_dAirTemp);
    void WindSpeedChanged(double p_dWindSpeed);
    void WindDirectionChanged(int p_iWindDirection);
    void TrackTempChanged(double p_dTrackTemp);
    void IsRainingChanged(int p_iIsRaining);
    void HumidityChanged(int p_iHumidity);
};

#endif // WEATHER_H
