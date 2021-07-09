#pragma once

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"
#include "RobotData.h"


class ControlpanelSubsystem {
    
    public: 
        void Init();
        void Periodic(RobotData &RobotData);
        void Disabled();

        void semiAutoMode(RobotData &robotData);
        void manualMode(RobotData &robotData);

    private:


//motors:
        static const int cpManipulatorID = 41;
        rev::CANSparkMax cpManipulator{cpManipulatorID, rev::CANSparkMax::MotorType::kBrushless};

        static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
        rev::ColorSensorV3 m_colorSensor{i2cPort};
        rev::ColorMatch m_colorMatcher;

        static constexpr frc::Color kBlueTarget = frc::Color(0.1763, 0.4508, 0.3728);
        static constexpr frc::Color kGreenTarget = frc::Color(0.2161, 0.5321, 0.2514);
        static constexpr frc::Color kRedTarget = frc::Color(0.3546, 0.4361, 0.2093);
        static constexpr frc::Color kYellowTarget = frc::Color(0.2967, 0.5427, 0.1606);


}; 
