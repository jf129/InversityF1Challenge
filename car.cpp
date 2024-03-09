#include "car.h"

Car::Car(QObject *parent, int p_iDriverNum): QObject{parent}
{
    // Initialise class variables
    this->cls_iDriverNum = p_iDriverNum;
    this->cls_iLapNum = 0;
    this->cls_iLastPit = 0;
}

int Car::GetDriverNumber()
{
    return this->cls_iDriverNum;                                                    // Returns driver number
}

void Car :: SetData(int p_iLapNum, bool p_bOutOfPit, double p_dLapTime, double p_dS1Time, double p_dS2Time, double p_dS3Time, int p_iIsBrake, int p_iPosition)
{
    QVector<double> l_dTempVect;                                                    // Temporary vector to hold sector times
    if (p_iLapNum != this->cls_iLapNum)                                             // Checks if car has completed another lap
    {
        if (p_bOutOfPit == true)                                                    // Checks if car has just come out of pit
        {
            this->cls_iLastPit = this->cls_iLapNum;                                 // Updates the lap number of the last pit
        }
        this->cls_iLapNum++;                                                        // Increments lap number

        this->cls_dLapTimes.append(p_dLapTime);                                     // Adds another lap time to vector

        // Adds sector times to temporary vector
        l_dTempVect.append(p_dS1Time);
        l_dTempVect.append(p_dS2Time);
        l_dTempVect.append(p_dS3Time);
        this->cls_dSectorTimes.append(l_dTempVect);                                 // Adds temporary vector to class vector of sector times

        // Emit signals that values have chagned
        emit LapNumChanged(this->cls_iLapNum);
        emit AddLapTime(p_dLapTime);
        emit AddSectorTimes(p_dS1Time, p_dS2Time, p_dS3Time);

        this->CalculatePit();                                                       // Calls CalculatePit
    }

    if (p_iIsBrake != this->cls_iIsBrake)                                           // Checks if brake status has changed
    {
        this->cls_iIsBrake = p_iIsBrake;                                            // Sets class variable
        emit BrakeChanged(this->cls_iIsBrake);                                      // Emits signal that poisition has changed
    }

    if (p_iPosition != this->cls_iPosition)                                         // Checks if position has changed
    {
        this->cls_iPosition = p_iPosition;                                          // Sets class variable
        emit PositionChanged(this->cls_iPosition);                                  // Emits signal that position has changed
    }
}

void Car::CalculatePit()
{
    // Calculates percentage changes
    this->cls_dLapPctChange = ((this->cls_dLapTimes[this->cls_iLapNum - 1] - this->cls_dLapTimes[this->cls_iLastPit])/this->cls_dLapTimes[this->cls_iLastPit]) * 100;
    this->cls_dS1PctChange = ((this->cls_dSectorTimes[this->cls_iLapNum - 1][0] - this->cls_dSectorTimes[this->cls_iLastPit][0])/this->cls_dSectorTimes[this->cls_iLastPit][0]) * 100;
    this->cls_dS2PctChange = ((this->cls_dSectorTimes[this->cls_iLapNum - 1][1] - this->cls_dSectorTimes[this->cls_iLastPit][1])/this->cls_dSectorTimes[this->cls_iLastPit][1]) * 100;
    this->cls_dS3PctChange = ((this->cls_dSectorTimes[this->cls_iLapNum - 1][2] - this->cls_dSectorTimes[this->cls_iLastPit][2])/this->cls_dSectorTimes[this->cls_iLastPit][2]) * 100;

    // Sets pit urgency depending on how much slower lap times have become
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

    // Emits signals that values have changed
    emit LapPctChanged(this->cls_dLapPctChange);
    emit S1PctChanged(this->cls_dS1PctChange);
    emit S2PctChanged(this->cls_dS2PctChange);
    emit S3PctChanged(this->cls_dS3PctChange);
}

int Car::GetPitUrgency()
{
    return this->cls_iPitUrgency;                   // Returns pit urgency
}
