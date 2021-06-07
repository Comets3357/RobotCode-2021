#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>

#include "RobotData.h"

class IndexerSubsystem {
    
    public:
        void Init();
        void Periodic(RobotData &robotData);

    private:
        void setCenterSpindle (double power);
        void setOmniWheel (double power); 
        void semiAutoMode(RobotData &robotData);
        void manualMode(RobotData &robotData);

        double getSpinnerVel();


//state variables:
        int shootPOV = -1;
        int omniDir = 1;

        
//motors:
        static const int centerSpindleID = 11, omniWheelID = 12;
        rev::CANSparkMax centerSpindle{centerSpindleID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax omniWheel{omniWheelID, rev::CANSparkMax::MotorType::kBrushless};


//encoders:
        rev::CANEncoder centerSpindlePOS = centerSpindle.GetEncoder();
        rev::CANPIDController centerSpindle_pidController = centerSpindle.GetPIDController();
 
};