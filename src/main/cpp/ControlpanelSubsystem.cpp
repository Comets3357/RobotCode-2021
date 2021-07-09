#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/util/color.h>



void ControlpanelSubsystem::Init(){

    cpManipulator.RestoreFactoryDefaults();
    //we inverted the right side and set motors to follow each other
    cpManipulator.SetInverted(false);

    cpManipulator.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    cpManipulator.SetSmartCurrentLimit(45);

    cpManipulator.Set(0);

    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);

}

void ControlpanelSubsystem::Periodic(RobotData &robotData){
    if(robotData.manualMode){
        manualMode(robotData);
    } else {
        semiAutoMode(robotData);
    }

} 

void ControlpanelSubsystem::semiAutoMode(RobotData &robotData){
    

    frc::Color detectedColor = m_colorSensor.GetColor();

    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

    if (matchedColor == kBlueTarget) {
      colorString = "Blue";
    } else if (matchedColor == kRedTarget) {
      colorString = "Red";
    } else if (matchedColor == kGreenTarget) {
      colorString = "Green";
    } else if (matchedColor == kYellowTarget) {
      colorString = "Yellow";
    } else {
      colorString = "Unknown";
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

void ControlpanelSubsystem::manualMode(RobotData &robotData){ 
    // if(){
    //     cpManipulator.Set(0.2);
    // }
}

void ControlpanelSubsystem::Disabled(){
    cpManipulator.Set(0);

}

