#include "../include/declarations.h"
namespace BKND {
namespace motors {
void ClearMotorRotations(pass Vals) {
  cmpc(Vals.leftmotor);
  cmpc(Vals.rightmotor);
}
void Velocity(pass Vals) {
  while (1) {
    float VLo = gmpc(Vals.leftmotor);
    float VRo = gmpc(Vals.rightmotor);
    msleep(100);
    float VLt = gmpc(Vals.leftmotor);
    float VRt = gmpc(Vals.rightmotor);

    float Lv = (VLt - VLo) * 10;
    float Rv = (VRt - VRo) * 10;
    Vals.leftspeed = Lv * 0.06;
    Vals.rightspeed = Rv * 0.06;
  }
}
void Speed(float p_leftpercent, float p_rightpercent, float p_timeinseconds,
           pass Vals) {
  float Lo = BKND::TTIW(gmpc(Vals.leftmotor));
  float Ro = BKND::TTIW(gmpc(Vals.rightmotor));
  motor(Vals.leftmotor, (p_leftpercent * Vals.lmm));
  motor(Vals.rightmotor, (p_rightpercent * Vals.rmm));
  msleep((p_timeinseconds * 1000) * Vals.tmm);
  float Lt = BKND::TTIW(gmpc(Vals.leftmotor));
  float Rt = BKND::TTIW(gmpc(Vals.rightmotor));
  float DelL = Lt - Lo;
  float DelR = Rt - Ro;
  BKND::pathFind::AthenaDecision(DelL, DelR, Vals);
}
void Distance(float p_leftinches, float p_rightinches, float p_timeinseconds,
              pass Vals) {
  float Ls = float((BKND::ITTW(p_leftinches / p_timeinseconds)) / 15.0);
  float Rs = float((BKND::ITTW(p_rightinches / p_timeinseconds)) / 15.0);
  Speed(Ls, Rs, p_timeinseconds, Vals);
}
void Rotation(float p_leftdegrees, float p_rightdegrees, float p_timeinseconds,
              pass Vals) {
  float DistL = BKND::DTIW(p_leftdegrees);
  float DistR = BKND::DTIW(p_rightdegrees);
  BKND::motors::Distance(DistL, DistR, p_timeinseconds, Vals);
}
void Accelerate(float p_leftmaxpercent, float p_rightmaxpercent,
                float p_timeinseconds, pass Vals) {
  float SpeedL = Vals.leftspeed;
  float DeltaLp = p_leftmaxpercent - SpeedL;

  float SpeedR = Vals.rightspeed;
  float DeltaRp = p_rightmaxpercent - SpeedR;

  for (float i = 0; i < 1; i += 0.01) {
    Speed(BKND::Interpolate(i, DeltaLp) + SpeedL,
          BKND::Interpolate(i, DeltaRp) + SpeedR, p_timeinseconds / 100, Vals);
  }
}
void Brake(pass Vals) { Speed(0, 0, 0.1, Vals); }
} // namespace motors
} // namespace BKND
