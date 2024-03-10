#include "racethread.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

using namespace std;

RaceThread::RaceThread()
{
    this->cls_iMonitoredCar = 0;
    this->cls_objWeather = new Weather();
    this->cls_Reply = nullptr;
    this->InitialiseCars();
}

Weather* RaceThread::GetWeatherPoint()
{
    return this->cls_objWeather;                                        // Returns pointer to weather object
}

Car* RaceThread::GetCarPoint()
{
    return this->cls_objCars[this->cls_iMonitoredCar];                  // Returns pointer to monitored Car object
}

void RaceThread::run()                                                  // Loop that runs in a separate thread to the main events
{
    while (true)
    {
        this->SetWeatherData();                                         // Sets weather data
        this->SetCarData();                                             // Sets car data
    }
}

void RaceThread::APIRequest(QString p_strURL)
{
    // Requests data from given web page
    connect(&this->cls_NetworkManager, &QNetworkAccessManager::finished, this, &RaceThread::ParseData);   // When data has been requested it will automatically be parsed
    const QUrl l_URL = QUrl(p_strURL);
    QNetworkRequest l_Request(l_URL);
    this->cls_Reply = this->cls_NetworkManager.get(l_Request);
}

void RaceThread::ParseData()
{
    // Parses data recieved from web page and sets the parsed data to the class variable
    QByteArray l_Data = this->cls_Reply->readAll();
    QJsonDocument l_JsonDoc = QJsonDocument::fromJson(l_Data);
    this->cls_Results = l_JsonDoc[""].toArray();
}

void RaceThread::InitialiseCars()
{
    this->APIRequest("https://api.openf1.org/v1/drivers?&session_key=latest");
    QJsonObject l_Entry;
    Car* l_ptrCar;

    for (int i = 0; i < this->cls_Results.count(); i++)
    {
        l_Entry = this->cls_Results[i].toObject();

        l_ptrCar = new Car(nullptr, l_Entry["driver_number"].toInt());

        this->cls_objCars.append(l_ptrCar);

        if (l_Entry["driver_number"].toInt() == 44)     // Change to take user input to choose which driver to monitor, hardcoded for now
        {
            this->cls_iMonitoredCar = i;
        }
    }
}

void RaceThread::SetWeatherData()
{
    this->APIRequest("https://api.openf1.org/v1/weather?meeting_key=latest");

    QJsonObject l_Entry = this->cls_Results[this->cls_Results.count() - 1].toObject();

    double l_dAirTemp = l_Entry["air_temperature"].toDouble();
    double l_dWindSpeed = l_Entry["wind_speed"].toDouble();
    double l_dWindDirection = l_Entry["wind_direction"].toDouble();
    double l_dTrackTemp = l_Entry["track_temperature"].toDouble();
    int l_iIsRaining = l_Entry["rainfall"].toInt();
    int l_iHumidity = l_Entry["Humidity"].toInt();

    this->cls_objWeather->SetData(l_dAirTemp, l_dWindSpeed, l_dWindDirection, l_dTrackTemp, l_iIsRaining, l_iHumidity);
}

void RaceThread::SetCarData()
{
    QJsonObject l_Entry;
    QString l_strRequest;
    string l_strTempStr;
    int l_iLapNum = 0;
    bool l_bOutOfPit = false;
    double l_dLapTime = 0;
    double l_dS1Time = 0;
    double l_dS2Time = 0;
    double l_dS3Time = 0;
    int l_iIsBrake = 0;
    int l_iPosition = 0;

    for (int i = 0; i < this->cls_objCars.count(); i++)
    {
        l_strTempStr = "https://api.openf1.org/v1/laps?session_key=latest&driver_number=" + to_string(this->cls_objCars[i]->GetDriverNumber());
        l_strRequest = QString::fromStdString(l_strTempStr);
        this->APIRequest(l_strRequest);
        l_Entry = this->cls_Results[this->cls_Results.count() - 1].toObject();

        l_iLapNum = l_Entry["lap_number"].toInt();
        l_bOutOfPit = l_Entry["is_pit_out_lap"].toBool();
        l_dLapTime = l_Entry["lap_duration"].toDouble();
        l_dS1Time = l_Entry["duration_sector_1"].toDouble();
        l_dS2Time = l_Entry["duration_sector_2"].toDouble();
        l_dS3Time = l_Entry["duration_sector_3"].toDouble();

        l_strTempStr = "https://api.openf1.org/v1/car_data?session_key=latest&driver_number=" + to_string(this->cls_objCars[i]->GetDriverNumber());
        l_strRequest = QString::fromStdString(l_strTempStr);
        this->APIRequest(l_strRequest);
        l_Entry = this->cls_Results[this->cls_Results.count() - 1].toObject();

        l_iIsBrake = l_Entry["brake"].toInt();

        l_strTempStr = "https://api.openf1.org/v1/position?session_key=latest&driver_number=" + to_string(this->cls_objCars[i]->GetDriverNumber());
        l_strRequest = QString::fromStdString(l_strTempStr);
        this->APIRequest(l_strRequest);
        l_Entry = this->cls_Results[this->cls_Results.count() - 1].toObject();

        l_iPosition = l_Entry["position"].toInt();

        this->cls_objCars[i]->SetData(l_iLapNum, l_bOutOfPit, l_dLapTime, l_dS1Time, l_dS2Time, l_dS3Time, l_iIsBrake, l_iPosition);
    }
}

void RaceThread::CalculatePit()
{
    // Calculate average percentage lap time decrease
    int l_iUrcency = this->cls_objCars[this->cls_iMonitoredCar]->GetPitUrgency();
    emit PitUrgencyChanged(l_iUrcency);
}
