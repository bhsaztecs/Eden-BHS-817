////////////////////
//  DECLARATIONS  //
////////////////////

float absolute(float);
// in (value)
// Get the absolute value of an input
// abs() wasnt working for whatever reason idk
// out (absolute value)

void CollisionCheck();
// Checks if the robot is attempting to move and failing
// WIP (need to check the Gs in the direction its not going)

void CollisionReset();
// Brings the robot to face the south wall and the west wall in order to find
// the location of the colision

void CollisionRecovery(float, float, float);
// in (x offset, y offset, angular offset)
// Brings the robot to the point of collision, with an optional offset ((0,0,0)
// for no offset.)

void AthenaDecision(float, float);
// in (left delta, right delta)
// decides which method of position/orientation calculation to preform

void AOPivot(float, float);
// in(Delta L, Delta R)
// calculates the change in orientation of the robot given a pivot

void APCount(float, float);
// in(Delta L, Delta R)
// calculates the change position given a straight movement

void APOTrig(float, float);
// in(Delta L, Delta R);
// calculates the change in position given complex deltas

void AOCalc(float);
// calculates the new orientation given the previous orientation and the change
// from previous orientation

void APCalc(float, float);
// calculates the new position given the previous orientation and the previous
// location, as well as the delta orientation and delta position

void Status(char hex[]);
// in (hexadecimal string which prints a set of chosen values)
/*
Type the function like this
hex[0] = 'F';
hex[1] = 'F';
hex[2] = 'F';
Status(hex);
*/
// OXY/Athena, Battery, Motor positions, Accelerometer, Gyro, Compass, Motor
// Multipliers, Servo Positions, Enabled Servos, Digitals, Analogs,
// CommandCalls(updates until further notice) hex value will be 3 characters
// (use https://www.rapidtables.com/convert/number/binary-to-hex.html) FFF
// prints all values 000 prints none prints the current state of the robot
// out(orientation, position, sensor values, wheel positions, servo
// positions, etc)

int MOE(float, float, float);
// in (value one, value two, range)
// calculates if value one is within a certain range of value two
// out (1 if values are within range, 0 if not)

void Test(int, int, int);
// calculates the values needed to preform a given movement
// ie. "go straight for 3 seconds"

void ArmVertical(float, float);
// in (goal position, time)
// locks the arm on the z axis as it attempts to go from the current position to
// the goal position

float rad(float);
// in (degrees)
// converts degrees to radians
// math.h's was busted idk
// out (radians)

float degrees(float);
// in (radians)
// converts radians to degrees
// out (degrees)

void Velocity();
// calculates the current velocity of each wheel in powerpercent

int clamp(float, float, float);
// in (min, val, max)
// checks that a value is within the minimum and maximum value
// out (1 true, 0 false)

void TankSpeed(float, float, float);
// in (left speed, right speed, time)
// moves the wheels independently at a certain speed for a certain amount of
// time

void TankRotation(float, float, float);
// in (left wheel goal, right wheel goal, time)
// moves the wheels independently to a goal position in a certain amount of time

void TankDistance(float, float, float);
// in (left wheel goal, right wheel goal, time)
// moves the wheels independently to a goal position in a certain amount of time

void DriveSpeed(float, float, float);
// in (base speed, turn percent, time);
// moves the wheels together at a certain speed for a certain amount of time

void DriveRotation(float, float, float);
// in (base rotations, turn rotations, time);
// moves the wheels together to a goal position in a certain amount of time

void DriveDistance(float, float, float);
// in (base distance, turn distance, time);
// moves the wheels together to a goal position in a certain amount of time

void TankAccelerate(float, float, int);
// in (left goal, right goal, acceleration value)
// moves the wheels independently, going faster over time

void DriveAccelerate(float, float, int);
// in (base speed goal, turn speed goal, acceleration value)
// moves the wheels together, going faster over time

void SmoothTankTime(float, float, float, float, int, float);
// in (first left acceleration goal, first right acceleration goal, second left
// acceleration goal, second right acceleration goal, 	acceleration value, how
// long to move at first goal) moves from current speed to a new goal, stays at
// the goal for a certain amount of time, and then goes from that goal to the
// second goal

void SmoothDriveTime(float, float, float, float, int, float);
// in (first base acceleration goal, first turn acceleration goal, second base
// acceleration goal, second turn acceleration goal, 	acceleration value, how
// long to move at first goal) moves from current speed to a new goal, stays at
// the goal for a certain amount of time, and then goes from that goal to the
// second goal

