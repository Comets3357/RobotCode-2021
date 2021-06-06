#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include "rev/CANSparkMax.h"
#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>


class IntakeSubsystem : public frc2::SubsystemBase {
    
    public:

        void Init();
        void setIntakeWheels(double power);
        void setPiston(bool direction);

    private:

        /* bool goBack = false;
        bool manualIntakeButtonDown = false;
        bool manualIntake = false;
        bool wheelsIntake = false; */
       /*  double pkP = 0.02, pkI = 0, pkD = 0, pkIz = 0, pkFF = 0, pkMaxOutput = 1, pkMinOutput = -1;
        double wkP = 1, wkI = 0, wkD = 0, wkIz = 0, wkFF = 0, wkMaxOutput = 1, wkMinOutput = -1; */

        int shiftFactor = 1;


        static const int intakeWheelsID = 32;
        rev::CANSparkMax wheels{intakeWheelsID, rev::CANSparkMax::MotorType::kBrushless};

        frc::DoubleSolenoid solenoidOne{1, 2};
        

       /*  rev::CANPIDController intakePivot_pidController = intakePivot.GetPIDController();
        rev::CANPIDController wheels_pidController = wheels.GetPIDController(); */

};