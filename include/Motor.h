#pragma once
#include "Basic.h"
void motors::ClearMotorRotations() {
  DLOG
  cmpc(LeftMotor);
  cmpc(RightMotor);
}
void motors::Velocity() {
  DLOG
  while ( 1 ) {
    float VLo = gmpc(LeftMotor);
    float VRo = gmpc(RightMotor);
    msleep(100);
    float VLt = gmpc(LeftMotor);
    float VRt = gmpc(RightMotor);

    float Lv = (VLt - VLo) * 10;
    float Rv = (VRt - VRo) * 10;
    LeftSpeed = Lv * 0.06;
    RightSpeed = Rv * 0.06;
  }
}
void motors::Speed(float LeftPercent, float RightPercent, float TimeInSeconds) {
  DLOG
  float Lo = TTIW(gmpc(LeftMotor));
  float Ro = TTIW(gmpc(RightMotor));
  motor(LeftMotor, (LeftPercent * LMM));
  motor(RightMotor, (RightPercent * RMM));
  msleep((TimeInSeconds * 1000) * TimeMultiplier);
  float Lt = TTIW(gmpc(LeftMotor));
  float Rt = TTIW(gmpc(RightMotor));
  float DelL = Lt - Lo;
  float DelR = Rt - Ro;
  AthenaDecision(DelL, DelR);
}
void motors::Rotation(float LeftDegrees, float RightDegrees, float TimeInSeconds) {
  DLOG
    float DistL = DTIW(LeftDegrees);
  float DistR = DTIW(RightDegrees);
  Distance(DistL, DistR, TimeInSeconds);
}
void motors::Distance(float LeftInches, float RightInches, float TimeInSeconds) {
  DLOG
  float Ls = float((ITTW(LeftInches / TimeInSeconds)) / 15);
  float Rs = float((ITTW(RightInches / TimeInSeconds)) / 15);
  Speed(Ls, Rs, TimeInSeconds);
}
void motors::Accelerate(float LeftMaxPercent, float RightMaxPercent, float TimeInSeconds) {
  DLOG
    float SpeedL = LeftSpeed;
  float DeltaLp = LeftMaxPercent - SpeedL;

  float SpeedR = RightSpeed;
  float DeltaRp = RightMaxPercent - SpeedR;

  for ( float i = 0; i < 1; i += 0.01 ) {
    Speed(Interpolate(i, DeltaLp) + SpeedL, Interpolate(i, DeltaRp) + SpeedR, TimeInSeconds / 100);
  }
}
void motors::Brake() {
  DLOG
    Speed(0, 0, 0.1);
}
