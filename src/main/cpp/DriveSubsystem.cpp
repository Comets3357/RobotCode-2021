#include "Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>


void DriveSubsystem::Init(){

    dbLM.RestoreFactoryDefaults();
    dbRM.RestoreFactoryDefaults();

    dbLS.RestoreFactoryDefaults();
    dbRS.RestoreFactoryDefaults();


    //we inverted the right side and set motors to follow each other
    dbLM.SetInverted(false);
    dbRM.SetInverted(true);

    dbLS.Follow(dbLM);
    dbRS.Follow(dbRM);

    dbRM.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    dbLM.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    dbLM.SetSmartCurrentLimit(45);
    dbRM.SetSmartCurrentLimit(45);
    dbLS.SetSmartCurrentLimit(45);
    dbRS.SetSmartCurrentLimit(45);

    dbLM.Set(0);
    dbRM.Set(0);

}

void DriveSubsystem::Periodic(RobotData &robotData){

    //adds spice to drive base :)
    lDrive = robotData.pLYStick;
    rDrive = robotData.pRYStick;
    frc::SmartDashboard::PutNumber("ldrive", lDrive);
    frc::SmartDashboard::PutNumber("rdrive", rDrive);


    double frontBack = cStraight*(lDrive + rDrive)/2;
    double leftRight = cTurn*(rDrive - lDrive)/2;

    
    //setting the motor speed, tank drive
    dbRM.Set(frontBack + leftRight);
    dbLM.Set(frontBack - leftRight);

} 

void DriveSubsystem::Disabled(){
    dbRM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    dbLM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    dbLM.Set(0);
    dbRM.Set(0);
}

