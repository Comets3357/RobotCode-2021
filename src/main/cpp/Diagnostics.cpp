#include <frc/smartdashboard/SmartDashboard.h>

#include "Diagnostics.h"

void Diagnostics::LogInit()
{
    timer.Reset();
}

void Diagnostics::TestInit()
{
    timer.Reset();
}

void Diagnostics::LogPeriodic(RobotData &robotData, DiagnosticsData &diagnosticsData)
{
    if (!timerStarted)
    {
        timer.Start();
        timerStarted = true;
    }
    
    setLogValues();
    // wpi::outs() << appendLogValues(robotData).c_str() << '\n';
    // frc::SmartDashboard::PutString("appendLogValues", appendLogValues(robotData));
    frc::SmartDashboard::PutString("day", day);
    frc::SmartDashboard::PutString("day", month);
    frc::SmartDashboard::PutString("day", year);
}

void Diagnostics::TestPeriodic(DiagnosticsData &diagnosticsData)
{

}


// sets the private variables for the diagnostics object
void Diagnostics::setLogValues()
{
    seconds = timer.Get();

    // current date/time based on current system
    time_t now = time(0);
    // cout << "Number of sec since January 1,1970 is:: " << now << endl;
    tm *ltm = localtime(&now);
    // print various components of tm structure.
    std::string day = "Day: "+ ltm->tm_mday;
    std::string month = "Month: "+ 1 + ltm->tm_mon;
    std::string year = "Year:" + 1900 + ltm->tm_year;
    /* cout + "Time: "+ 5+ltm->tm_hour + ":";
    cout + 30+ltm->tm_min + ":";
    cout + ltm->tm_sec + endl; */

    eventName = frc::DriverStation::GetInstance().GetEventName();
    matchType = frc::DriverStation::GetInstance().GetMatchType();
    alliance = frc::DriverStation::GetInstance().GetAlliance();
    location = frc::DriverStation::GetInstance().GetLocation();
    matchNum = frc::DriverStation::GetInstance().GetMatchNumber();

    if (frc::DriverStation::GetInstance().IsAutonomous()) {matchMode = "auto";}
    else if (frc::DriverStation::GetInstance().IsOperatorControl()) {matchMode = "oper";}
    else if (frc::DriverStation::GetInstance().IsTest()) {matchMode = "test";}

    pStickConnected = frc::DriverStation::GetInstance().IsJoystickConnected(0);
    sStickConnected = frc::DriverStation::GetInstance().IsJoystickConnected(1);
    batteryVoltage = frc::DriverStation::GetInstance().GetBatteryVoltage();


}

std::string Diagnostics::appendLogValues(RobotData &RobotData)
{
    std::string log =
    "log"
    ;
    return log;
}