#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
using namespace std;
void VDPnF(double t, double x[], double f[],double P[]);
void VDPF(double t, double x[], double f[],double P[]);
void VDPF2(double t, double x[], double f[],double P[]);
void VDPFU3(double t, double x[], double f[],double P[]);
void VDPU4(double t, double x[], double f[],double P[]);
void VDPFU4(double t, double x[], double f[],double P[]);
void DuffingU3(double t, double x[], double f[],double P[]);
double U(double x,double P[],int d);
void crazy(double t, double x[], double f[],double P[]);
void DuffingFU(double t, double x[], double f[],double P[]);
void menu(string opcion,double t,double x[],double f[],double P[]);
void Duf_Van_elastic(double t, double x[],double f[],double P[]);
void Duf_Van_dissipative(double t, double x[],double f[],double P[]);
void Duf_Van_mixed(double t, double x[],double f[],double P[]);
void Van_Duf_elastic(double t, double x[],double f[],double P[]);
void Van_Duf_dissipative(double t, double x[],double f[],double P[]);
void Van_Duf_mixed(double t, double x[],double f[],double P[]);