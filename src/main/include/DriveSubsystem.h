#pragma once

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>
#include <adi/ADIS16448_IMU.h>

#include "RobotData.h"


class DriveSubsystem {
    
    public: 
        void Init();
        void Periodic(RobotData &robotData);
        void Disabled();

    private:

        double lDrive = 0;
        double rDrive = 0;
        const double cStraight = 1;
        const double cTurn = 1;
        bool climbMode = false;

        void updateData(RobotData &robotData);
        
        void teleopControl(RobotData &robotData); // converts js inputs to desire velocity
        void setVelocity(RobotData &robotData);

        void courseCorrectedDrive(RobotData &robotData); // was only used for pid testing

        void potato(RobotData &robotData);
        void initDriveForward(RobotData &robotData);
        void driveForward(RobotData &robotData);
        void initArc(RobotData &robotData);
        //void arc(RobotData &robotData); // DOES NOT WORK
        void turnInPlace(RobotData &robotData);
        


//motors:
        static const int leftLeadDeviceID = 1, leftFollowDeviceID = 2, rightLeadDeviceID = 3, rightFollowDeviceID = 4;
        rev::CANSparkMax dbLM{leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbRM{rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbLS{leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbRS{rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};

        rev::CANEncoder dbRMEncoder = dbRM.GetEncoder();
        rev::CANEncoder dbLMEncoder = dbLM.GetEncoder();

        rev::CANPIDController dbRMPID = dbRM.GetPIDController();
        rev::CANPIDController dbLMPID = dbLM.GetPIDController();
        

//gyro:
        frc::ADIS16448_IMU gyro{};

}; 
