#pragma once

#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc/Solenoid.h>

#include "RobotData.h"
#include "Diagnostics.h"


class IntakeSubsystem {
    
    public:

        void Init();
        void Periodic(RobotData &robotData, DiagnosticsData &diagnosticsData);
        void Disabled();


    private:

        int shootPOV;
        
        void setIntakeRollers(double avgDrive);
        void setPiston(bool direction);
        bool getPiston();
        void semiAutoMode(RobotData &robotData);
        void manualMode(RobotData &robotData);
    

        void updateDiagnostics(DiagnosticsData &diagnosticsData);

        /* bool goBack = false;
        bool manualIntakeButtonDown = false;
        bool manualIntake = false;
        bool wheelsIntake = false; */
       /*  double pkP = 0.02, pkI = 0, pkD = 0, pkIz = 0, pkFF = 0, pkMaxOutput = 1, pkMinOutput = -1;
        double wkP = 1, wkI = 0, wkD = 0, wkIz = 0, wkFF = 0, wkMaxOutput = 1, wkMinOutput = -1; */

        int shiftFactor = 1;

        static const int intakeRollersID = 32;
        rev::CANSparkMax rollers{intakeRollersID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANEncoder rollersEncoder = rollers.GetEncoder();

        frc::Solenoid solenoidOne{0};

};