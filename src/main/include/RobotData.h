#pragma once

// auton mode
enum AutonSelect
{
    autonSelect_potato,
    autonSelect_exitInitLine
};

// this is for drivebase auton
enum DriveMode
{
    driveMode_teleop,       
    driveMode_potato,       
    driveMode_initDriveForward,
    driveMode_driveForward  
};

//could be separated into all separate files for the data *from* each subsystem
//commented out variables are not in use
struct RobotData 
{
    //controller data

    bool manualMode;
    int shift;
    bool shootingMode;

    //L = left, R = right, p = primary, s = secondary, Btn = button
    //primary

    double pLXStick;
    double pLYStick = 0;
    double pRXStick;
    double pRYStick = 0;
    bool pLStickBtn;
    bool pRStickBtn;

    double pLTrigger;
    double pRTrigger;
    bool pLBumper;
    bool pRtBumper;

    bool pXBtn;
    bool pYBtn;
    bool pABtn;
    bool pBBtn;

    bool pLCenterBtn;
    bool pRCenterBtn;

    int pDPad;

    //sStick

    double sLXStick;
    double sLYStick = 0;
    double sRXStick;
    double sRYStick = 0;
    bool sLStickBtn;
    bool sRStickBtn;

    double sLTrigger = 0;
    double sRTrigger = 0;
    bool sLBumper = false;
    bool sRBumper = false;

    bool sXBtn = false;
    bool sYBtn = false;
    bool sABtn = false;
    bool sBBtn = false;

    bool sLCenterBtn;
    bool sRCenterBtn;

    int sDPad = -1;


    //shooter data
    double hoodPosition;
    double turretPosition;
    double flywheelVelocity;
    bool readyShoot = false;
    bool isZero = false;

    //limelight data
    double xOffset;
    double yOffset;
    double calcHoodPos;

    //gyro data
    double rawAngle;
    double robotAngle; // mod by 360


    // auton stuff
    int autonStep  = 0;

    AutonSelect autonSelect{autonSelect_potato};
    DriveMode driveMode{driveMode_potato};  // should have a default?

    //turn
    double desiredAngleDiff; 
    double radius;
    double finalAngle;
    double initialAngle;

    // drive_forward
    double desiredDBDist;
    double initialLDBPos;
    double initialRDBPos;
    double currentLDBPos;
    double currentRDBPos;
    // prolly wanna check the other two encoders


    
} ;