void SetArm(float, float);
// in (arm goal, claw goal)
// sets the arm and claw to a goal position

void ChangeArm(float, float);
// in (delta arm position, delta claw position)
// changes the arm from the current position to the goal position

void SlowSetArm(float, float);
// in (goal arm position, time)
// goes to the goal arm position in a certain amount of time

int DTTW(float);
// in (Degrees)
// converts degrees to wheel ticks
// out (Ticks)

float TTDW(int);
// in (Ticks)
// converts wheel ticks to degrees
// out (Degrees)

float DTIW(float);
// in (Degrees)
// converts wheel degrees to inches
// out (Inches)

float ITDW(float);
// in (Inches)
// converts inches to wheel degrees
// out (Degrees)

float TTIW(int);
// in (Ticks)
// converts wheel ticks into inches
// out (Inches)

int ITTW(float);
// in (Inches)
// converts inches to wheel ticks
// out (Ticks)

int DTTA(float);
// in (Degrees)
// converts degrees to arm tics
// out (Tics)

float TTDA(int);
// in (Tics)
// converts arm tics to degrees
// out (Degrees)

int DTTC(float);
// in(Degrees)
// converts degrees to claw tics
// out(Tics)

float TTDC(int);
// in(Tics)
// converts claw tics to degrees
// out(Degrees)

void Wait(float);
// in (seconds)
// a pause

void Brake();
// employs braking in both wheels

void CMR();
// clears motor tick counters

void HandsOff();
// initiates wait for light program
// stop touching the robot!

void Startup();
// initiates system resets, prepares the robot to run

////////////////////
///////////////////
//   MOVEMENT  ///
/////////////////

void TankSpeed(float SpeedL, float SpeedR, float Time) {
    if (commandCalls == 1) {
        printf("TankSpeed called. \n");
    }
    float Lo = TTIW(gmpc(Leftm));
    float Ro = TTIW(gmpc(Rightm));
    motor(Leftm, (SpeedL * LMM));
    motor(Rightm, (SpeedR * RMM));
    msleep((Time * 1000) * timemult);
    float Lt = TTIW(gmpc(Leftm));
    float Rt = TTIW(gmpc(Rightm));
    float DelL = Lt - Lo;
    float DelR = Rt - Ro;
    if (AthenaOn == 1) {
        AthenaDecision(DelL, DelR);
    }
}

void TankRotation(float RotL, float RotR, float Time) {
    if (commandCalls == 1) {
        printf("TankRotation called. \n");
    }
    float DistL = DTIW(RotL);
    float DistR = DTIW(RotR);
    TankDistance(DistL, DistR, Time);
}

void TankDistance(float DistL, float DistR, float Time) {
    if (commandCalls == 1) {
        printf("TankDistance called. \n");
    }
    float Ls = (ITTW(DistL) / Time) / 15;
    float Rs = (ITTW(DistR) / Time) / 15;
    if (Ls > 100 || Rs > 100) {
        if (Ls > Rs) {
            float t = ((Time * (Ls / 100)) + 0.01);
            printf("Speed (%f) is too high. increase time to %.2f \n", Ls, t);
        } else {
            float t = ((Time * (Rs / 100)) + 0.01);
            printf("Speed (%f) is too high. increase time to %.2f \n", Rs, t);
        }
    } else {
        TankSpeed(Ls, Rs, Time);
    }
}

/////////////////

void DriveSpeed(float BaseS, float DifS, float Time) {
    if (commandCalls == 1) {
        printf("DriveSpeed called. \n");
    }
    float SpeedL = BaseS + DifS;
    float SpeedR = BaseS - DifS;

    TankSpeed(SpeedL, SpeedR, Time);
}

void DriveRotation(float BaseRot, float DifRot, float Time) {
    if (commandCalls == 1) {
        printf("DriveRotation called. \n");
    }
    float RotL = BaseRot + DifRot;
    float RotR = BaseRot - DifRot;

    TankRotation(RotL, RotR, Time);
}

void DriveDistance(float BaseD, float DifD, float Time) {
    if (commandCalls == 1) {
        printf("DriveDistance called. \n");
    }
    float DistL = BaseD + DifD;
    float DistR = BaseD - DifD;

    TankDistance(DistL, DistR, Time);
}

/////////////////
/////////////////

