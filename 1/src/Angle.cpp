#include "Angle.hpp"
#include <cmath>

Angle::Angle(double initspeed,double gravity)
:initspeed(initspeed),gravity(gravity)
{

}
double Angle::solver(double distance)
{
    if (distance<=0.0)
    {
        return -1.0;
    }
 double sin2Theta = (gravity*distance)/(initspeed*initspeed);
if (sin2Theta > 1.0)
{
    return -1.0;
}
return std::asin(sin2Theta)/2.0;
} 
double Angle::solver(double distance,double height,double &time)
{
    if (distance<=0.0)
    {
        time =-1.0;
        return -1.0;
    }
    double delta = initspeed*initspeed*initspeed*initspeed - gravity*(gravity*distance*distance + 2.0*height*initspeed*initspeed);
    if (delta < 0)
    {
        return -1.0;
    }
    double theta = std::atan((initspeed*initspeed + std::sqrt(delta))/(gravity*distance));
    time = 2.0 * initspeed * std::sin(theta) / gravity;
    return theta;
}
