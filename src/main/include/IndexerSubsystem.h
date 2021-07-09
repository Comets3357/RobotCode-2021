#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include "rev/CANSparkMax.h"
#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>

#include "RobotData.h"

class IndexerSubsystem {
    
    public:


        void Init();
        void Periodic(RobotData &robotData);

        void setIndexerBelt(double power); //function
        bool getGoBack();
        void setGoBack(bool GoBack);
        bool IntakeRun();
        void Reset();
        double getPOS();

    private:

        bool manualIndexerInput = false;
        bool goBack = false;
        int powerCells = 0;
        bool ballIn = false;
    public:
        bool intakeRun = true;
        //0 = not started, 1 = running, 2 = done
        int ball4 = 0;
        int ball5 = 0;
        int ball3 = 0;
//motors:
        static const int centerSpindleID = 11, omniWheelID = 12;
        rev::CANSparkMax centerSpindle{centerSpindleID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax omniWheel{omniWheelID, rev::CANSparkMax::MotorType::kBrushless};


//encoder:
        rev::CANEncoder indexerBeltPOS = indexerBelt.GetEncoder();

        rev::CANPIDController indexerBelt_pidController = indexerBelt.GetPIDController();
//sensor
        frc::DigitalInput indexSensor{2};
        frc::DigitalInput indexSensor2{3};
};