void TankAccelerate(float GoalSpeedL, float GoalSpeedR, int Acceleration) {
    if (commandCalls == 1) {
        printf("TankAccelerate called. \n");
    }
    float CurrentSpeedL = Lp;
    float CurrentSpeedR = Rp;
    float SpeedDifL = GoalSpeedL - CurrentSpeedL;
    float SpeedDifR = GoalSpeedR - CurrentSpeedR;
    SpeedDifL = SpeedDifL / 25;
    SpeedDifR = SpeedDifR / 25;
    float SpeedL = CurrentSpeedL;
    float SpeedR = CurrentSpeedR;
    int count = 0;
    while (count < 25) {
        TankSpeed(SpeedL, SpeedR, (Acceleration / 100));
        SpeedL += SpeedDifL;
        SpeedR += SpeedDifR;
    }
}

void DriveAccelerate(float GoalBase, float GoalDif, int Acceleration) {
    if (commandCalls == 1) {
        printf("DriveAccelerate called. \n");
    }
    float CurrentBase = (Lp + Rp) / 2;
    float CurrentDif = CurrentBase - Rp;
    float SpeedDifB = GoalBase - CurrentBase;
    float SpeedDifD = GoalDif - CurrentDif;
    SpeedDifB = SpeedDifB / 25;
    SpeedDifD = SpeedDifD / 25;
    float SpeedB = CurrentBase;
    float SpeedD = CurrentDif;
    int count = 0;
    while (count < 25) {
        DriveSpeed(SpeedB, SpeedD, (Acceleration / 1000));
        SpeedB += SpeedDifB;
        SpeedD += SpeedDifD;
    }
}

/////////////////

void SmoothTankTime(float TopL, float TopR, float BotL, float BotR,
                    int Acceleration, float Time) {
    if (commandCalls == 1) {
        printf("SmoothTankTime called. \n");
    }
    TankAccelerate(TopL, TopR, Acceleration);
    TankSpeed(TopL, TopR, Time);
    TankAccelerate(BotL, BotR, Acceleration);
}

void SmoothDriveTime(float TopB, float TopD, float BotB, float BotD,
                     int Acceleration, float Time) {
    if (commandCalls == 1) {
        printf("SmoothDriveTime called. \n");
    }
    DriveAccelerate(TopB, TopD, Acceleration);
    DriveSpeed(TopB, TopD, Time);
    DriveAccelerate(BotB, BotD, Acceleration);
}

/////////////////
//     ARM     //
/////////////////

void SetArm(float PosA, float PosC) {
    if (commandCalls == 1) {
        printf("SetArm called. \n");
    }
    enable_servos();
    set_servo_position(Arm, DTTA(PosA));
    msleep(10);
    set_servo_position(Claw, DTTC(PosC));
    msleep(10);
    disable_servos();
}

void ChangeArm(float DeltaA, float DeltaC) {
    if (commandCalls == 1) {
        printf("ChangeArm called. \n");
    }
    int CurA = TTDA(get_servo_position(Arm));
    int CurC = TTDA(get_servo_position(Claw));
    int PosA = CurA + DeltaA;
    int PosC = CurC + DeltaC;

    SetArm(PosA, PosC);
}

void SlowSetArm(float Pos, float Time) {
    if (commandCalls == 1) {
        printf("SlowSetArm called. \n");
    }
    int CurPos = get_servo_position(Arm);
    int distance = Pos - CurPos;
    int Distn = distance / 50;
    int Timen = Time / 50;
    int count = 0;
    while (count < 50) {
        ChangeArm(Distn, 0);
        msleep(Timen);
        count += 1;
    }
}

/////////////////
// CONVERSIONS //
//    wheels   //
/////////////////

int DTTW(float Degrees) {
    if (commandCalls == 1) {
        printf("DTTW called. \n");
    }
    int Ticks = Degrees * 5.55;
    return Ticks;
}

float TTDW(int Ticks) {
    if (commandCalls == 1) {
        printf("TTDW called. \n");
    }
    float Degrees = Ticks / 5.55;
    return Degrees;
}

float DTIW(float Degrees) {
    if (commandCalls == 1) {
        printf("DTIW called. \n");
    }
    float Inches = WheelRadius * rad(Degrees);
    return Inches;
}

float ITDW(float Inches) {
    if (commandCalls == 1) {
        printf("ITDW called. \n");
    }
    float Degrees = degrees(WheelRadius / Inches);
    return Degrees;
}

