#pragma once
#include "basic.h"
namespace motors {
void ClearMotorRotations() {
  DLOG KIPR::cmpc(LeftMotor);
  KIPR::cmpc(RightMotor);
}
void Velocity() {
  DLOG while (1) {
    float VLo = KIPR::gmpc(LeftMotor);
    float VRo = KIPR::gmpc(RightMotor);
    KIPR::msleep(100);
    float VLt = KIPR::gmpc(LeftMotor);
    float VRt = KIPR::gmpc(RightMotor);

    float Lv = (VLt - VLo) * 10;
    float Rv = (VRt - VRo) * 10;
    LeftSpeed = Lv * 0.06;
    RightSpeed = Rv * 0.06;
  }
}
void Speed(float LeftPercent, float RightPercent, float TimeInSeconds) {
  DLOG float Lo = TTIW(KIPR::gmpc(LeftMotor));
  float Ro = TTIW(KIPR::gmpc(RightMotor));
  KIPR::motor(LeftMotor, (LeftPercent * LMM));
  KIPR::motor(RightMotor, (RightPercent * RMM));
  KIPR::msleep((TimeInSeconds * 1000) * TimeMultiplier);
  float Lt = TTIW(KIPR::gmpc(LeftMotor));
  float Rt = TTIW(KIPR::gmpc(RightMotor));
  float DelL = Lt - Lo;
  float DelR = Rt - Ro;
  pathFind::AthenaDecision(DelL, DelR);
}
void Rotation(float LeftDegrees, float RightDegrees, float TimeInSeconds) {
  DLOG float DistL = DTIW(LeftDegrees);
  float DistR = DTIW(RightDegrees);
  Distance(DistL, DistR, TimeInSeconds);
}
void Distance(float LeftInches, float RightInches, float TimeInSeconds) {
  DLOG float Ls = float((ITTW(LeftInches / TimeInSeconds)) / 15.0);
  float Rs = float((ITTW(RightInches / TimeInSeconds)) / 15.0);
  Speed(Ls, Rs, TimeInSeconds);
}
void Accelerate(float LeftMaxPercent, float RightMaxPercent,
                float TimeInSeconds) {
  DLOG float SpeedL = LeftSpeed;
  float DeltaLp = LeftMaxPercent - SpeedL;

  float SpeedR = RightSpeed;
  float DeltaRp = RightMaxPercent - SpeedR;

  for (float i = 0; i < 1; i += 0.01) {
    Speed(Interpolate(i, DeltaLp) + SpeedL, Interpolate(i, DeltaRp) + SpeedR,
          TimeInSeconds / 100);
  }
}
void Brake() { DLOG Speed(0, 0, 0.1); }
} // namespace motors
