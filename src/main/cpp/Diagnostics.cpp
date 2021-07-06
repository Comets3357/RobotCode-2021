#include <frc/smartdashboard/SmartDashboard.h>

#include "Diagnostics.h"

void Diagnostics::LogInit()
{
    timer.Reset();

    // create file
    std::string filePath;
    if (bool usingUSB = false)
    {
        filePath = "/media/sda/Diagnostics/Logs/";
    }
    else
    {
        filePath = "/home/lvuser/Diagnostics/Logs/";
    }
    constructMetaElements(filePath);

    std::string paramHeader = "";
    constructParamHeader(paramHeader);

    log_file.open(filePath);

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

std::string Diagnostics::convertAutonSelect(int param)
{
    std::array<std::string, 6> autonSelectStrings
    {
        "potato", "exitInitLine", "shootAndDrive", "shootAndCollectBalls",
        "trenchRun", "goofy"
    };
    return autonSelectStrings.at(param);
}

std::string Diagnostics::convertDriveMode(int param)
{
    std::array<std::string, 6> driveModeStrings
    {
        "teleop", "potato", "initDriveStraight", "driveStraight",
        "arc", "initArc"
    };
    return driveModeStrings.at(param);
}

/* std::string Diagnostics::convertSolenoidValue(int param)
{
    std::array<std::string, 3> valueStrings{"-1", "1", "0"};
    return valueStrings.at(param);
} */

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
    // auton - robot

    std::string log = ""; // local log var
    log.reserve(1200);  // temp byte count for reserver

    addLogSnippet(log, seconds);
    addLogSnippet(log, matchMode);
    addLogSnippet(log, pStickConnected);
    addLogSnippet(log, sStickConnected);
    addLogSnippet(log, batteryVoltage);

    addLogSnippet(log, diagnosticsData.accelX);
    addLogSnippet(log, diagnosticsData.accelY);
    addLogSnippet(log, diagnosticsData.accelZ);

    addLogSnippet(log, robotData.robotAngle);
    addLogSnippet(log, robotData.robotTiltAngle);
    addLogSnippet(log, robotData.robotYAngle);

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

    addLogSnippet(log, diagnosticsData.solenoidOneValue);
    addLogSnippet(log, diagnosticsData.solenoidArmL);
    addLogSnippet(log, diagnosticsData.solenoidArmR);
    addLogSnippet(log, diagnosticsData.solenoidLockL);
    addLogSnippet(log, diagnosticsData.solenoidLockR);

    addLogSnippet(log, diagnosticsData.turretLSwitch);
    addLogSnippet(log, diagnosticsData.hoodLSwitch);

    addLogSnippet(log, robotData.validTarget);

    addLogSnippet(log, robotData.manualMode);
    addLogSnippet(log, robotData.shift);

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

    addLogSnippet(log, convertAutonSelect(robotData.autonSelect));
    addLogSnippet(log, robotData.autonStep);
    addLogSnippet(log, convertDriveMode(robotData.driveMode));

    addLogSnippet(log, robotData.climbMode);

    // delete the last comma and space
    log.erase(log.length() - 1);
    log.erase(log.length() - 1);
    log += "\n";

    return log;
}

void Diagnostics::constructMetaElements(std::string &filePath)
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
    char* dt = ctime(&now);
    std::string dt2(dt);
    dt2.erase(dt2.length() - 1);
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

    if (frc::DriverStation::GetInstance().IsFMSAttached())
    {
        // filePath += ("Matches/" + month + "." + day + "." + year + "event" + eventName + " type" + matchType + " match" + matchNum + ".txt");
        filePath += ("Matches/" + dt2 + " " + eventName + " " + matchType + " " + alliance + " " + location + " match " + matchNum + ".txt");
    }
    else
    {
        // filePath += ("Other/" + month + "." + day + "." + year + ".txt");
        filePath += ("Other/" + dt2 + ".txt");
    }

    // metaHeader += (month + "." + day + "." + year + " event: " + eventName + " type: " + matchType + " match: " + matchNum + " alliance: " + alliance + " location: " + location);
}

