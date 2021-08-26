#include "Robot.h"

void LEDSubsystem::RobotInit(){

    

}

void LEDSubsystem::Periodic(RobotData &robotData){
    
    if (!robotData.manualMode && !robotData.climbMode && robotData.teleopEnabled) {
        SetColor(0,255,0);
    } else if (robotData.manualMode && !robotData.climbMode && robotData.teleopEnabled) {
        SetColor(255,69,0);
    } else if (robotData.manualMode && robotData.climbMode && robotData.teleopEnabled) {
        SetColor(0,255,255);
    } else if (robotData.climbMode && robotData.teleopEnabled) {
        SetColor(0,0,255);
    } else if (robotData.autonEnabled) {
        SetColor(255,255,0);
    } else {
        SetColor(255,0,0);
    }

} 

void LEDSubsystem::SetColor(double r, double g, double b) {

    LED.SetLEDOutput(r/255,CANifier::LEDChannelB);
    LED.SetLEDOutput(g/255,CANifier::LEDChannelA);
    LED.SetLEDOutput(b/255,CANifier::LEDChannelC);
}
