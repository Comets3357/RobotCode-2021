#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc2/command/SubsystemBase.h>

#include "RobotData.h"


class DriveSubsystem : frc2::SubsystemBase {
    
    public: 
        void Init();
        void Periodic(RobotData &RobotData);

    private:

        double lDrive = 0;
        double rDrive = 0;
        bool climbMode = false;


//motors:
        static const int leftLeadDeviceID = 1, leftFollowDeviceID = 2, rightLeadDeviceID = 3, rightFollowDeviceID = 4;
        rev::CANSparkMax dbLM{leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbRM{rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbLS{leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbRS{rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};

        /* rev::CANPIDController dbRM_pidController = dbRM.GetPIDController();
        rev::CANPIDController dbLM_pidController = dbLM.GetPIDController();
        rev::CANPIDController dbRS_pidController = dbLM.GetPIDController();
        rev::CANPIDController dbLS_pidController = dbLM.GetPIDController(); */


}; 
