#pragma once

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>
#include <frc/BuiltInAccelerometer.h>
#include <frc/PowerDistributionPanel.h>
#include <adi/ADIS16448_IMU.h>
#include <frc/Compressor.h>

#include "RobotData.h"
#include "Diagnostics.h"


class DriveSubsystem {
    
    public: 
        void RobotInit();
        void Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData);
        void DisabledInit();

    private:

        double lDrive = 0;
        double rDrive = 0;

        void updateData(RobotData &robotData);
        void updateDiagnostics(DiagnosticsData &diagnosticsData);

        // void courseCorrectedDrive(RobotData &robotData); // was only used for pid testing

        void teleopControl(RobotData &robotData);
        void potato(RobotData &robotData);
        void initDriveStraight(RobotData &robotData);
        void driveStraight(RobotData &robotData);
        void initTurnInPlace(RobotData &robotData);
        void turnInPlace(RobotData &robotData);
        // void turnToAngle(RobotData &robotData);

        void setVelocity(RobotData &robotData);
        void courseCorrection(bool isForward, RobotData &robotData); //ACTUAL course correction
        


//motors:
        static const int leftLeadDeviceID = 1, leftFollowDeviceID = 2, rightLeadDeviceID = 3, rightFollowDeviceID = 4;
        
        rev::CANSparkMax dbLM{leftLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbRM{rightLeadDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbLS{leftFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax dbRS{rightFollowDeviceID, rev::CANSparkMax::MotorType::kBrushless};

        rev::CANEncoder dbRMEncoder = dbRM.GetEncoder();
        rev::CANEncoder dbLMEncoder = dbLM.GetEncoder();
        rev::CANEncoder dbRSEncoder = dbRS.GetEncoder();
        rev::CANEncoder dbLSEncoder = dbLS.GetEncoder();

        rev::CANPIDController dbRMPID = dbRM.GetPIDController();
        rev::CANPIDController dbLMPID = dbLM.GetPIDController();
        
// accelerometer
        frc::BuiltInAccelerometer accelerometer{};

// PDP
        frc::PowerDistributionPanel pdp{0};

//gyro:
        frc::ADIS16448_IMU gyro{};

// compressor
        frc::Compressor compressor{0};

}; 
