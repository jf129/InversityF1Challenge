#ifndef CAR_H
#define CAR_H

#include <QObject>

class Car : public QObject
{
    Q_OBJECT
private:
    int cls_iDriverNum;
    int cls_iLapNum;
    QVector<double> cls_dLapTimes;
    QVector<QVector<double>> cls_dSectorTimes;
    int cls_iIsBrake;
    int cls_iPosition;
    double cls_dLapPctChange;
    double cls_dS1PctChange;
    double cls_dS2PctChange;
    double cls_dS3PctChange;
    int cls_iPitUrgency;
    int cls_iLastPit;

public:
    explicit Car(QObject *parent = nullptr, int p_iDiverNum = 0);
    int GetDriverNumber();
    void SetData(int p_iLapNum, bool p_bOutOfPit, double p_dLapTime, double p_dS1Time, double p_dS2Time, double p_dS3Time, int p_iIsBrake, int p_iPosition);
    int GetPitUrgency();
    void CalculatePit();

signals:
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