float TTIW(int Ticks) {
    if (commandCalls == 1) {
        printf("TTIW called. \n");
    }
    float Inches = Ticks / 206.49999936;
    return Inches;
}

int ITTW(float Inches) {
    if (commandCalls == 1) {
        printf("ITTW called. \n");
    }
    int Ticks = Inches * 206.49999936;
    return Ticks;
}

/////////////////
// CONVERSIONS //
//     arms    //
/////////////////

int DTTA(float Degrees) {
    if (commandCalls == 1) {
        printf("DTTA called. \n");
    }
    int Tics = (0.09 / Degrees) + 57.15;
    return Tics;
}

float TTDA(int Tics) {
    if (commandCalls == 1) {
        printf("TTDA called. \n");
    }
    float Degrees = (0.09 * Tics) - 57.15;
    return Degrees;
}

int DTTC(float Degrees) {
    if (commandCalls == 1) {
        printf("DTTC called. \n");
    }
    int Tics = (12.05 * Degrees) + 723.5;
    return Tics;
}

float TTDC(int Tics) {
    if (commandCalls == 1) {
        printf("TTDC called. \n");
    }
    float Degrees = (0.082 * Tics) - 60;
    return Degrees;
}

/////////////////
// MISCELLANEOUS//
/////////////////

void Wait(float Time) {
    if (commandCalls == 1) {
        printf("Wait called. \n");
    }
    Brake();
    ao();
    disable_servos();
    msleep(Time * 1000);
    enable_servos();
}

void Brake() {
    if (commandCalls == 1) {
        printf("Brake called. \n");
    }
    freeze(Leftm);
    freeze(Rightm);
}

void CMR() {
    if (commandCalls == 1) {
        printf("CMR called. \n");
    }
    cmpc(Leftm);
    cmpc(Rightm);
}

void HandsOff() {
    if (commandCalls == 1) {
        printf("HandsOff called. \n");
    }
    printf("and god said... /n");
    wait_for_light(Starts);
    shut_down_in(119);
    printf("...let there be light /n");
}

void Startup() {
    if (commandCalls == 1) {
        printf("Startup called. \n");
    }
    if (LMM > RMM) {
        WMM = 1 / LMM;
    }
    if (LMM < RMM) {
        WMM = 1 / RMM;
    }

    RMM = RMM * WMM;
    LMM = LMM * WMM;

    if (LMM > RMM) {
        timemult = (1 - RMM) + 1;
    }
    if (LMM < RMM) {
        timemult = (1 - LMM) + 1;
    }

    enable_servos();
    Brake();
    CMR();
    SetArm(90, 90);
}

/////////////////
//  COLLISION  //
/////////////////

float Accelerometer() {
    if (commandCalls == 1) {
        printf("Accelerometer called. \n");
    }
    float AccelAvg = (accel_x() + accel_z()) / 2;
    return AccelAvg;
}

void CollisionCheck() {
    if (commandCalls == 1) {
        printf("CollisionCheck called. \n");
    }
    float Acceleration = 0;
    float Movement = 0;
    Collision = 0;
    if (MOE(Accelerometer(), 0, 0.1) == 1) {
        Acceleration = 0;
    } else {
        Acceleration = 1;
    }

    if (MOE(DeltaL, 0, 10) == 1) {
        Movement = 0;
    } else {
        Movement = 1;
    }

    if (Acceleration == 1 && Movement == 1) {
        Collision = 1;
    } else {
        Collision = 0;
    }
}

void CollisionReset() {
    if (commandCalls == 1) {
        printf("CollisionReset called. \n");
    }
    // face bottom
    // drive
    // back up
    // face left
    // drive
    // back up
}

void CollisionRecovery(float x, float y, float o) {
    if (commandCalls == 1) {
        printf("CollisionRecovery called. \n");
    }
    // if collided
    // run reset
    // adjust values for offset
    // trig n follow values
    // turn to orrientation
}

/////////////////
//   ATHENA    //
/////////////////

void AthenaDecision(float DeltaL, float DeltaR) {
    if (commandCalls == 1) {
        printf("AthenaDecision called. \n");
    }
    if (MOE(absolute(DeltaL), absolute(DeltaR), athenaMargin) &&
        DeltaL != DeltaR) {
        AOPivot(DeltaL, DeltaR);
    } else if (MOE(DeltaL, DeltaR, athenaMargin)) {
        APCount(DeltaL, DeltaR);
    } else {
        APOTrig(DeltaL, DeltaR);
    }
}

