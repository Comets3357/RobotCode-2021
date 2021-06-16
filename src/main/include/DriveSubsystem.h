#pragma once

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>
#include <adi/ADIS16448_IMU.h>

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
        //void updateGyro(RobotData &robotData); not in use

        //doesn't work
        //void setDrivePID(rev::CANPIDController &motor, int p, int i, int d, int ff);

        void teleopControl(RobotData &robotData);
        void setDrive(RobotData &robotData);
        void courseCorrectedDrive(RobotData &robotData);

        void potato(RobotData &robotData);
        void initDriveForward(RobotData &robotData);
        void driveForward(RobotData &robotData);
        void arc(RobotData &robotData);
        void initArc(RobotData &robotData);
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
