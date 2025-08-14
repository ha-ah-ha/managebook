#include<iostream>
#include<cmath>
#include<iomanip> 
#define M_PI 3.14159265358979323846
using namespace std;

int main(){
    int a,b,H,M;
    cin>>a>>b>>H>>M;
    double angle = abs(30.0 * H + 0.5 * M - 6.0 * M);
    if (angle > 180) {
        angle = 360 - angle;
    }
    angle = angle * M_PI / 180.0;
    double c=2.0*a*b*cos(angle);
    double d=sqrt(a*a+b*b-c);
    cout << fixed << setprecision(15) << d << endl;
    return 0;
}