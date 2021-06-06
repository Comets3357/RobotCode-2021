#pragma once

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>

#include "RobotData.h"


class DriveSubsystem {
    
    public: 
        void Init();
        void Periodic(RobotData &robotData);
        void Auton(int select, RobotData &robotData);
        void Disabled();

    private:

        double lDrive = 0;
        double rDrive = 0;
        bool climbMode = false;

        void updateData(RobotData &robotData);

        void setDrive(double lDrive, double rDrive);

        void potato(RobotData &robotData);
        void driveForward(RobotData &robotData);
        


//motors:
        static const int leftLeadDeviceID = 1, leftFollowDeviceID = 2, rightLeadDeviceID = 3, rightFollowDeviceID = 4;
        rev::CANSparkMax dbLM{leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbRM{rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbLS{leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbRS{rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};

        rev::CANEncoder dbRMEncoder = dbRM.GetEncoder();
        rev::CANEncoder dbLMEncoder = dbLM.GetEncoder();

        /* rev::CANPIDController dbRM_pidController = dbRM.GetPIDController();
        rev::CANPIDController dbLM_pidController = dbLM.GetPIDController(); */
        


}; 
