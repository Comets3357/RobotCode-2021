#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc2/command/SubsystemBase.h>


class LimelightSubsystem : public frc2::SubsystemBase {
    
    public:

        void RobotInit();
        void Periodic(RobotData &robotData);

        double getHorizontalOffset();
        double getVerticalOffset();
        int getTarget();
        double calcHoodPOS(double verticalOffset, RobotData &robotData);
        double calcTurretPOS(double horOffset);
        int getPipeline(double verticalOffset);

    private:   

};