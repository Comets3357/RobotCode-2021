#pragma once

#include <array>
#include <string>
#include <ctime>
#include <frc/Timer.h>
#include <frc/DriverStation.h>
#include <frc/DoubleSolenoid.h>

#include "RobotData.h"

struct DiagnosticsData
{
    // accelerometer
    double accelX, accelY, accelZ;

    // motor contollers
    std::array<std::uint16_t, 32> mControlFaults;

    std::array<double, 32>
        mControlCurrents,
        mControlVoltages,
        mControlPositions,
        mControlVelocities,
        mControlTemps;

    // PDP slots
    std::array<double, 16> pdpCurrents, pdpPowers;

    // compressor
    bool
        compEnabled,
        compPressureSwitchVal,
        compCurrent,

        compCurrentHighFault,
        compShortedFault,
        compNotConnectedFault;

    // solenoids
    frc::DoubleSolenoid::Value solenoidOneValue;

    // limit switches
    bool turrentLSwitch, hoodLSwitch;
};

class Diagnostics
{
public:
    void LogInit();
    void TestInit();
    void LogPeriodic(RobotData &robotData, DiagnosticsData &diagnosticsData);
    void TestPeriodic(DiagnosticsData &diagnosticsData);

private:
    void setLogValues();
    std::string appendLogValues(RobotData &RobotData);

    frc::Timer timer{};
    bool timerStarted = false;
    double seconds;

    // meta data from driverstation
    std::string day, month, year;
    std::string eventName;
    frc::DriverStation::MatchType matchType;
    frc::DriverStation::Alliance alliance;
    int location;
    int matchNum = -1;

    // match
    std::string matchMode;

    // driverstation checks
    bool pStickConnected;
    bool sStickConnected;
    double batteryVoltage;
};