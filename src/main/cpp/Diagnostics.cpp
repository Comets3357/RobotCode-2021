#include <frc/smartdashboard/SmartDashboard.h>

#include "Diagnostics.h"

void Diagnostics::LogInit()
{
    timer.Reset();

    // create file
    std::string filePath = "/media/sda/Diagnostics/";
    std::string metaHeader = "";
    constructMetaElements(filePath, metaHeader);

    std::string paramHeader = "";
    constructParamHeader(paramHeader);

    wpi::outs() << "filePath: " << filePath << '\n';
    wpi::outs() << "metaHeader: " << metaHeader << '\n';
    wpi::outs() << "paramHeader: " << paramHeader << '\n';

    frc::SmartDashboard::PutString("filePath", filePath);
    frc::SmartDashboard::PutString("metaHeader", metaHeader);
    frc::SmartDashboard::PutString("pararmHeader", paramHeader);

    log_file.open(filePath);

    log_file << metaHeader << "\n";
    log_file << paramHeader << "\n";
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
    wpi::outs() << appendLogValues(robotData, diagnosticsData) << '\n';
    frc::SmartDashboard::PutString("appendLogValues", appendLogValues(robotData, diagnosticsData));
    log_file << appendLogValues(robotData, diagnosticsData);
}

void Diagnostics::TestPeriodic(DiagnosticsData &diagnosticsData)
{
}

// sets the private variables for the diagnostics object
void Diagnostics::setLogValues()
{
    seconds = timer.Get();

    if (frc::DriverStation::GetInstance().IsAutonomous())
    {
        matchMode = "auto";
    }
    else if (frc::DriverStation::GetInstance().IsOperatorControl())
    {
        matchMode = "oper";
    }
    else if (frc::DriverStation::GetInstance().IsTest())
    {
        matchMode = "test";
    }

    pStickConnected = frc::DriverStation::GetInstance().IsJoystickConnected(0);
    sStickConnected = frc::DriverStation::GetInstance().IsJoystickConnected(1);
    batteryVoltage = frc::DriverStation::GetInstance().GetBatteryVoltage();
}

// repetetive and unideal but I'm running out of time, so I'm gonna use overload instead of function templates. I tried using pointers and auto type parameters previously.

void Diagnostics::addLogSnippet(std::string &log, std::string param)
{
    log += (param + ", ");
}

void Diagnostics::addLogSnippet(std::string &log, int param)
{
    log += (std::to_string(param) + ", ");
}

void Diagnostics::addLogSnippet(std::string &log, bool param)
{
    log += (std::to_string(param) + ", ");
}

void Diagnostics::addLogSnippet(std::string &log, double param)
{
    log += (std::to_string(param) + ", ");
}

void Diagnostics::addLogSnippet(std::string &log, std::uint16_t param)
{
    log += (std::to_string(param) + ", ");
}

std::string Diagnostics::convertMatchType(int param)
{
    std::array<std::string, 4> matchTypeStrings{"none", "prac", "qual", "elim"};
    return matchTypeStrings.at(param);
}

std::string Diagnostics::convertAlliance(int param)
{
    std::array<std::string, 3> allianceStrings{"red", "blu", "inv"};
    return allianceStrings.at(param);
}

std::string Diagnostics::convertSolenoidValue(int param)
{
    std::array<std::string, 3> valueStrings{"-1", "1", "0"};
    return valueStrings.at(param);
}

