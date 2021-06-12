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
    frc::SmartDashboard::PutString("appendLogValues", appendLogValues(robotData));

    frc::SmartDashboard::PutString("day", day);
    frc::SmartDashboard::PutString("day", month);
    frc::SmartDashboard::PutString("day", year);

    frc::SmartDashboard::PutString("eventName", eventName);
    // frc::SmartDashboard::PutString("matchType", static_cast<std::string>(matchType));
    // frc::SmartDashboard::PutString("matchType", matchType);
    // frc::SmartDashboard::PutValue("matchType", matchType);
    // alliance

    frc::SmartDashboard::PutNumber("matchNum", matchNum);

    frc::SmartDashboard::PutString("matchMode", matchMode);
    frc::SmartDashboard::PutBoolean("pStickConnected", pStickConnected);
    frc::SmartDashboard::PutBoolean("sStickConnected", sStickConnected);

    frc::SmartDashboard::PutNumber("seconds", seconds);
    frc::SmartDashboard::PutNumber("batteryVoltage", batteryVoltage);


    frc::SmartDashboard::PutNumber("accelX", diagnosticsData.accelX);
    frc::SmartDashboard::PutNumber("accelY", diagnosticsData.accelY);
    frc::SmartDashboard::PutNumber("accelZ", diagnosticsData.accelZ);

    frc::SmartDashboard::PutNumber("pdpTotalVoltage", diagnosticsData.pdpTotalVoltage);
    frc::SmartDashboard::PutNumber("pdpTotalCurrent", diagnosticsData.pdpTotalCurrent);
    frc::SmartDashboard::PutNumber("pdpTotalPower", diagnosticsData.pdpTotalPower);
    frc::SmartDashboard::PutNumber("pdpTotalEnergy", diagnosticsData.pdpTotalEnergy);
    frc::SmartDashboard::PutNumber("pdpTemp", diagnosticsData.pdpTemp);
    
    frc::SmartDashboard::PutNumber("dbLM current", diagnosticsData.mControlCurrents.at(1));
    frc::SmartDashboard::PutNumber("dbRM current", diagnosticsData.mControlCurrents.at(3));
    frc::SmartDashboard::PutNumber("dbLS current", diagnosticsData.mControlCurrents.at(2));
    frc::SmartDashboard::PutNumber("dbRS current", diagnosticsData.mControlCurrents.at(4));

    frc::SmartDashboard::PutNumber("dbLM voltage", diagnosticsData.mControlVoltages.at(1));
    frc::SmartDashboard::PutNumber("dbRM voltage", diagnosticsData.mControlVoltages.at(3));
    frc::SmartDashboard::PutNumber("dbLS voltage", diagnosticsData.mControlVoltages.at(2));
    frc::SmartDashboard::PutNumber("dbRS voltage", diagnosticsData.mControlVoltages.at(4));
    
    frc::SmartDashboard::PutNumber("dbLM temperature", diagnosticsData.mControlTemps.at(1));
    frc::SmartDashboard::PutNumber("dbRM temperature", diagnosticsData.mControlTemps.at(3));
    frc::SmartDashboard::PutNumber("dbLS temperature", diagnosticsData.mControlTemps.at(2));
    frc::SmartDashboard::PutNumber("dbRS temperature", diagnosticsData.mControlTemps.at(4));

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