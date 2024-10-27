#pragma once
#include "basic.h"

class Motors {
  int LeftPort, RightPort;
  float LMM, RMM, TMM;
  float LeftSpeed = 0, RightSpeed = 0;
  void NormalizeMultipliers(float lmm, float rmm) {
    float WMM = 1;
    if (LMM > RMM) {
      WMM = 1 / LMM;
    } else {
      WMM = 1 / RMM;
    }

    RMM = RMM * WMM;
    LMM = LMM * WMM;
    TMM = WMM;
  }

public:
  Motors(int leftport, int rightport, float lmm, float rmm) {
    LeftPort = leftport;
    RightPort = rightport;
    NormalizeMultipliers(lmm, rmm);
    Clear();
  }
  void Clear() { BKND::motors::ClearMotorRotations(LeftPort, RightPort); }
  void Velocity() {
    BKND::motors::Velocity(LeftPort, RightPort, LeftSpeed, RightSpeed);
  }
  void Speed(float LeftGoalPercent, float RightGoalPercent,
             float TimeInSeconds) {
    BKND::motors::Speed(LeftGoalPercent, RightGoalPercent, TimeInSeconds,
                        LeftPort, RightPort, LMM, RMM, TMM);
  }
  void Rotation(float LeftGoalDegrees, float RightGoalDegrees,
                float TimeInSeconds) {
    BKND::motors::Rotation(LeftGoalDegrees, RightGoalDegrees, TimeInSeconds,
                           LeftPort, RightPort, LMM, RMM, TMM);
  }
  void Distance(float LeftGoalInches, float RightGoalInches,
                float TimeInSeconds) {
    BKND::motors::Distance(LeftGoalInches, RightGoalInches, TimeInSeconds,
                           LeftPort, RightPort, LMM, RMM, TMM);
  }
  void Accelerate(float LeftGoalPercent, float RightGoalPercent,
                  float TimeInSeconds) {
    BKND::motors::Accelerate(LeftGoalPercent, RightGoalPercent, TimeInSeconds,
                             LeftPort, RightPort, LeftSpeed, RightSpeed, LMM,
                             RMM, TMM);
  }
  void Brake() { BKND::motors::Brake(LeftPort, RightPort); }
};
class Servos {
public:
  Servos(int port, BKND::P2D min, BKND::P2D max) {}
};
class Sensors {
public:
  Sensors(int port, BKND::sensors::type) {}
};
class PathFind {
public:
  PathFind(float margin, Motors readfrom) {}
};
class Misc {
public:
  Misc(Sensors startlight, Motors applyto) {}
};
