/* Talon SRX motor; can be used as a BaseMotor. */


#include <ctre/Phoenix.h> /* Requires Phoenix along with this vendordep */
#include <BaseMotor.hpp>


class TalonSRXMotor : public BaseMotor{
    TalonSRX* talon;
    bool invert = false;
public:
    TalonSRXMotor (int canID){
        talon = new TalonSRX(canID);
    }
    
    bool setInverted() {
        invert =! invert;
        talon -> SetInverted(invert);
    }
    
    void SetPercent(double speed){
        if (speed < 0) {
            talon -> SetInverted(!invert);
        }
        else {
            talon -> SetInverted(invert);
        }
        
        talon -> Set(ControlMode::PercentOutput, speed);
    }

    void SetP(double kP){
        talon -> Config_kP(0, kP);
    }

    void SetI(double kI){
        talon -> Config_kI(0, kI);
    }

    void SetD(double kD){
        talon -> Config_kD(0, kD);
    }

    void SetF(double kF){
        talon -> Config_kF(0, kF);
    }

    void SetOutputRange(double kPeakOF, double kPeakOR, double kNominalOF = 0, double kNominalOR = 0){
        talon -> ConfigPeakOutputForward(kPeakOF);
        talon -> ConfigPeakOutputReverse(kPeakOR);
        talon -> ConfigNominalOutputForward(kNominalOF);
        talon -> ConfigNominalOutputReverse(kNominalOR);
    }

    void SetPositionPID(double position){
        if (position < 0) {
            talon -> SetInverted(!invert);
        }
        else {
            talon -> SetInverted(invert);
        }
        
        talon -> Set(ControlMode::Position, position);
    }

    void SetSpeedPID(double speed){
        if (speed < 0) {
            talon -> SetInverted(!invert);
        }
        else {
            talon -> SetInverted(invert);
        }
        
        talon -> Set(ControlMode::Velocity, speed);
    }
    
    double GetPosition() {
        return talon -> GetSelectedSensorPosition();
    }
    
    double GetVelocity() {
        return talon -> GetSelectedSensorVelocity();
    }
    
    bool isAtZero() {
        return GetPosition() == 0;
    }
};
