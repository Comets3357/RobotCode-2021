#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>

#include "RobotData.h"


class ShooterSubsystem {
    
    public:

        void Init();
        void Periodic(RobotData &robotData);
        void Disabled();

    private:

        void updateData(RobotData &robotData);
        void semiAutoMode(RobotData &robotData);
        void manualMode(RobotData &robotData);


        double getHoodPos();
        double getTurretPos();
        double getWheelPos();
        double getWheelVel();
        bool getTurretLimitSwitch();
        bool getHoodLimitSwitch();

        void setShooterPID(rev::CANPIDController motor, int pidSlot, double p, double i, double d, double ff);
        void setHood(double power);
        void setTurret(double power);
        void setWheel(double power);
        void setHoodPos(double pos);
        void setTurretPos(double pos);
        
        bool shooting = false;

        int secondaryPOVArrayInput;
        int turretSequence = 0;
        int shootPOV;

        bool intakeEncoderPositionZero;

        static const int shooterWheelMID = 21;
        static const int shooterWheelSID = 20;
        static const int shooterHoodID = 22;
        static const int shooterTurretID = 23;


//motors:
        rev::CANSparkMax shooterWheelM{shooterWheelMID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax shooterWheelS{shooterWheelSID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax shooterHood{shooterHoodID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax shooterTurret{shooterTurretID, rev::CANSparkMax::MotorType::kBrushless};

//encoders;
        rev::CANEncoder shooterHoodPOS = shooterHood.GetEncoder();
        rev::CANEncoder shooterTurretPOS = shooterTurret.GetEncoder();
        rev::CANEncoder shooterWheelMPOS = shooterWheelM.GetEncoder();
        rev::CANEncoder shooterWheelSPOS = shooterWheelS.GetEncoder();

//limit switches;
        rev::CANDigitalInput turretReverseLimit = shooterTurret.GetReverseLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed);
        rev::CANDigitalInput hoodReverseLimit = shooterHood.GetReverseLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed);

//PIDs;
        rev::CANPIDController shooterWheelMPID = shooterWheelM.GetPIDController();
        rev::CANPIDController shooterWheelSPID = shooterWheelS.GetPIDController();
        rev::CANPIDController shooterHoodPID = shooterHood.GetPIDController();
        rev::CANPIDController shooterTurretPID= shooterTurret.GetPIDController();




        /* rev::CANPIDController shooterFlywheelM_pidController = shooterFlywheelM.GetPIDController();
        rev::CANPIDController shooterFlywheelS_pidController = shooterFlywheelS.GetPIDController();
        rev::CANPIDController shooterHood_pidController = shooterHood.GetPIDController();
        rev::CANPIDController shooterTurret_pidController = shooterTurret.GetPIDController();
        rev::CANPIDController shooterKick_pidController = shooterKick.GetPIDController(); */
    
        



};