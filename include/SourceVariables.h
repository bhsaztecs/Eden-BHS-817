/////////////////
//  constants  //
//  //  /  //  //
//    ports    //
//  //  /  //  //
int Leftm = 0;  // left motor port
int Rightm = 3; // right motor port
int Claw = 0;   // claw servo port
int Arm = 1;    // arm servo port
//  //  /  //  //
int Leftb = 1;  // back left button port
int Rightb = 2; // back right button port
int Frontb = 0; // front bar button port
//  //  /  //  //
int Starts = 1; // start on light sensor port
int Downs = 2;  // downward light sensor port
int Fronts = 3; // frontward light sensor port
//  //  /  //  //
//    other    //
//  //  /  //  //
float Armlength = 8;  // arm length in inches
float Armoffsety = 2; // vertical arm offset in inches
float Armoffsetx = 2; // horizontal arm offset in inches
//  //  /  //  //
float Botoffsetx = 4; // bot offset in inches (roomba starting box is 0,0)
float Botoffsety = 0; // the center of the wheels "axel" is the bot position
//  //  /  //  //
float LMM = 1; // if a motor is drifting, adjust this number accordingly
float RMM = 1; // if its drifting to the left, lower the right motor multiplier  (between 1 and 0)
float timemult = 1; // multiplies time in order to adjust for distance loss (greater than 1)

float WheelRadius = 1.5; // radius of the wheel in inches
float AxelRadius = 3.25; // radius of the axel in inches
float TurnRate = 3.8; //i have no fucking idea how to calculate this man just guess until youre right

float CurrentO = 0; // robot's starting orientation relative to global setup
float CurrentX = 0; // robot's X offset relative to global setup
float CurrentY = 0; // robot's Y offset relative to global setup

int AthenaOn = 1; // disables pathfinding if its draining too many recources
float athenaMargin = 0; // margin of error in which math is chosen, higher for less recourses, lower for more precision
int CollisionChecks = 1; //disables collision checks

// IGNORE THIS SHIT
float DeltaL = 0;
float DeltaR = 0;

float Ooffset = 0;
float Xoffset = 0;
float Yoffset = 0;

int Lv = 0;
int Rv = 0;
float Lp = 0;
float Rp = 0;
int Lo = 0;
int Lt = 0;
int Ro = 0;
int Rt = 0;
float WMM = 1;
char hex[] = {'F', 'F', 'F'};
int commandCalls = 0;
int Collision = 0;

int TurnToOn = 0;
int StraightOn = 0;

int centisec = 0;
int sec = 0;
int min = 0;

bool AutoTravel = false;
bool Confirm = false;
bool Diagnostics = false;
bool AthenaToggle = true;
bool HandsOffToggle = false;
bool CollisionToggle = true;
int menubuffer = 0;