#pragma once

#include <array>
#include <string>
#include <ctime>
#include <fstream>
#include <frc/Timer.h>
#include <frc/TimedRobot.h>
#include <frc/DriverStation.h>
#include <frc/Solenoid.h>

#include "RobotData.h"

struct DiagnosticsData
{
    // accelerometer
    double accelX{-1.0}, accelY{-1.0}, accelZ{-1.0};

    // motor contollers
    // 33 so that we can use real mControl CAN IDs
    std::array<double, 41>
        mControlCurrents{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        mControlVoltages{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        mControlPositions{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        mControlVelocities{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
        mControlTemps{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    std::array<std::uint16_t, 41> mControlFaults{};

    // PDP slots
    double pdpTotalVoltage{-1.0};
    double pdpTotalCurrent{-1.0};
    double pdpTotalPower{-1.0};
    double pdpTotalEnergy{-1.0};
    double pdpTemp{-1.0};
    std::array<double, 16> pdpCurrents{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    // compressor
    bool
        compEnabled{false},
        compPressureSwitchVal{false};

    double compCurrent{-1.0};

    bool
        compCurrentHighFault{false},
        compShortedFault{false},
        compNotConnectedFault{false};

    // solenoids
    bool
        solenoidArm{false},
        solenoidLockL{false},
        solenoidLockR{false};

    // limit switches
    bool turretLSwitch{false}, hoodLSwitch{false};
};

class Diagnostics
{
public:
    void LogInit();
    void TestInit();
    void LogPeriodic(RobotData &robotData, DiagnosticsData &diagnosticsData);
    void TestPeriodic(DiagnosticsData &diagnosticsData);

private:
    void constructMetaElements(std::string &filePath);
    void constructParamHeader(std::string &paramHeader);
    void setLogValues();
    std::string appendLogValues(RobotData &robotData, DiagnosticsData &diagnosticsData);

    void addLogSnippet(std::string &log, std::string param);
    void addLogSnippet(std::string &log, int param);
    void addLogSnippet(std::string &log, bool param);
    void addLogSnippet(std::string &log, double param);
    void addLogSnippet(std::string &log, std::uint16_t param);

    std::string convertMatchType(int param);
    std::string convertAlliance(int param);
    std::string convertSolenoidValue(int param);
    std::string convertAutonSelect(int param);
    std::string convertDriveMode(int param);

    std::ofstream log_file;

    frc::Timer timer{};
    bool timerStarted = false;
    double seconds{-1.0};

    // match
    std::string matchMode{"none"};
    bool pStickConnected{false};
    bool sStickConnected{false};
    double batteryVoltage{-1.0};
};