std::string Diagnostics::appendLogValues(RobotData &robotData, DiagnosticsData &diagnosticsData)
{
    // timer - diagnostics
    // accelerometer - diagnostics
    // gyro - robot
    // mcontrols - diagnostics
    // pdp - diagnostics
    // compressor - diagnostics
    // solenoids - diagnostics
    // limit switch - diagnostics
    // limelight - robot
    // battery - diagnostics
    // js - robot

    std::string log = ""; // local log var

    addLogSnippet(log, seconds);
    addLogSnippet(log, matchMode);
    addLogSnippet(log, pStickConnected);
    addLogSnippet(log, sStickConnected);
    addLogSnippet(log, batteryVoltage);

    addLogSnippet(log, diagnosticsData.accelX);
    addLogSnippet(log, diagnosticsData.accelY);
    addLogSnippet(log, diagnosticsData.accelZ);

    addLogSnippet(log, robotData.robotAngle);

    std::array<int, 11> mControlIDs{1, 2, 3, 4, 32, 11, 12, 23, 22, 20, 21};
    for (int i = 0; i < 11; i++)
    {
        addLogSnippet(log, diagnosticsData.mControlCurrents.at(
                               mControlIDs.at(i)));
        addLogSnippet(log, diagnosticsData.mControlVoltages.at(
                               mControlIDs.at(i)));
        addLogSnippet(log, diagnosticsData.mControlPositions.at(
                               mControlIDs.at(i)));
        addLogSnippet(log, diagnosticsData.mControlVelocities.at(
                               mControlIDs.at(i)));
        addLogSnippet(log, diagnosticsData.mControlTemps.at(
                               mControlIDs.at(i)));
        addLogSnippet(log, diagnosticsData.mControlFaults.at(
                               mControlIDs.at(i)));
    }

    addLogSnippet(log, diagnosticsData.pdpTotalVoltage);
    addLogSnippet(log, diagnosticsData.pdpTotalCurrent);
    addLogSnippet(log, diagnosticsData.pdpTotalPower);
    addLogSnippet(log, diagnosticsData.pdpTotalEnergy);
    addLogSnippet(log, diagnosticsData.pdpTemp);
    for (int i = 0; i < 16; i++)
    {
        addLogSnippet(log, diagnosticsData.pdpCurrents.at(i));
    }

    addLogSnippet(log, diagnosticsData.compEnabled);
    addLogSnippet(log, diagnosticsData.compPressureSwitchVal);
    addLogSnippet(log, diagnosticsData.compCurrent);

    addLogSnippet(log, diagnosticsData.compCurrentHighFault);
    addLogSnippet(log, diagnosticsData.compShortedFault);
    addLogSnippet(log, diagnosticsData.compNotConnectedFault);

    addLogSnippet(log, convertSolenoidValue(diagnosticsData.solenoidOneValue));

    addLogSnippet(log, diagnosticsData.turretLSwitch);
    addLogSnippet(log, diagnosticsData.hoodLSwitch);

    addLogSnippet(log, robotData.validTarget);

    addLogSnippet(log, robotData.pLYStick);
    addLogSnippet(log, robotData.pRYStick);
    addLogSnippet(log, robotData.pABtn);
    addLogSnippet(log, robotData.pLShoulderBtn);

    addLogSnippet(log, robotData.sLYStick);
    addLogSnippet(log, robotData.sRYStick);
    addLogSnippet(log, robotData.sABtn);
    addLogSnippet(log, robotData.sBBtn);
    addLogSnippet(log, robotData.sXBtn);
    addLogSnippet(log, robotData.sYBtn);
    addLogSnippet(log, robotData.sLBumper);
    addLogSnippet(log, robotData.sRBumper);
    addLogSnippet(log, robotData.sRCenterBtn);
    addLogSnippet(log, robotData.sDPad);

    // delete the last comma
    log.erase(log.length() - 1);

    return log;
}

void Diagnostics::constructMetaElements(std::string &filePath, std::string &metaHeader)
{
    // set defaults/errors
    std::string day = "-1";
    std::string month = "-1";
    std::string year = "-1";
    std::string eventName = "-1";
    std::string matchType = "-1";
    std::string alliance = "-1";
    std::string location = "-1";
    std::string matchNum = "-1";

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char* dt = ctime(&now); // can't get this to string but whatever
    day = std::to_string(ltm->tm_mday);
    month = std::to_string(1 + ltm->tm_mon);
    year = std::to_string(1900 + ltm->tm_year);

    eventName = frc::DriverStation::GetInstance().GetEventName();
    if (eventName == "")
    {
        eventName = "none";
    }
    matchType = convertMatchType(frc::DriverStation::GetInstance().GetMatchType());
    alliance = convertAlliance(frc::DriverStation::GetInstance().GetAlliance());
    location = std::to_string(frc::DriverStation::GetInstance().GetLocation());
    matchNum = std::to_string(frc::DriverStation::GetInstance().GetMatchNumber());

    frc::SmartDashboard::PutString("day", day);
    frc::SmartDashboard::PutString("month", month);
    frc::SmartDashboard::PutString("year", year);
    frc::SmartDashboard::PutString("eventName", eventName);
    frc::SmartDashboard::PutString("matchType", matchType);
    frc::SmartDashboard::PutString("matchNum", matchNum);
    frc::SmartDashboard::PutString("alliance", alliance);
    frc::SmartDashboard::PutString("location", location);

    wpi::outs() << frc::DriverStation::GetInstance().IsFMSAttached() << '\n';
    frc::SmartDashboard::PutBoolean("IsFMSAttached", frc::DriverStation::GetInstance().IsFMSAttached());
    if (frc::DriverStation::GetInstance().IsFMSAttached())
    {
        filePath += ("Matches/" + month + "." + day + "." + year + "event" + eventName + " type" + matchType + " match" + matchNum + ".txt");
    }
    else
    {
        filePath += ("Other/" + month + "." + day + "." + year + ".txt");
    }

    metaHeader += (month + "." + day + "." + year + " event: " + eventName + " type: " + matchType + " match: " + matchNum + " alliance: " + alliance + " location: " + location);
}

void Diagnostics::constructParamHeader(std::string &paramHeader)
{
    paramHeader +=
        ("param"
         "Header"
         /* "seconds, "
        "matchMode, "
        "pStickConnected, "
        "sStickCOnnected, "
        "batteryVoltage, "
        ", " */
        );
}