void AOPivot(float DeltaL, float DeltaR) {
    if (commandCalls == 1) {
        printf("AOPivot called. \n");
    }
    float Wa = (absolute(DeltaL) + absolute(DeltaR)) / 2;
    float Ooffset = Wa / TurnRate;

    AOCalc(Ooffset);
}

void APCount(float DeltaL, float DeltaR) {
    if (commandCalls == 1) {
        printf("APCount called. \n");
    }
    float Dist = (DeltaL + DeltaR) / 2;
    float Ang = rad(CurrentO);
    Yoffset = Dist * sin(Ang);
    Xoffset = Dist * cos(Ang);
    APCalc(Xoffset, Yoffset);
}

void APOTrig(float DeltaL, float DeltaR) {
    if (commandCalls == 1) {
        printf("APOTrig called. \n");
    }
    float T = (DeltaL + DeltaR) / (DeltaL - DeltaR);

    float A = (DeltaL + DeltaR) / 2;
    float Ao = A / absolute(T);

    float Gx = absolute(T);
    float Gy = 0;

    float x1 = (Gx * cos(Ao)) - (Gy * sin(Ao));
    float y1 = (Gy * cos(Ao)) + (Gx * sin(Ao));

    float G2x = (x1 - Gx) + CurrentX;
    float G2y = (y1 - Gy) + CurrentY;

    float D2x = G2x - CurrentX;
    float D2y = G2y - CurrentY;

    float x2 = (D2x * cos(CurrentO)) - (D2y * sin(CurrentO));
    float y2 = (D2y * cos(CurrentO)) + (D2x * sin(CurrentO));

    APCalc(x2, y2);
    AOCalc(Ao);
}

void AOCalc(float Ooffset) {
    if (commandCalls == 1) {
        printf("AOCalc called. \n");
    }
    CurrentO = Ooffset + CurrentO;
}

void APCalc(float Xoffset, float Yoffset) {
    if (commandCalls == 1) {
        printf("APCalc called. \n");
    }
    CurrentY = Yoffset + CurrentY;
    CurrentX = Xoffset + CurrentX;
}

/////////////////
//   ARTEMIS   //
/////////////////

void TurnTo(int DeltaO, float Time) {
    if (commandCalls == 1) {
        printf("TurnTo called. \n");
    }
    float GoalO = CurrentO + rad(DeltaO);
    float WheelAngle = GoalO * TurnRate * 57.2957795131;
    if (WheelAngle > 0) {
        TankRotation(-WheelAngle, WheelAngle, Time);
    }
    if (WheelAngle < 0) {
        TankRotation(WheelAngle, -WheelAngle, Time);
    }
}

void GoTo(float GoalX, float GoalY, float Time) {
    if (commandCalls == 1) {
        printf("GoTo called. \n");
    }
    float DistX = CurrentX - GoalX;
    float DistY = CurrentY - GoalY;
    float DistC = sqrt(pow(DistX, 2) + pow(DistY, 2));
    float arc = degrees(atan(DistX / DistY));

    TurnTo(arc, Time / 4);
    TankDistance(DistC, DistC, ((Time / 4) * 3));
}

void GoAndFace(float GoalX, float GoalY, int GoalO, float Time) {
    if (commandCalls == 1) {
        printf("GoAndFace called. \n");
    }
    GoTo(GoalX, GoalY, (Time / 5) * 4);
    TurnTo(GoalO, Time / 5);
}

void FollowCurve(float Radius, float Distance, float Time) {
    if (commandCalls == 1) {
        printf("FollowCurve called. \n");
    }
    float SlowRad = Radius - AxelRadius;
    float FastRad = Radius + AxelRadius;
    float SlowSpeed = SlowRad * tan(0.785398);
    float FastSpeed = FastRad * tan(0.785398);
    FastSpeed = (FastSpeed / SlowSpeed) * Distance;
    SlowSpeed = (SlowSpeed / SlowSpeed) * Distance;
    if (Radius > 0) {
        TankDistance(FastSpeed, SlowSpeed, Time);
    }
    if (Radius < 0) {
        TankDistance(SlowSpeed, FastSpeed, Time);
    }
}

/////////////////
//  HEPHAESTUS //
/////////////////

/////////////////
//   HERMES    //
/////////////////

/////////////////
// MISCELLANEOUS//
/////////////////

