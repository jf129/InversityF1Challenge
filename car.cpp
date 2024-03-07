#include "car.h"

Car::Car(QObject *parent, int p_iDriverNum): QObject{parent}
{
    this->cls_iDriverNum = p_iDriverNum;
    this->cls_iLapNum = 0;
    this->cls_iLastPit = 0;
}

int Car::GetDriverNumber()
{
    return this->cls_iDriverNum;
}

void Car :: SetData(int p_iLapNum, bool p_bOutOfPit, double p_dLapTime, double p_dS1Time, double p_dS2Time, double p_dS3Time, int p_iIsBrake, int p_iPosition)
{
    QVector<double> l_dTempVect;
    if (p_iLapNum != this->cls_iLapNum)
    {
        if (p_bOutOfPit == true)
        {
            this->cls_iLastPit = this->cls_iLapNum;
        }
        this->cls_iLapNum++;

        this->cls_dLapTimes.append(p_dLapTime);

        l_dTempVect.append(p_dS1Time);
        l_dTempVect.append(p_dS2Time);
        l_dTempVect.append(p_dS3Time);
        this->cls_dSectorTimes.append(l_dTempVect);

        emit LapNumChanged(this->cls_iLapNum);
        emit AddLapTime(p_dLapTime);
        emit AddSectorTimes(p_dS1Time, p_dS2Time, p_dS3Time);

        this->CalculatePit();
    }

    if (p_iIsBrake != this->cls_iIsBrake)
    {
        this->cls_iIsBrake = p_iIsBrake;
        emit BrakeChanged(this->cls_iIsBrake);
    }

    if (p_iPosition != this->cls_iPosition)
    {
        this->cls_iPosition = p_iPosition;
        emit PositionChanged(this->cls_iPosition);
    }
}

void Car::CalculatePit()
{
// calculate percentage changes and calculate pit urgency
    this->cls_dLapPctChange = ((this->cls_dLapTimes[this->cls_iLapNum - 1] - this->cls_dLapTimes[this->cls_iLastPit])/this->cls_dLapTimes[this->cls_iLastPit]) * 100;
    this->cls_dS1PctChange = ((this->cls_dSectorTimes[this->cls_iLapNum - 1][0] - this->cls_dSectorTimes[this->cls_iLastPit][0])/this->cls_dSectorTimes[this->cls_iLastPit][0]) * 100;
    this->cls_dS2PctChange = ((this->cls_dSectorTimes[this->cls_iLapNum - 1][1] - this->cls_dSectorTimes[this->cls_iLastPit][1])/this->cls_dSectorTimes[this->cls_iLastPit][1]) * 100;
    this->cls_dS3PctChange = ((this->cls_dSectorTimes[this->cls_iLapNum - 1][2] - this->cls_dSectorTimes[this->cls_iLastPit][2])/this->cls_dSectorTimes[this->cls_iLastPit][2]) * 100;

    if (this->cls_dLapPctChange >= 2)
    {
        this->cls_iPitUrgency = 2;
    }
    else if (this->cls_dLapPctChange >= 1)
    {
        this->cls_iPitUrgency = 1;
    }
    else
    {
        this->cls_iPitUrgency = 0;
    }

    emit LapPctChanged(this->cls_dLapPctChange);
    emit S1PctChanged(this->cls_dS1PctChange);
    emit S2PctChanged(this->cls_dS2PctChange);
    emit S3PctChanged(this->cls_dS3PctChange);
}

int Car::GetPitUrgency()
{
    return this->cls_iPitUrgency;
}
