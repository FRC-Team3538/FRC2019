#include "robotmap.h"


robotmap::robotmap() {
    
    driveRight.SetInverted(false);
    driveLeft.SetInverted(true);
    
    driveBase.SetExpiration(0.1);
}