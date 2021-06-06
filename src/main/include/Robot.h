//Tells the compiler to not include the header files multiple times
#pragma once

//Header files from FRC
#include <frc/TimedRobot.h>
#include <frc/Joystick.h>
#include "rev/CANSparkMax.h"
#include <frc2/command/SubsystemBase.h>

//Header files from us
#include "IntakeSubsystem.h"
#include "DriveSubsystem.h"
#include "IndexerSubsystem.h"
#include "ShooterSubsystem.h"
#include "Auto.h"
#include "Manual.h"
#include "Controller.h"



//Robot class inherits from TimedRobot
class Robot : public frc::TimedRobot {

  public:
      bool manualMode = false;
      void RobotInit() override;
      void TeleopPeriodic() override;

      //frc::Joystick mainStick{0}; //primary controller
      frc::Joystick sStick{0}; //secondary controller
      frc::Joystick mainStick{1};

      DriveSubsystem db{};
      ShooterSubsystem shooter{};
      IndexerSubsystem indexer{};
      IntakeSubsystem intake{};
      Manual manual{};
      Auto autoo{};
      Controller control{};



  private:



};

//Notes:
//GetRawButton and GetRawButtonPressed are not the same
//button index starts at 1




