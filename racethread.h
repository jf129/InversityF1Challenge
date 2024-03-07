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
    Weather* cls_objWeather;
    QVector<Car*> cls_objCars;
    int cls_iMonitoredCar;
    void APIRequest(QString p_strURL);
    void SetWeatherData();
    //QNetworkAccessManager cls_NetworkManager;
    QNetworkReply* cls_Reply;
    QJsonArray cls_Results;
    void InitialiseCars();
    void SetCarData();
public:
    RaceThread();
    Weather* GetWeatherPoint();
    Car* GetCarPoint();
    void run() override;
public slots:
    void ParseData();
    void CalculatePit();
signals:
    void PitUrgencyChanged(int p_iUrgency);
};

#endif // RACETHREAD_H
