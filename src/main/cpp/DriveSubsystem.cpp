#include "Robot.h"
#include "DriveSubsystem.h"
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

    //slows down the speed to 0.3 of the total
    lDrive = robotData.pLYStick * .3;
    rDrive = robotData.pRYStick * .3;

    
    //setting the motor speed, tank drive
    dbLM.Set(lDrive);
    dbRM.Set(rDrive);

} 

void DriveSubsystem::Disabled(){
    dbRM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    dbLM.SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
}

