#ifndef Angle_hpp
#define Angle_hpp

class Angle
{
private: 
double initspeed;
double gravity;

public:
Angle(double initspeed,double gravity);
double solver(double distance);
double solver(double distance,double height,double &time); 

};
#endif