void Diagnostics::constructParamHeader(std::string &paramHeader)
{
    {paramHeader +=
        (/* "param"
         "Header" */
        
        "seconds, "
        "matchMode, "
        "pStickConnected, "
        "sStickCOnnected, "
        "batteryVoltage, "
        "accelX, "
        "accelY, "
        "accelZ, "
        "gyroYaw, "
        "gyroTilt, "
        "gyroPitch, "

        "mControl1Current, "
        "mControl1Voltage, "
        "mControl1Position, "
        "mControl1Velocity, "
        "mControl1Temp, "
        "mControl1Faults, "

        "mControl2Current, "
        "mControl2Voltage, "
        "mControl2Position, "
        "mControl2Velocity, "
        "mControl2Temp, "
        "mControl2Faults, "

        "mControl3Current, "
        "mControl3Voltage, "
        "mControl3Position, "
        "mControl3Velocity, "
        "mControl3Temp, "
        "mControl3Faults, "

        "mControl4Current, "
        "mControl4Voltage, "
        "mControl4Position, "
        "mControl4Velocity, "
        "mControl4Temp, "
        "mControl4Faults, "

        "mControl32Current, "
        "mControl32Voltage, "
        "mControl32Position, "
        "mControl32Velocity, "
        "mControl32Temp, "
        "mControl32Faults, "

        "mControl11Current, "
        "mControl11Voltage, "
        "mControl11Position, "
        "mControl11Velocity, "
        "mControl11Temp, "
        "mControl11Faults, "

        "mControl12Current, "
        "mControl12Voltage, "
        "mControl12Position, "
        "mControl12Velocity, "
        "mControl12Temp, "
        "mControl12Faults, "

        "mControl23Current, "
        "mControl23Voltage, "
        "mControl23Position, "
        "mControl23Velocity, "
        "mControl23Temp, "
        "mControl23Faults, "

        "mControl22Current, "
        "mControl22Voltage, "
        "mControl22Position, "
        "mControl22Velocity, "
        "mControl22Temp, "
        "mControl22Faults, "

        "mControl20Current, "
        "mControl20Voltage, "
        "mControl20Position, "
        "mControl20Velocity, "
        "mControl20Temp, "
        "mControl20Faults, "

        "mControl21Current, "
        "mControl21Voltage, "
        "mControl21Position, "
        "mControl21Velocity, "
        "mControl21Temp, "
        "mControl21Faults, "

        "pdpTotalVoltage, "
        "pdpTotalCurrent, "
        "pdpTotalPower, "
        "pdpTotalEnergy, "
        "pdpTemp, "

        "pdp0Current, "
        "pdp1Current, "
        "pdp2Current, "
        "pdp3Current, "
        "pdp4Current, "
        "pdp5Current, "
        "pdp6Current, "
        "pdp7Current, "
        "pdp8Current, "
        "pdp9Current, "
        "pdp10Current, "
        "pdp11Current, "
        "pdp12Current, "
        "pdp13Current, "
        "pdp14Current, "
        "pdp15Current, "

        "compEnabled, "
        "compPressureSwitchVal, "
        "compCurrent, "
        "compCurrentHighFault, "
        "compShortedFault, "
        "compNotConnectedFault, "

        "solenoidOneValue, "
        "solenoidArmL, "
        "solenoidArmR, "
        "solenoidLockL, "
        "solenoidLockR, "

        "turretLSwitch, "
        "hoodLSwitch, "

        "validTarget, "

        "manualMode, "
        "shift, "

        "pLYStick, "
        "pRYStick, "
        "pABtn, "
        "pLShoulderBtn, "

        "sLYStick, "
        "sRYStick, "
        "sABtn, "
        "sBBtn, "
        "sXBtn, "
        "sYBtn, "
        "sLBumper, "
        "sRBumper, "
        "sRCenterBtn, "
        "sDPad, "

        "autonSelect, "
        "autonStep, "
        "driveMode, "

        "climbMode, "
        
        );}

    // twice because there's a comma and space
    paramHeader.erase(paramHeader.length() - 1);
    paramHeader.erase(paramHeader.length() - 1);
}