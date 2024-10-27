#pragma once
#include "basic.h"
namespace motors {
using namespace BKND;
using namespace BKND::motors;
using namespace KIPR;
void ClearMotorRotations(int p_leftmotor, int p_rightmotor) {
  DLOG cmpc(p_leftmotor);
  cmpc(p_rightmotor);
}
void Velocity(int p_leftmotor, int p_rightmotor, float &p_leftspeed,
              float &p_rightspeed) {
  DLOG while (1) {
    float VLo = gmpc(p_leftmotor);
    float VRo = gmpc(p_rightmotor);
    msleep(100);
    float VLt = gmpc(p_leftmotor);
    float VRt = gmpc(p_rightmotor);

    float Lv = (VLt - VLo) * 10;
    float Rv = (VRt - VRo) * 10;
    p_leftspeed = Lv * 0.06;
    p_rightspeed = Rv * 0.06;
  }
}
void Speed(float p_leftpercent, float p_rightpercent, float p_timeinseconds,
           int p_leftmotor, int p_rightmotor, float p_lmm, float p_rmm,
           float p_timemultiplier) {
  DLOG float Lo = TTIW(gmpc(p_leftmotor));
  float Ro = TTIW(gmpc(p_rightmotor));
  motor(p_leftmotor, (p_leftpercent * p_lmm));
  motor(p_rightmotor, (p_rightpercent * p_rmm));
  msleep((p_timeinseconds * 1000) * p_timemultiplier);
  float Lt = TTIW(gmpc(p_leftmotor));
  float Rt = TTIW(gmpc(p_rightmotor));
  float DelL = Lt - Lo;
  float DelR = Rt - Ro;
  pathFind::AthenaDecision(DelL, DelR);
}
void Rotation(float p_leftdegrees, float p_rightdegrees, float p_timeinseconds,
              int p_leftmotor, int p_rightmotor, float p_lmm, float p_rmm,
              float p_timemultiplier) {
  DLOG float DistL = DTIW(p_leftdegrees);
  float DistR = DTIW(p_rightdegrees);
  Distance(DistL, DistR, p_timeinseconds, p_leftmotor, p_rightmotor, p_lmm,
           p_rmm, p_timemultiplier);
}
void Distance(float p_leftinches, float p_rightinches, float p_timeinseconds,
              int p_leftmotor, int p_rightmotor, float p_lmm, float p_rmm,
              float p_timemultiplier) {
  DLOG float Ls = float((ITTW(p_leftinches / p_timeinseconds)) / 15.0);
  float Rs = float((ITTW(p_rightinches / p_timeinseconds)) / 15.0);
  Speed(Ls, Rs, p_timeinseconds, p_leftmotor, p_rightmotor, p_lmm, p_rmm,
        p_timemultiplier);
}
void Accelerate(float p_leftmaxpercent, float p_rightmaxpercent,
                float p_timeinseconds, int p_leftmotor, int p_rightmotor,
                float &p_leftspeed, float &p_rightspeed, float p_lmm,
                float p_rmm, float p_timemultiplier) {
  DLOG float SpeedL = p_leftspeed;
  float DeltaLp = p_leftmaxpercent - SpeedL;

  float SpeedR = p_rightspeed;
  float DeltaRp = p_rightmaxpercent - SpeedR;

  for (float i = 0; i < 1; i += 0.01) {
    Speed(Interpolate(i, DeltaLp) + SpeedL, Interpolate(i, DeltaRp) + SpeedR,
          p_timeinseconds / 100, p_leftmotor, p_rightmotor, p_lmm, p_rmm,
          p_timemultiplier);
  }
}
void Brake(int p_leftmotor, int p_rightmotor) {
  DLOG Speed(0, 0, 0.1, p_leftmotor, p_rightmotor, 1, 1, 1);
}
} // namespace motors
