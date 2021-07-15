#pragma once

#include <rev/CANSparkMax.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <adi/ADIS16448_IMU.h>

#include "RobotData.h"
#include "Diagnostics.h"

class ClimbSubsystem {
    
    public:

        void RobotInit();
        void Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData);

        void updateDiagnostics(DiagnosticsData &diagnosticsData);

        bool initiationRunning = false;
        bool initiated = false;

        int startingPhase = 0;

        double voltageTargetL;
        double voltageTargetR;

        int timer;

        bool movingLeft = false;

        bool lockToggle = true;

        int zeroLoop = 0;


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
        frc::DoubleSolenoid solenoidArm{3,1};

        frc::Solenoid solenoidLockR{2};
        frc::Solenoid solenoidLockL{4};

        rev::CANDigitalInput climbArmRLimit = climbArmR.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen);
        //rev::CANDigitalInput climbArmRLimit = climbArmR.GetReverseLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed);
        frc::DigitalInput climbArmLLimit {0};

        // frc::ADIS16448_IMU imu{};
};