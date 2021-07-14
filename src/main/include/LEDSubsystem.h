#pragma once

#include "RobotData.h"
#include "ctre/Phoenix.h"

class LEDSubsystem {

    public:

        void RobotInit();
        void Periodic(RobotData &robotData);
        void DisabledInit();

    private:

        void SetColor(double r, double g, double b);

        CANifier LED {0};

};