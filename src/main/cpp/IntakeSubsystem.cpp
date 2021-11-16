#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "IntakeSubsystem.h"



void IntakeSubsystem::RobotInit(){

    rollers.RestoreFactoryDefaults();
    rollers.SetInverted(true);
    rollers.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    rollers.SetSmartCurrentLimit(45);
    setIntakeRollers(0);
    setPiston(false);
    setIntakeRollers(0);

}

void IntakeSubsystem::Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData){
    //decide if in manual mode or auto mode
    if(!robotData.climbMode){
        if(robotData.manualMode){
            manualMode(robotData);
        } else {
            semiAutoMode(robotData);
        }
    }else{
        setIntakeRollers(0);
        setPiston(false);
    }

    updateDiagnostics(diagnosticsData);
}


void IntakeSubsystem::semiAutoMode(RobotData &robotData){

    double averageDBVel = ((robotData.LdriveVel + robotData.RdriveVel) / 2);

    //sets the speed of the intake roller based on how fast the robot is driving 
    double pow = -0.9;
    if(averageDBVel > 3500){
        pow = -0.9;
    }else if(averageDBVel > 2800){
        pow = -0.8;
    }else if(averageDBVel > 2100){
        pow = -0.7;
    }else if(averageDBVel > 1000){
        pow = -0.6;
    }else{
        pow = -0.5;
    }

    // frc::SmartDashboard::PutNumber("speed", pow);


    //Intake balls
    if(robotData.sRTrigger){ //runs intake
        if(!getPiston()){ //if the piston is up put it down
            setPiston(true);
        }
        setIntakeRollers(pow + 0.15);
    }else if(robotData.sLTrigger){ //runs intake backwards
        setIntakeRollers(robotData.sLTrigger);
    }else{ 
        if(getPiston()){ //if the piston is down put it up
            setPiston(false);
        }
        setIntakeRollers(0);
    }
}

void IntakeSubsystem::manualMode(RobotData &robotData){

    double averageDBVel = ((robotData.LdriveVel + robotData.RdriveVel) / 2);

    //sets the speed of the intake roller based on how fast the robot is driving 
    double pow = -0.9;
    if(averageDBVel > 3500){
        pow = -0.9;
    }else if(averageDBVel > 2800){
        pow = -0.8;
    }else if(averageDBVel > 2100){
        pow = -0.7;
    }else if(averageDBVel > 1000){
        pow = -0.6;
    }else{
        pow = -0.5;
    }

    //if shift trigger run intake rollers opposite with trigger power
    if(robotData.shift){
        if(robotData.sRTrigger){
            setIntakeRollers((robotData.sRTrigger*-pow) + 0.15);
        } else {
            setIntakeRollers(0);
        }

    //else trigger controls roller power
    }else{
        setIntakeRollers(-robotData.sRTrigger);

        //r bumper controls pistons
        if(robotData.sRBumper && !alreadyToggledIntakePos){ 
            setPiston(!getPiston());
            alreadyToggledIntakePos = true;
        } 
        if (!robotData.sRBumper) {
            alreadyToggledIntakePos = false;
        }

        
    }
}

/**
 * @param direction false is retracted and true is extended
 */
void IntakeSubsystem::setPiston(bool direction){  
    if (direction){
        solenoidOne.Set(true);
    } else {
        solenoidOne.Set(false);
    }
    
}

bool IntakeSubsystem::getPiston(){
    if(solenoidOne.Get() == true){
        return true;
    }else{
        return false;
    }
}

void IntakeSubsystem::setIntakeRollers(double power){
    rollers.Set(power);
}

void IntakeSubsystem::DisabledInit(){
    setIntakeRollers(0);
    setPiston(false);
}

void IntakeSubsystem::updateDiagnostics(DiagnosticsData &diagnosticsData)
{
    /**
     * solenoidOne
     * intake rollers 32
     */
    diagnosticsData.solenoidOneValue = solenoidOne.Get();

    diagnosticsData.mControlCurrents.at(32) = rollers.GetOutputCurrent();
    diagnosticsData.mControlVoltages.at(32) = rollers.GetBusVoltage();
    diagnosticsData.mControlTemps.at(32) = rollers.GetMotorTemperature();

    diagnosticsData.mControlPositions.at(32) = rollersEncoder.GetPosition();
    diagnosticsData.mControlVelocities.at(32) = rollersEncoder.GetVelocity();

    diagnosticsData.mControlFaults.at(32) = rollers.GetFaults();
}