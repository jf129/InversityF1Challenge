#include "dashboard.h"
#include "./ui_dashboard.h"
#include <QStyleOptionFrame>

using namespace std;

Dashboard::Dashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    this->cls_objRaceThread = new RaceThread();                                                     //  Creates RaceThread object

    this->cls_ptrWeather = this->cls_objRaceThread->GetWeatherPoint();                              // Sets Weather pointer
    //this->cls_ptrCar = this->cls_objRaceThread->GetCarPoint();                                    // Sets Car pointer

    // Connects signals from weather to slots
    connect(this->cls_ptrWeather, &Weather::AirTempChanged, this, &Dashboard::ChangeAirTemp);
    connect(this->cls_ptrWeather, &Weather::WindSpeedChanged, this, &Dashboard::ChangeAirTemp);
    connect(this->cls_ptrWeather, &Weather::WindDirectionChanged, this, &Dashboard::ChangeAirTemp);
    connect(this->cls_ptrWeather, &Weather::TrackTempChanged, this, &Dashboard::ChangeAirTemp);
    connect(this->cls_ptrWeather, &Weather::IsRainingChanged, this, &Dashboard::ChangeAirTemp);
    connect(this->cls_ptrWeather, &Weather::HumidityChanged, this, &Dashboard::ChangeHumidity);

    // Connects signals from car to slots
    /*connect(this->cls_ptrCar, &Car::LapNumChanged, this, &Dashboard::ChangeLapNum);
    connect(this->cls_ptrCar, &Car::AddLapTime, this, &Dashboard::AddLapTime);
    connect(this->cls_ptrCar, &Car::AddSectorTimes, this, &Dashboard::AddSectorTimes);
    connect(this->cls_ptrCar, &Car::BrakeChanged, this, &Dashboard::ChangeBrake);
    connect(this->cls_ptrCar, &Car::PositionChanged, this, &Dashboard::ChangePosition);
    connect(this->cls_ptrCar, &Car::LapPctChanged, this, &Dashboard::ChangeLapPct);
    connect(this->cls_ptrCar, &Car::S1PctChanged, this, &Dashboard::ChangeS1Pct);
    connect(this->cls_ptrCar, &Car::S2PctChanged, this, &Dashboard::ChangeS2Pct);
    connect(this->cls_ptrCar, &Car::S3PctChanged, this, &Dashboard::ChangeS3Pct);*/

    this->InitGraph();

    this->cls_objRaceThread->start();                   // Start separate thread to get data from API and update GUI
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::InitGraph()
{
    // Initialises graph that displays lap and sector times
}

// ******************************************************************************************
// Slots that change the relevant GUI elements depending on which value changes

void Dashboard::ChangeAirTemp(double p_dAirTemp)
{
    ui->lblAirTempVal->setText(QString::number(p_dAirTemp));
    ui->sldAirTempSlide->setValue(p_dAirTemp);

    if (p_dAirTemp >= 40)
    {
        ui->frmAirTempCol->setStyleSheet("background-colour: rgb(255, 0, 0");
    }
    else if (p_dAirTemp >= 30)
    {
        ui->frmAirTempCol->setStyleSheet("background-colour: rgb(255, 128, 0");
    }
    else
    {
        ui->frmAirTempCol->setStyleSheet("background-colour: rgb(0, 255, 0");
    }
}

void Dashboard::ChangeWindSpeed(double p_dWindSpeed)
{
    ui->lblWindSpeedVal->setText(QString::number(p_dWindSpeed));
    ui->sldWindSpeedSlide->setValue(p_dWindSpeed);

    if (p_dWindSpeed >= 20)
    {
        ui->frmWindSpeedCol->setStyleSheet("background-colour: rgb(255, 0, 0");
    }
    else if (p_dWindSpeed >= 10)
    {
        ui->frmWindSpeedCol->setStyleSheet("background-colour: rgb(255, 128, 0");
    }
    else
    {
        ui->frmWindSpeedCol->setStyleSheet("background-colour: rgb(0, 255, 0");
    }
}

void Dashboard::ChangeWindDirection(double p_dWindDirection)
{
    ui->lblWindDirectionVal->setText(QString::number(p_dWindDirection));
}

void Dashboard::ChangeTrackTemp(double p_dTrackTemp)
{
    ui->lblTrackTempVal->setText(QString::number(p_dTrackTemp));
    ui->sldTrackTempSlide->setValue(p_dTrackTemp);

    if (p_dTrackTemp >= 50)
    {
        ui->frmTrackTempCol->setStyleSheet("background-colour: rgb(255, 0, 0");
    }
    else if (p_dTrackTemp >= 40)
    {
        ui->frmTrackTempCol->setStyleSheet("background-colour: rgb(255, 128, 0");
    }
    else
    {
        ui->frmTrackTempCol->setStyleSheet("background-colour: rgb(0, 255, 0");
    }
}

void Dashboard::ChangeIsRaining(int p_iIsRaining)
{
    ui->lblIsRainingVal->setText(QString::number(p_iIsRaining));
}

void Dashboard::ChangeHumidity(int p_iHumidity)
{
    ui->lblHumidityVal->setText(QString::number(p_iHumidity));
    ui->sldHumiditySlide->setValue(p_iHumidity);

    if (p_iHumidity >= 40)
    {
        ui->frmAirTempCol->setStyleSheet("background-colour: rgb(255, 0, 0");
    }
    else if (p_iHumidity >= 30)
    {
        ui->frmAirTempCol->setStyleSheet("background-colour: rgb(255, 128, 0");
    }
    else
    {
        ui->frmAirTempCol->setStyleSheet("background-colour: rgb(0, 255, 0");
    }
}

void Dashboard::ChangeLapNum(int p_iLapNum)
{
    // Move trangle representing car forward
}

void Dashboard::AddLapTime(double p_dLapTime)
{
    // Add another lap time to the graph
}

void Dashboard::AddSectorTimes(double p_dS1Time, double p_dS2Time, double p_dS3Time)
{
    // Add sector times to the graph
}

void Dashboard::ChangeBrake(int p_iIsBrake)
{
    if (p_iIsBrake == 1)
    {
        ui->lblBrakesVal->setText("ON");
    }
    else
    {
        ui->lblBrakesVal->setText("OFF");
    }
}

void Dashboard::ChangePosition(int p_iPosition)
{
    ui->lblPositionVal->setText(QString::number(p_iPosition));
}

void Dashboard::ChangeLapPct(double p_dLapPctChange)
{
    ui->lblLapPctVal->setText(QString::number(p_dLapPctChange));
}

void Dashboard::ChangeS1Pct(double p_dS1PctChange)
{
    ui->lblS1PctVal->setText(QString::number(p_dS1PctChange));
}

void Dashboard::ChangeS2Pct(double p_dS2PctChange)
{
    ui->lblS2PctVal->setText(QString::number(p_dS2PctChange));
}

void Dashboard::ChangeS3Pct(double p_dS3PctChange)
{
    ui->lblS3PctVal->setText(QString::number(p_dS3PctChange));
}

void Dashboard::PitUrgencyChanged(int p_iUrgency)
{
    // Display pit window depending on urgency

    // Update pit indicator
    switch (p_iUrgency)
    {
    case (0):
        ui->lblPitUrgencyVal->setStyleSheet("background-colour: rgb(255, 0, 0");
        break;
    case(1):
        ui->lblPitUrgencyVal->setStyleSheet("background-colour: rgb(255, 128, 0");
        break;
    case (2):
        ui->lblPitUrgencyVal->setStyleSheet("background-colour: rgb(0, 255, 0");
        break;
    }
}
