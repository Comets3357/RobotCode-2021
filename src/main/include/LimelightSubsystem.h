#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include "rev/CANSparkMax.h"
#include <frc2/command/SubsystemBase.h>

#include "Diagnostics.h"


class LimelightSubsystem : public frc2::SubsystemBase {
    
    public:

        void Init();
        void Periodic(RobotData &robotData);

        double getHorizontalOffset();
        double getVerticalOffset();
        double calcHoodPOS(double verticalOffset);

    private:

        
        //double getAngle_Horizontal();
        double targetOffsetAngle_Horizontal; 
        double targetOffsetAngle_Vertical;
        //double targetArea;
        //double targetSkew; 
        double shooterHoodPOS;

        //double TurretPOS;

};