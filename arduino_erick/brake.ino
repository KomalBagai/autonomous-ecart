#define t_eng 600
#define t_dis 600
#define pwm_eng_r 200
#define pwm_dis_r 70
#define pwm_f 250
#define t_dis_f 100
#define t_eng_f 200

bool isBraked = false;

void engage_brake(){
    analogWrite(THROTTLE_TO_RICK, 0); // send throttle zero when braking
    Right(R_BREAK_RPWM, R_BREAK_LPWM, pwm_eng_r, t_eng);  // brake
    Left(F_BREAK_RPWM, F_BREAK_LPWM, pwm_f, t_eng_f);  // brake
    nh.logwarn("brake true");
    isBraked = true;
}
void disengage_brake(){
    Left(R_BREAK_RPWM, R_BREAK_LPWM, pwm_dis_r, t_dis);  // brake
    Right(F_BREAK_RPWM, F_BREAK_LPWM, pwm_f, t_dis_f);  // brake
    nh.logwarn("brake false");
    isBraked = false;
}

void apply_brakes(int desired){
    if (desired == 1 && isBraked == false){
        engage_brake();
    }
    else {
        Stop(R_BREAK_RPWM, R_BREAK_LPWM);
        Stop(F_BREAK_RPWM, F_BREAK_LPWM);
    }
    if (desired == 0 && isBraked == true){
        disengage_brake();
    }
    else {
        Stop(R_BREAK_RPWM, R_BREAK_LPWM);
        Stop(F_BREAK_RPWM, F_BREAK_LPWM);
        // isBraked = false;
    }
}