void Status(char hex[]) {
    if (commandCalls == 1) {
        printf("Status called. \n");
    }
    int onoff[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int loopn = 0;

    while (loopn < 12) {
        if (hex[loopn / 4] == '0') {
            onoff[loopn] = 0;
            onoff[loopn + 1] = 0;
            onoff[loopn + 2] = 0;
            onoff[loopn + 3] = 0;
            loopn = loopn + 4;
        }

        else if (hex[loopn / 4] == '1') {
            onoff[loopn] = 0;
            onoff[loopn + 1] = 0;
            onoff[loopn + 2] = 0;
            onoff[loopn + 3] = 1;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == '2') {
            onoff[loopn] = 0;
            onoff[loopn + 1] = 0;
            onoff[loopn + 2] = 1;
            onoff[loopn + 3] = 0;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == '3') {
            onoff[loopn] = 0;
            onoff[loopn + 1] = 0;
            onoff[loopn + 2] = 1;
            onoff[loopn + 3] = 1;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == '4') {
            onoff[loopn] = 0;
            onoff[loopn + 1] = 1;
            onoff[loopn + 2] = 0;
            onoff[loopn + 3] = 0;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == '5') {
            onoff[loopn] = 0;
            onoff[loopn + 1] = 1;
            onoff[loopn + 2] = 0;
            onoff[loopn + 3] = 1;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == '6') {
            onoff[loopn] = 0;
            onoff[loopn + 1] = 1;
            onoff[loopn + 2] = 1;
            onoff[loopn + 3] = 0;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == '7') {
            onoff[loopn] = 0;
            onoff[loopn + 1] = 1;
            onoff[loopn + 2] = 1;
            onoff[loopn + 3] = 1;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == '8') {
            onoff[loopn] = 1;
            onoff[loopn + 1] = 0;
            onoff[loopn + 2] = 0;
            onoff[loopn + 3] = 0;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == '9') {
            onoff[loopn] = 1;
            onoff[loopn + 1] = 0;
            onoff[loopn + 2] = 0;
            onoff[loopn + 3] = 1;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == 'A') {
            onoff[loopn] = 1;
            onoff[loopn + 1] = 0;
            onoff[loopn + 2] = 1;
            onoff[loopn + 3] = 0;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == 'B') {
            onoff[loopn] = 1;
            onoff[loopn + 1] = 0;
            onoff[loopn + 2] = 1;
            onoff[loopn + 3] = 1;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == 'C') {
            onoff[loopn] = 1;
            onoff[loopn + 1] = 1;
            onoff[loopn + 2] = 0;
            onoff[loopn + 3] = 0;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == 'D') {
            onoff[loopn] = 1;
            onoff[loopn + 1] = 1;
            onoff[loopn + 2] = 0;
            onoff[loopn + 3] = 1;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == 'E') {
            onoff[loopn] = 1;
            onoff[loopn + 1] = 1;
            onoff[loopn + 2] = 1;
            onoff[loopn + 3] = 0;
            loopn = loopn + 4;
        } else if (hex[loopn / 4] == 'F') {
            onoff[loopn] = 1;
            onoff[loopn + 1] = 1;
            onoff[loopn + 2] = 1;
            onoff[loopn + 3] = 1;
            loopn = loopn + 4;
        }
    }
    printf("\n");
    int loop = 0;
    for (loop = 0; loop < 12; loop++) {
        printf("%d", onoff[loop]);
    }
    loop = 0;
    printf(" || ");
    for (loop = 0; loop < 3; loop++) {
        printf("%c", hex[loop]);
    }
    printf("\n");

    if (onoff[0] == 1) {
        printf("O: %f, X: %f, Y: %f, Athena: %i\n", CurrentO, CurrentX, CurrentY,
               AthenaOn);
    }

    if (onoff[1] == 1) {
        printf("Battery: %.0f%% \n", power_level_life() * 100);
    }

    if (onoff[2] == 1) {
        printf("GMPC Left: %i, Right: %i, Average: %i \n", gmpc(Leftm),
               gmpc(Rightm), ((gmpc(Leftm) + gmpc(Rightm)) / 2));
    }

    if (onoff[3] == 1) {
        printf("Accelerometer X: %i Y: %i Z: %i Average: %i \n", accel_x(),
               accel_y(), accel_z(), (accel_x() + accel_y() + accel_z()) / 3);
    }

    if (onoff[4] == 1) {
        printf("Gyroscope X: %i Y: %i Z: %i Average: %i \n", gyro_x(), gyro_y(),
               gyro_z(), (gyro_x() + gyro_y() + gyro_z()) / 3);
    }

    if (onoff[5] == 1) {
        printf("Compass %f \n", get_compass_angle());
    }

    if (onoff[6] == 1) {
        printf("Motor Multipliers LMM: %f, RMM: %f, WMM: %f, TMM: %f \n", LMM, RMM,
               WMM, timemult);
    }

    if (onoff[7] == 1) {
        printf("Servo Positions 0: %i 1: %i 2: %i 3: %i \n", get_servo_position(0),
               get_servo_position(1), get_servo_position(2), get_servo_position(3));
    }

    if (onoff[8] == 1) {
        printf("Servos Enabled 0:%i 1:%i 2:%i 3:%i \n", get_servo_enabled(0),
               get_servo_enabled(1), get_servo_enabled(2), get_servo_enabled(3));
    }

    if (onoff[9] == 1) {
        printf("Digitals 0:%i 1:%i 2:%i 3:%i 4:%i 5:%i 6:%i 7:%i \n", digital(0),
               digital(1), digital(2), digital(3), digital(4), digital(5),
               digital(6), digital(7));
    }

    if (onoff[10] == 1) {
        printf("Analogs 0: %i 1: %i 2: %i 3: %i 4: %i 5: %i 6: %i 7: %i \n",
               analog(0), analog(1), analog(2), analog(3), analog(4), analog(5),
               analog(6), analog(7));
    }

    if (onoff[11] == 1) {
        printf("Command calls: On \n");
        commandCalls = 1;
        printf("Command calls: %i\n", commandCalls);
    }
    if (onoff[11] == 0) {
        printf("Command calls: Off \n");
        commandCalls = 0;
        printf("Command calls: %i\n", commandCalls);
    }
    printf("\n");
}

int MOE(float InputA, float InputB, float Range) {
    if (commandCalls == 1) {
        printf("MOE called. \n");
    }
    float Min = InputB - Range;
    float Max = InputB + Range;
    return clamp(Min, InputA, Max);
}

void Test(int movetype, int measuretype, int direction) {
    if (commandCalls == 1) {
        printf("Test called. \n");
    }
    // movetype straight or turn
    // measuretype time dist rot
    // direction forwards backwards left right
}

float absolute(float value) {
    if (commandCalls == 1) {
        printf("absolute called. \n");
    }
    if (value < 0) {
        value = value * -1;
    }
    return value;
}

float rad(float degrees) {
    if (commandCalls == 1) {
        printf("rad called. \n");
    }
    float rad = degrees * 0.0174532951;
    return rad;
}

void Velocity() {
    if (commandCalls == 1) {
        printf("Velocity called. \n");
    }
    while (1) {
        float VLo = gmpc(Leftm);
        float VRo = gmpc(Rightm);
        msleep(10);
        float VLt = gmpc(Leftm);
        float VRt = gmpc(Rightm);

        Lv = VLt - VLo;
        Rv = VRt - VRo;
        Lp = Lv / 15;
        Rp = Rv / 15;
    }
}

float degrees(float radians) {
    if (commandCalls == 1) {
        printf("degrees called. \n");
    }
    float degrees = radians * 57.2957795131;
    return degrees;
}

int clamp(float min, float val, float max) {
    if (commandCalls == 1) {
        printf("clamp called. \n");
    }
    if (min < val && val < max) {
        return 1;
    } else {
        return 0;
    }
}

/////////////////
//     ARM     //
/////////////////

void ArmVertical(float Position, float Time) {
    if (commandCalls == 1) {
        printf("ArmVertical called. \n");
    }
    Position = Position - Armoffsety;
    while (MOE(TTDA(get_servo_position(Arm)), Position, 10) != 1) {
        float armdist = TTDA(get_servo_position(Arm)) - Position;
        int Divisor = round(armdist * (-(armdist / 10)) + 10);
        float Increment = armdist / Divisor;
        float NextPosition = TTDA(get_servo_position(Arm)) + Increment;
        float Angle = asin(NextPosition / Armlength);
        float Versin = (Armlength - (sqrt(pow(Armlength, 2) - pow(NextPosition, 2)))) - Armoffsetx;

        SlowSetArm(TTDA(Angle), Time);
        TankDistance(Versin, Versin, Time);
    }
}