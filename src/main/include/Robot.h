//Tells the compiler to not include the header files multiple times
#pragma once

//Header files from FRC
#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc/Timer.h>

//Header files from us
#include "Auton.h"
#include "IntakeSubsystem.h"
#include "DriveSubsystem.h"
#include "IndexerSubsystem.h"
#include "ShooterSubsystem.h"
#include "Controller.h"
#include "LimelightSubsystem.h"
#include "ControlpanelSubsystem.h"

#include "RobotData.h"



//Robot class inherits from TimedRobot
class Robot : public frc::TimedRobot {

  public:
      bool manualMode = false;

      void RobotInit() override;
      void RobotPeriodic() override;
      void AutonomousInit() override;
      void AutonomousPeriodic() override;
      void TeleopPeriodic() override;
      void DisabledInit() override;

  private:
      DriveSubsystem db{};
      ShooterSubsystem shooter{};
      IndexerSubsystem indexer{};
      IntakeSubsystem intake{};
      LimelightSubsystem limelight{};
      ControlpanelSubsystem controlpanel{};

      Controller control{};
      Auton auton{};
      RobotData robotData{};

      






};

//Notes:
//GetRawButton and GetRawButtonPressed are not the same
//button index starts at 1




