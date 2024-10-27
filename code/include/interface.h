#pragma once
#include "basic.h"

class Motors {
  int LeftPort, RightPort;
  float LMM, RMM, TimeMultiplier;
  void NormalizeMultipliers(float lmm, float rmm) {
    float WMM = 1;
    if (LMM > RMM) {
      WMM = 1 / LMM;
    } else {
      WMM = 1 / RMM;
    }

    RMM = RMM * WMM;
    LMM = LMM * WMM;
    TimeMultiplier = WMM;
  }

public:
  Motors(int leftport, int rightport, float lmm, float rmm) {
    LeftPort = leftport;
    RightPort = rightport;
    NormalizeMultipliers(lmm, rmm);
    Clear();
  }
  void Clear() { BKND::motors::ClearMotorRotations(LeftPort, RightPort); }
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
