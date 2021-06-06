#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include "rev/CANSparkMax.h"
#include <frc2/command/SubsystemBase.h>

class Auto : public frc2::SubsystemBase {
    
    public:

        

        void Init();
        void Periodic(frc::Joystick &sStick, IndexerSubsystem &index, ShooterSubsystem &shooter, IntakeSubsystem &intake);

    private:
        int sideWheelDirection = 1;
        int secondaryPOVArrayInput;


};