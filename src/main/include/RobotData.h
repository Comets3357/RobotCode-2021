#pragma once

// auton mode
enum AutonSelect
{
    autonSelect_potato,
    autonSelect_exitInitLine,
    autonSelect_shootAndDrive,
    autonSelect_shootAndCollectBalls, // pretty much the same as trench run
    autonSelect_trenchRun,
    autonSelect_goofy // temporary
};

// this is for drivebase auton
enum DriveMode
{
    driveMode_teleop,
    driveMode_potato,
    driveMode_initDriveForward,
    driveMode_driveForward,
    driveMode_arc,
    driveMode_initArc
};

//could be separated into all separate files for the data *from* each subsystem
//commented out variables are not in use
struct RobotData 
{
    // timer
    double seconds;

    //controller data

    bool manualMode = false;
    bool shift; //shift for more button options
    bool shootingMode;
    bool limelightOn;

    //L = left, R = right, p = primary, s = secondary, Btn = button

    //primary

    // this will have merge conflict with climb's pLShoulderBtn
    bool pLShoulderBtn;

    double pLXStick;
    double pLYStick = 0;
    double pRXStick;
    double pRYStick = 0;
    bool pLStickBtn;
    bool pRStickBtn;

    double pLTrigger;
    double pRTrigger;
    bool pLBumper;
    bool pRBumper;

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
    static const int shootingBtn = 90;
    int targetVelocity = 0;
    bool readyShoot = false; //when flywheel reaches velocity and everything is aimed

    //drive base
    double Ldrive;
    double Rdrive;


    //limelight data
    double xOffset;
    double yOffset;
    double calcHoodPos;
    bool validTarget;
    int pipeline; //for LED power

    //gyro data
    //greater angle means clockwise
    double rawAngle;
    double robotAngle; // mod by 360


    // auton stuff
    int autonStep  = 0;
    AutonSelect autonSelect;    // only for diagnostics purposes; do not use
    DriveMode driveMode{driveMode_teleop};  // should have a default?

    //turn
    double desiredAngleDiff; 
    double arcRadius;   // the inside radius. for a turn in place use radius -1
    double sideRatio;
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