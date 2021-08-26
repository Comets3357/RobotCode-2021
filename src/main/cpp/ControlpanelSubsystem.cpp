#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/util/Color.h>
#include <frc/DriverStation.h>

void ControlpanelSubsystem::RobotInit()
{

  cpManipulator.RestoreFactoryDefaults();

  cpManipulator.SetInverted(false);

  cpManipulator.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  cpManipulator.SetSmartCurrentLimit(45);

  cpManipulator.Set(0);

  m_colorMatcher.AddColorMatch(kBlueTarget);
  m_colorMatcher.AddColorMatch(kGreenTarget);
  m_colorMatcher.AddColorMatch(kRedTarget);
  m_colorMatcher.AddColorMatch(kYellowTarget);
}

void ControlpanelSubsystem::Periodic(RobotData &robotData)
{
  frc::SmartDashboard::PutNumber("armup", armUp);
  frc::SmartDashboard::PutNumber("armtoggle", armToggle);
  frc::SmartDashboard::PutNumber("armuponrequest", robotData.armUpOnRequest);
  frc::SmartDashboard::PutNumber("lastarm", robotData.lastArmUp);
  if (robotData.climbMode)
  {
    if (robotData.manualMode)
    {
      manualMode(robotData);
    }
    else
    {
      semiAutoMode(robotData);
    }
  }
}

void ControlpanelSubsystem::semiAutoMode(RobotData &robotData)
{

  std::string gameData;
  gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
  if (gameData.length() > 0)
  {
    switch (gameData[0])
    {
    case 'B':
      targetColor = "Red";
      break;
    case 'G':
      targetColor = "Yellow";
      break;
    case 'R':
      targetColor = "Blue";
      break;
    case 'Y':
      targetColor = "Green";
      break;
    default:
      targetColor = " ";
      break;
    }
  }

  if (robotData.sABtn)
  {
    if (rotatingToggle)
    {
      if (!rotating)
      {
        rotating = true;
        cpManipulator.Set(0.2);
      }
      else if (rotating)
      {
        rotating = false;
        cpManipulator.Set(0);
        colorsPast = 0;
        lastColor = " ";
      }
      rotatingToggle = false;
    }
  }
  else
  {
    rotatingToggle = true;
  }

  if (robotData.sBBtn)
  {
    goingToColor = true;
  }

  frc::Color detectedColor = m_colorSensor.GetColor();

  std::string colorString;
  double confidence = 0.0;
  frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

  if (matchedColor == kBlueTarget)
  {
    colorString = "Blue";
  }
  else if (matchedColor == kRedTarget)
  {
    colorString = "Red";
  }
  else if (matchedColor == kGreenTarget)
  {
    colorString = "Green";
  }
  else if (matchedColor == kYellowTarget)
  {
    colorString = "Yellow";
  }
  else
  {
    colorString = "Unknown";
  }

  if (goingToColor)
  {
    if (colorString == targetColor)
    {
      cpManipulator.Set(0);
      goingToColor = false;
    }
    else
    {
      cpManipulator.Set(0.1);
    }
  }

  if (rotating && lastColor != colorString)
  {
    colorsPast += 1;
    lastColor = colorString;
  }

  if (rotating && colorsPast > 31)
  {
    rotating = false;
    colorsPast = 0;
    cpManipulator.Set(0);
    lastColor = " ";
  }

  if (robotData.sXBtn)
  {

    if (armToggle)
    {
      if (!armUp)
      {
        robotData.armUpOnRequest = true;
        armUp = true;
        robotData.lastArmUp = true;
      }
      else
      {
        robotData.armUpOnRequest = true;
        armUp = false;
        robotData.lastArmUp = false;
      }
    }
    armToggle = false;
  }
  else
  {
    armToggle = true;
  }

  /**
     * Open Smart Dashboard or Shuffleboard to see the color detected by the 
     * sensor.
     */
  frc::SmartDashboard::PutNumber("Red", detectedColor.red);
  frc::SmartDashboard::PutNumber("Green", detectedColor.green);
  frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
  frc::SmartDashboard::PutNumber("Confidence", confidence);
  frc::SmartDashboard::PutString("Detected Color", colorString);
}

void ControlpanelSubsystem::manualMode(RobotData &robotData)
{
  if (false)
  {
    cpManipulator.Set(0.2);
  }
}

void ControlpanelSubsystem::Disabled()
{
  cpManipulator.Set(0);
}
