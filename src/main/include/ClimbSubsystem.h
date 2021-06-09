#pragma once

#include <rev/CANSparkMax.h>
#include <frc/Solenoid.h>
#include <adi/ADIS16448_IMU.h>

#include "RobotData.h"

class IntakeSubsystem {
    
    public:

        void Init();
        void Periodic(RobotData &robotData);

    private:

        void setPistonR(bool direction);
        void setPistonL(bool direction);
        void setLockR(bool direction);
        void setLockL(bool direction);

        // Change SparkMax IDs
        static const int climbArmRID = 99;
        static const int climbArmLID = 99;
        rev::CANSparkMax climbArmR{climbArmRID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax climbArmL{climbArmLID, rev::CANSparkMax::MotorType::kBrushless};

        // Change CAN IDs
        frc::Solenoid solenoidArmR{3};
        frc::Solenoid solenoidArmL{4};

        frc::Solenoid solenoidLockR{5};
        frc::Solenoid solenoidLockL{6};
};