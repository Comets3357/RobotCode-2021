#pragma once

#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
//#include <frc/DoubleSolenoid.h>
#include <frc/Solenoid.h>

#include "RobotData.h"


class IntakeSubsystem {
    
    public:

        void Init();
        void Periodic(frc::Joystick &sStick,IndexerSubsystem &index);
        void SetPivot(int Position);

    private:

        int shootPOV;
        
        void setIntakeRollers(double power);
        void setPiston(bool direction);
        void semiAutoMode(RobotData &robotData);
        void manualMode(RobotData &robotData);

        /* bool goBack = false;
        bool manualIntakeButtonDown = false;
        bool manualIntake = false;
        bool wheelsIntake = false;
        bool run = true;
        double pkP = 0.02, pkI = 0, pkD = 0, pkIz = 0, pkFF = 0, pkMaxOutput = 1, pkMinOutput = -1;
        double wkP = 1, wkI = 0, wkD = 0, wkIz = 0, wkFF = 0, wkMaxOutput = 1, wkMinOutput = -1;

        int shiftFactor = 1;


        static const int intakeRollersID = 32;
        rev::CANSparkMax rollers{intakeRollersID, rev::CANSparkMax::MotorType::kBrushless};

        //frc::DoubleSolenoid solenoidOne{1, 2};
        frc::Solenoid solenoidOne{0};

       /*  rev::CANPIDController intakePivot_pidController = intakePivot.GetPIDController();
        rev::CANPIDController wheels_pidController = wheels.GetPIDController(); */

};