#ifndef RACETHREAD_H
#define RACETHREAD_H

#include "weather.h"
#include "car.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QThread>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class RaceThread : public QThread
{
    Q_OBJECT
private:
    Weather* cls_objWeather;                                // Class pointer to Weather object
    QVector<Car*> cls_objCars;                              // Vector holding pointers to all Car objects
    int cls_iMonitoredCar;                                  // Vector index of Car object being monitored
    void APIRequest(QString p_strURL);                      // Requests data from specified URL
    void SetWeatherData();                                  // Sets data relating to the weather
    QNetworkAccessManager cls_NetworkManager;               // Class object of QNetworkAccessManager for requesting from web page
    QNetworkReply* cls_Reply;                               // Pointer to reply from web page
    QJsonArray cls_Results;                                 // Data requested from web page in Json format after being parsed
    void InitialiseCars();                                  // Initialises all cars in race
    void SetCarData();                                      // Sets data relating to each car
public:
    RaceThread();                                           // Default constructor
    Weather* GetWeatherPoint();                             // Returns a pointer to the Weather object in order to connect signals to slots
    Car* GetCarPoint();                                     // Returns a pointer to the monitored Car object in order to connect signals to slots
    void run() override;                                    // Function that is run in alternate thread to handle the updating of real-time data
public slots:
    void ParseData();                                       // Parses reply from web page in Json format
    void CalculatePit();                                    // Calculates when the monitored car should pit
signals:                                                    // Emitted when specific value changes
    void PitUrgencyChanged(int p_iUrgency);
};

#endif // RACETHREAD_H
