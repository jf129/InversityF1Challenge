#ifndef CAR_H
#define CAR_H

#include <QObject>

class Car : public QObject
{
    Q_OBJECT
private:
    int cls_iDriverNum;                                                         // Driver unique number
    int cls_iLapNum;                                                            // Which lap the car is on
    QVector<double> cls_dLapTimes;                                              // Vector to hold lap times
    QVector<QVector<double>> cls_dSectorTimes;                                  // 2d vector to hold lap sector times
    int cls_iIsBrake;                                                           // 1 if braking, 0 if not
    int cls_iPosition;                                                          // Car's position in race
    double cls_dLapPctChange;                                                   // Lap time percentage change from last pit or start of race
    double cls_dS1PctChange;                                                    // Sector 1 time percentage change from last pit or start of race
    double cls_dS2PctChange;                                                    // Sector 2 time percentage change from last pit or start of race
    double cls_dS3PctChange;                                                    // Sector 3 time percentage change from last pit or start of race
    int cls_iPitUrgency;                                                        // How urgent a pit stop is needed
    int cls_iLastPit;                                                           // Lap number of last pit stop

public:
    explicit Car(QObject *parent = nullptr, int p_iDiverNum = 0);               // Constructor, sets driver number
    int GetDriverNumber();                                                      // Returns driver number of car
    void SetData(int p_iLapNum, bool p_bOutOfPit, double p_dLapTime,            // Sets all real-time data relating to the car
                 double p_dS1Time, double p_dS2Time, double p_dS3Time,
                 int p_iIsBrake, int p_iPosition);
    int GetPitUrgency();                                                        // Returns pit urgency
    void CalculatePit();                                                        // Calculates how urgent it is for the car to pit

signals:                                                                        // Emitted when specific value changes
    void LapNumChanged(int p_iLapNum);
    void AddLapTime(double p_dLapTime);
    void AddSectorTimes(double p_dS1Time, double p_dS2Time, double p_dS3Time);
    void BrakeChanged(int p_iIsBrake);
    void PositionChanged(int p_iPosition);
    void LapPctChanged(double p_dLapPctChange);
    void S1PctChanged(double p_dS1PctChange);
    void S2PctChanged(double p_dS2PctChange);
    void S3PctChanged(double p_dS3PctChange);
};

#endif // CAR_H
