#include "MovingObject.h"
#include <cmath>

ClassImp(MovingObject);
MovingObject::MovingObject(){ // by default set components to zero
    fVx = 0.0;
    fVy = 0.0;
    fVz = 0.0;
}
MovingObject::MovingObject(Double_t vx, Double_t vy, Double_t vz){
    fVx = vx; //other constructor that initialize them from their args
    fVy = vy;
    fVz = vz;
}
MovingObject::~MovingObject(){//initializes empty destructor
}

Double_t MovingObject::Vx() const{//getter, returns velocity components
    return fVx;
}
Double_t MovingObject::Vy() const{ //getter
    return fVy;
}
Double_t MovingObject::Vz() const{//getter
    return fVz;
}
void MovingObject::SetVelocity(Double_t vx, Double_t vy, Double_t vz){
    fVx = vx;//update the components
    fVy = vy;
    fVz = vz;
}
Double_t MovingObject::Speed() const { //calc the speed
    return std::sqrt((fVx*fVx) + (fVy*fVy) + (fVz*fVz));
}
Double_t MovingObject::HorizontalSpeed() const { //calc the speed but discard the z axis
    return std::sqrt((fVx*fVx) + (fVy*fVy));
}