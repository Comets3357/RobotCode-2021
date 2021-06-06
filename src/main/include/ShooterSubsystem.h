#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc2/command/SubsystemBase.h>

#include "RobotData.h"


class ShooterSubsystem : public frc2::SubsystemBase {
    
    public:

        void Init();
        void Periodic(RobotData &robotData);
        

        //pass limelight and indexer values through
        /* bool turretInRange(LimelightSubsystem &limelight); //function definition
        bool hoodInRange(LimelightSubsystem &limelight);
        void setShooterFlyWheel(double power); */
        

    private:

        int shootPOV;

        void updateData(RobotData &robotData);
        void semiAutoMode(RobotData &robotData);
        void manualMode(RobotData &robotData);


        double getHoodPos();
        double getTurretPos();
        double getWheelPos();
        double getWheelVel();
        bool getTurretLimitSwitch();
        bool getHoodLimitSwitch();

        void setHood(double power);
        void setTurret(double power);
        void setWheel(double power);
        void setHoodPos(double pos);
        void setTurretPos(double pos);
        
        bool shooting = false;

        int secondaryPOVArrayInput;
        bool intakeEncoderPositionZero;
        double manualIntakePivotInput;
        int turretSequence = 0;
        //double whereShooterMoves;
        /* double fkP = 0.0007, fkI = 0, fkD = 0, fkIz = 0.0002, fkFF = 0, fkMaxOutput = 1, fkMinOutput = -1;
        double kkP = 0.00035, kkI = 0, kkD = 0, kkIz = 0.0002, kkFF = 0, kkMaxOutput = 1, kkMinOutput = -1;
        double tkP = 0.05, tkI = 0, tkD = 0, tkIz = 0, tkFF = 0, tkMaxOutput = 1, tkMinOutput = -1;
        double hkP = 0.04, hkI = 0, hkD = 0, hkIz = 0, hkFF = 0, hkMaxOutput = 1, hkMinOutput = -1;
 */

        //tried to start an encoder to get the position of the pivot
        static const int shooterWheelMID = 21;
        static const int shooterWheelSID = 20;
        static const int shooterHoodID = 22;
        static const int shooterTurretID = 25;


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

        /* rev::CANPIDController shooterFlywheelM_pidController = shooterFlywheelM.GetPIDController();
        rev::CANPIDController shooterFlywheelS_pidController = shooterFlywheelS.GetPIDController();
        rev::CANPIDController shooterHood_pidController = shooterHood.GetPIDController();
        rev::CANPIDController shooterTurret_pidController = shooterTurret.GetPIDController();
        rev::CANPIDController shooterKick_pidController = shooterKick.GetPIDController(); */
    
        


};