#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc/shuffleboard/Shuffleboard.h>

#include "RobotData.h"
#include "Diagnostics.h"
#include <frc/shuffleboard/Shuffleboard.h>


class IndexerSubsystem {
    
    public:
        void RobotInit();
        void Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData);
        void DisabledInit();


    private:
        void setCenterSpindle (double power);
        void setOmniWheel (double power); 
        void semiAutoMode(RobotData &robotData);
        void manualMode(RobotData &robotData);
        

        void updateDiagnostics(DiagnosticsData &diagnosticsData);

        double getSpinnerVel();


//state variables:
        int shootPOV = -1;
        int omniDir = 1;
        int tickCount = 0;

        
//motors:
        static const int centerSpindleID = 11, omniWheelID = 12;
        rev::CANSparkMax centerSpindle{centerSpindleID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax omniWheel{omniWheelID, rev::CANSparkMax::MotorType::kBrushless};


//encoders:
        rev::CANEncoder centerSpindlePOS = centerSpindle.GetEncoder();
        rev::CANPIDController centerSpindle_pidController = centerSpindle.GetPIDController();

        rev::CANEncoder omniWheelPOS = omniWheel.GetEncoder();
 
};