#pragma once
#include "basic.h"
namespace motors {
using namespace BKND;
using namespace BKND::motors;
using namespace KIPR;
void ClearMotorRotations(int LeftMotor, int RightMotor) {
  DLOG cmpc(LeftMotor);
  cmpc(RightMotor);
}
void Velocity(int LeftMotor, int RightMotor, float &LeftSpeed,
              float &RightSpeed) {
  DLOG while (1) {
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
void Speed(float LeftPercent, float RightPercent, float TimeInSeconds,
           int LeftMotor, int RightMotor, float LMM, float RMM,
           float TimeMultiplier) {
  DLOG float Lo = TTIW(gmpc(LeftMotor));
  float Ro = TTIW(gmpc(RightMotor));
  motor(LeftMotor, (LeftPercent * LMM));
  motor(RightMotor, (RightPercent * RMM));
  msleep((TimeInSeconds * 1000) * TimeMultiplier);
  float Lt = TTIW(gmpc(LeftMotor));
  float Rt = TTIW(gmpc(RightMotor));
  float DelL = Lt - Lo;
  float DelR = Rt - Ro;
  pathFind::AthenaDecision(DelL, DelR);
}
void Rotation(float LeftDegrees, float RightDegrees, float TimeInSeconds,
              int LeftMotor, int RightMotor, float LMM, float RMM,
              float TimeMultiplier) {
  DLOG float DistL = DTIW(LeftDegrees);
  float DistR = DTIW(RightDegrees);
  Distance(DistL, DistR, TimeInSeconds, LeftMotor, RightMotor, LMM, RMM,
           TimeMultiplier);
}
void Distance(float LeftInches, float RightInches, float TimeInSeconds,
              int LeftMotor, int RightMotor, float LMM, float RMM,
              float TimeMultiplier) {
  DLOG float Ls = float((ITTW(LeftInches / TimeInSeconds)) / 15.0);
  float Rs = float((ITTW(RightInches / TimeInSeconds)) / 15.0);
  Speed(Ls, Rs, TimeInSeconds, LeftMotor, RightMotor, LMM, RMM, TimeMultiplier);
}
void Accelerate(float LeftMaxPercent, float RightMaxPercent,
                float TimeInSeconds, int LeftMotor, int RightMotor,
                float &LeftSpeed, float &RightSpeed, float LMM, float RMM,
                float TimeMultiplier) {
  DLOG float SpeedL = LeftSpeed;
  float DeltaLp = LeftMaxPercent - SpeedL;

  float SpeedR = RightSpeed;
  float DeltaRp = RightMaxPercent - SpeedR;

  for (float i = 0; i < 1; i += 0.01) {
    Speed(Interpolate(i, DeltaLp) + SpeedL, Interpolate(i, DeltaRp) + SpeedR,
          TimeInSeconds / 100, LeftMotor, RightMotor, LMM, RMM, TimeMultiplier);
  }
}
void Brake(int LeftMotor, int RightMotor) {
  DLOG Speed(0, 0, 0.1, LeftMotor, RightMotor, 1, 1, 1);
}
} // namespace motors
