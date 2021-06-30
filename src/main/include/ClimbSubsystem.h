#pragma once

#include <rev/CANSparkMax.h>
#include <frc/Solenoid.h>
#include <adi/ADIS16448_IMU.h>

#include "RobotData.h"

class ClimbSubsystem {
    
    public:

        void Init();
        void Periodic(RobotData &robotData);

        bool initiationRunning = false;
        bool initiated = false;

        int startingPhase = 0;

        double voltageTargetL;
        double voltageTargetR;

        int timer;

        bool movingLeft = false;

        bool lockToggle = true;

    private:

        void semiAutoMode(RobotData &robotData);
        void manualMode(RobotData &robotData);

        void setPistonR(bool direction);
        void setPistonL(bool direction);
        void setLockR(bool direction);
        void setLockL(bool direction);

        // Change SparkMax IDs
        static const int climbArmRID = 34;
        static const int climbArmLID = 35;
        rev::CANSparkMax climbArmR{climbArmRID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax climbArmL{climbArmLID, rev::CANSparkMax::MotorType::kBrushless};

        rev::CANEncoder climbArmRPos = climbArmR.GetEncoder();
        rev::CANEncoder climbArmLPos = climbArmL.GetEncoder();

        // Change CAN IDs
        frc::Solenoid solenoidArmR{1};
        frc::Solenoid solenoidArmL{3};

        frc::Solenoid solenoidLockR{2};
        frc::Solenoid solenoidLockL{4};

        //frc::ADIS16448_IMU imu{};
};