//Tells the compiler to not include the header files multiple times
#pragma once

//Header files from FRC
#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc2/command/SubsystemBase.h>

//Header files from us
#include "IntakeSubsystem.h"
#include "DriveSubsystem.h"
#include "IndexerSubsystem.h"
#include "ShooterSubsystem.h"
#include "Controller.h"
#include "LimelightSubsystem.h"
#include "Auton.h"

#include "RobotData.h"



//Robot class inherits from TimedRobot
class Robot : public frc::TimedRobot {

  public:
      bool manualMode = false;

      void RobotInit() override;
      void RobotPeriodic() override;
      void AutonomousPeriodic() override;
      void TeleopPeriodic() override;
      void DisabledInit() override;


      DriveSubsystem db{};
      ShooterSubsystem shooter{};
      IndexerSubsystem indexer{};
      IntakeSubsystem intake{};
      LimelightSubsystem limelight{};

      Controller control{};
      Auton auton{};
      RobotData robotData{};




  private:



};

//Notes:
//GetRawButton and GetRawButtonPressed are not the same
//button index starts at 1




