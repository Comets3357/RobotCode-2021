#pragma once

#include <rev/CANSparkMax.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <adi/ADIS16448_IMU.h>

#include "RobotData.h"

class ClimbSubsystem {
    
    public:

        void RobotInit();
        void Periodic(RobotData &robotData);

        bool initiationRunning = false;
        bool initiated = false;

        bool climbing = false;

        bool movingLeft = false;

        bool lockToggle = true;

        int zeroLoop = 0;


        void semiAutoMode(RobotData &robotData);
        void manualMode(RobotData &robotData);

        void climbRunToPosition(double pos, double pow);
        void climbLevel(double degree, double degreeRange);

        // Change SparkMax IDs
        static const int climbArmRID = 34;
        static const int climbArmLID = 35;
        rev::CANSparkMax climbArmR{climbArmRID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax climbArmL{climbArmLID, rev::CANSparkMax::MotorType::kBrushless};

        rev::CANEncoder climbArmRPos = climbArmR.GetEncoder();
        rev::CANEncoder climbArmLPos = climbArmL.GetEncoder();

        // Change CAN IDs
        frc::DoubleSolenoid solenoidArm{3,1};

        frc::Solenoid solenoidLockR{2};
        frc::Solenoid solenoidLockL{4};

        rev::CANDigitalInput climbArmRLimit = climbArmR.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen);

        rev::CANDigitalInput climbArmLLimit = climbArmL.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen);

        //rev::CANDigitalInput climbArmRLimit = climbArmR.GetReverseLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed);
        // frc::DigitalInput climbArmLLimit {0};

        // frc::ADIS16448_IMU imu{};
};