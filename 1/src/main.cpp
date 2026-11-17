#include <iostream>
#include "Angle.hpp"
#define rad =180.0/3.141592658 //转为弧度制
using namespace std;

int main()
{
    Angle angle(10.0,9.8);
    double distance;
    double height;
    cout<<"请输入距离d(m)";
    cin>>distance;

    double theta =angle.solver(distance);

    if(theta !=-1.0)
    {
        double degree =theta*180.0/3.141592658;
        cout<<"抬升角:"<< degree << endl;
    
    }
    else
    {
        cout<<"无解"<<endl;
    }
    cout<<"请输入距离高度h(m)";
    cin >> height;
    double time = 0.0;
    double thetaHeight = angle.solver(distance,height,time);
    if(thetaHeight !=-1.0)
    {
        cout<<"抬升角:"<< thetaHeight*180.0/3.141592658 << endl;
        cout<<"时间:"<< time <<"s"<< endl;
    }
    else
    {
        cout<<"无解"<<endl;
    }
    return 0;
}