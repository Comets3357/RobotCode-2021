#pragma once

#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include "rev/CANSparkMax.h"
#include <frc2/command/SubsystemBase.h>
#include "Controller.h"

class Manual : public frc2::SubsystemBase {
    
    public:

        void Init();
        void Periodic(Controller &control, frc::Joystick &sStick, IndexerSubsystem &index, ShooterSubsystem &shooter, IntakeSubsystem &intake);

    private:


};