#pragma once

#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc/Solenoid.h>

#include "RobotData.h"


class IntakeSubsystem {
    
    public:

        void Init();
        void Periodic(RobotData &robotData);

    private:

        int shootPOV;
        
        void setIntakeRollers(double power);
        void setPiston(bool direction);
        bool getPiston();
        void semiAutoMode(RobotData &robotData);
        void manualMode(RobotData &robotData);

        int shiftFactor = 1;

        static const int intakeRollersID = 32;
        rev::CANSparkMax rollers{intakeRollersID, rev::CANSparkMax::MotorType::kBrushless};

        frc::Solenoid solenoidOne{0};

};