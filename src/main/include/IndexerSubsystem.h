#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include "rev/CANSparkMax.h"
#include <frc2/command/SubsystemBase.h>

class IndexerSubsystem : public frc2::SubsystemBase {
    
    public:


        void Init();
        void SetSpinner (double power); //function
        void SetSide (double power); //function
        double getSpinnerVel();


    private:
        
//motors:
        static const int centerSpindleID = 11, sideWheelID = 12;
        rev::CANSparkMax centerSpindle{centerSpindleID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax sideWheel{sideWheelID, rev::CANSparkMax::MotorType::kBrushless};


//encoder:
        rev::CANEncoder centerSpindlePOS = centerSpindle.GetEncoder();
        rev::CANPIDController centerSpindle_pidController = centerSpindle.GetPIDController();
 
};