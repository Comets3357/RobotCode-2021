#pragma once

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>

#include "RobotData.h"


class ControlpanelSubsystem {
    
    public: 
        void Init();
        void Periodic(RobotData &RobotData);
        void Disabled();

    private:


//motors:
        static const int cpManipulatorID = 41;
        rev::CANSparkMax cpManipulator{cpManipulatorID, rev::CANSparkMax::MotorType::kBrushless};
}; 
