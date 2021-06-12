#pragma once

//could be separated into all separate files for the data *from* each subsystem
//commented out variables are not in use
struct RobotData 
{
    //controller data

    bool manualMode;
    bool shift;
    bool shootingMode;

    //L = left, R = right, p = primary, s = secondary, Btn = button
    //primary

    double pLXStick;
    double pLYStick;
    double pRXStick;
    double pRYStick;
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
    double sLYStick;
    double sRXStick;
    double sRYStick;
    bool sLStickBtn;
    bool sRStickBtn;

    double sLTrigger;
    double sRTrigger;
    bool sLBumper;
    bool sRBumper;

    bool sXBtn;
    bool sYBtn;
    bool sABtn;
    bool sBBtn;

    bool sLCenterBtn;
    bool sRCenterBtn;

    int sDPad;


    //shooter data
    double hoodPosition;
    double turretPosition;
    double flywheelVelocity;
    bool readyShoot = false;
    bool isZero = false;
    static const int shootingBtn = 90;
    int targetVelocity = 0;


    //limelight data
    double xOffset;
    double yOffset;
    double calcHoodPos;



    
} ;