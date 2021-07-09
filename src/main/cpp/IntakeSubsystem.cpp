#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "IntakeSubsystem.h"



void IntakeSubsystem::Init(){
    //just the basics to start off
    rollers.RestoreFactoryDefaults();
    rollers.SetInverted(true);
    rollers.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

/*  intakePivot_pidController.SetP(pkP);
    intakePivot_pidController.SetI(pkI);
    intakePivot_pidController.SetD(pkD);
    intakePivot_pidController.SetIZone(pkIz);
    intakePivot_pidController.SetFF(pkFF);
    intakePivot_pidController.SetOutputRange(pkMinOutput, pkMaxOutput);

    wheels_pidController.SetP(wkP);
    wheels_pidController.SetI(wkI);
    wheels_pidController.SetD(wkD);
    wheels_pidController.SetIZone(wkIz);
    wheels_pidController.SetFF(wkFF);
    wheels_pidController.SetOutputRange(wkMinOutput, wkMaxOutput);
 */

    rollers.SetSmartCurrentLimit(45);



}

void IntakeSubsystem::SetPivot(int Position){
    if (intakePivotPOS.GetPosition() > Position+1){
        intakePivot.Set(-0.2);
    } else if (intakePivotPOS.GetPosition() < Position-1){
        intakePivot.Set(0.2);
    } else{
        intakePivot.Set(0);
    }
}

void IntakeSubsystem::Periodic(frc::Joystick &sStick, IndexerSubsystem &index){
    if (index.ball3 == 1){

        if (index.getPOS() < 5){
            index.setIndexerBelt(0.5);
        } else{
            //index.setIndexerBelt(0);
            index.ball3 = 2;
            index.intakeRun = true;
        }

    } else if (index.ball4){

        // if(wheelsPOS.GetPosition() < -2){
        //     wheels.Set(-0.2);
            
        
        // } else{
        //     index.intakeRun = true;
        //     index.ball4 = false;
        // }
    } else if (index.ball5){
        // if (intakePivotPOS.GetPosition() > 1){
        //     intakePivot.Set(-0.2);
        //     wheelsPOS.SetPosition(0);
        // } else if (intakePivotPOS.GetPosition() < -1){
        //     intakePivot.Set(0.25);
        //     wheelsPOS.SetPosition(0);
        // } else if(wheelsPOS.GetPosition() < 1){
        //     intakePivot.Set(0);
        //     wheels.Set(0.2);
            
        
        // } else{
        //     index.intakeRun = true;
        //     index.ball5 = false;
        // }
    }
    //go back button for intake
    run = index.IntakeRun();
      
    if (sStick.GetRawButton(1)){
        goBack = false;
        
        wheels.Set(0);
        
        //index.setIndexerBelt(0);
    }
}

    //toggle between manual and auto
    if (sStick.GetRawButton(8) && !manualIntakeButtonDown && run){
        if (!manualIntake){
            manualIntake = true;
            manualIntakeButtonDown = true;  
        } else if (manualIntake){
            manualIntake = false;
            manualIntakeButtonDown = true;
        }
    } else if (!sStick.GetRawButton(8)){
        manualIntakeButtonDown = false;
    }

    //manual intake
    if (manualIntake && !goBack && run){

        if (sStick.GetRawAxis(3) > 0.5){
            
            if (intakePivotPOS.GetPosition() < 13){
                intakePivot.Set(0.1);
                
                wheels.Set(0.3);
                
            
            } else{
                intakePivot.Set(0);
                if (wheelsPOS.GetVelocity() < 1150){
                    //index.setIndexerBelt(0.36);

                } else{
                    //index.setIndexerBelt(0);
                }

            }
        } else{
            
            wheels.Set(0);
            
            
            if (intakePivotPOS.GetPosition() > 0){
                intakePivot.Set(-0.1);
            
            } else{
                intakePivot.Set(0);
            }
            
        }
        
    //automatic intake
    } else if (!manualIntake && !goBack && run){
        if (sStick.GetRawAxis(3) > 0.5){
            
            wheels.Set(0.3);
              
            
            if (wheelsPOS.GetVelocity() > 1200){
                wheelsIntake = true;
            }
            if (wheelsPOS.GetVelocity() < 1150 && wheelsIntake){
                //index.setIndexerBelt(0.36);

            } else{
                //index.setIndexerBelt(0);
            }
        } else {
            wheelsIntake = false;
            
            wheels.Set(0);
            
            
        }

    }

    
    frc::SmartDashboard::PutNumber("Encoder Position", wheelsPOS.GetPosition());
    frc::SmartDashboard::PutNumber("intake velocity", wheelsPOS.GetVelocity());

void IntakeSubsystem::manualMode(RobotData &robotData){

    if(robotData.sLTrigger){
        setPiston(true);
    } else {
        setPiston(false);
    }

    if(robotData.sLBumper){
        setIntakeRollers(0.3*robotData.shift);
    } else {
        setIntakeRollers(0);
    }

}


void IntakeSubsystem::setPiston(bool direction){
    if (direction){
        solenoidOne.Set(true);
    } else {
        solenoidOne.Set(false);
    }
    
}

void IntakeSubsystem::setIntakeRollers(double power){
    rollers.Set(power);
}



