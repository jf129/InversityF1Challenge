#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "racethread.h"
#include "weather.h"
#include "car.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dashboard;
}
QT_END_NAMESPACE

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    Dashboard(QWidget *parent = nullptr);                                       // Default constructor
    ~Dashboard();                                                               // Destructor
public slots:                                                                   // Changes the state of GUI components relating to the specific value
    void ChangeAirTemp(double p_dAirTemp);
    void ChangeWindSpeed(double p_dWindSpeed);
    void ChangeWindDirection(double p_dWindDirection);
    void ChangeTrackTemp(double p_dTrackTemp);
    void ChangeIsRaining(int p_iIsRaining);
    void ChangeHumidity(int p_iHumidity);
    void ChangeLapNum(int p_iLapNum);
    void AddLapTime(double p_dLapTime);
    void AddSectorTimes(double p_dS1Time, double p_dS2Time, double p_dS3Time);
    void ChangeBrake(int p_iIsBrake);
    void ChangePosition(int p_iPosition);
    void ChangeLapPct(double p_dLapPctChange);
    void ChangeS1Pct(double p_dS1PctChange);
    void ChangeS2Pct(double p_dS2PctChange);
    void ChangeS3Pct(double p_dS3PctChange);
    void PitUrgencyChanged(int p_iUrgency);

private:
    Ui::Dashboard *ui;                                                          // Class GUI object
    RaceThread* cls_objRaceThread;                                              // Class pointer to RaceThread object
    Weather* cls_ptrWeather;                                                    // Class pointer to Weather object
    Car* cls_ptrCar;                                                            // Class pointer to the object of Car thats data is being monitored
    void InitGraph();                                                           // Initialises the lap and sector time graph
};
#endif // DASHBOARD_H
