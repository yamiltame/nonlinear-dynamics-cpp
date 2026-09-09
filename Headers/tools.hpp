#include "libs.hpp"
using namespace std;

string print_array(int n, double A[]);
int getnum(string mess);
double getdouble(string mess);
void parametros(double P[],string filename);
void rk4(double y[], double dt, double yout[], double t,double params[],string sistema,
    void (*menu)(string opcion,double t, double x[],double f[],double P[]));
void make_solution(int n,double x[],double xout[],
    double params[],double t,double dt,double l1, double lim,string sistema,
    void (*menu)(string opcion,double t, double x[],double f[],double P[]));
string phase_portrait(int n,double t,double dt,double lim,double I[][2],
	double dx,string nombre,double params[],int p,string sistema,
    void (*menu)(string opcion,double t, double x[],double f[],double P[]));
string readline(int file, int &p);
string Retrato_fase(string filename);
string get_solucion(string filename);
void resuelve_cubica(double A[],double x[]);
void puntos_fijos(double inicio,double fin,double P[]);
void valor_promedio(double inicio,double fin, double P[]);
string diagrama_bifurcacion(int n, double x[], double P[],int np,int index,double finp,double dp,
    double t,double dt,double t1,double lim, string sistema,string param_name,double ps,
    void (*menu)(string opcion,double t, double x[],double f[],double P[]));
string make_retrato_limite(int n, double x[], double P[],int np,int index,double finp,double dp,
    double t,double dt,double t1,double lim, string sistema,string param_name,double ps, int delay,
    void (*menu)(string opcion,double t, double x[],double f[],double P[]));
string get_bifurcacion(string filename);
string get_retrato_limite(string filename);
string get_synch(string filename);
string bif_synch(int n, double x[], double P[],int np,int index,double finp,double dp,
    double t,double dt,double t1,double lim, string sistema, string param_name,double ps,double definicion,
    void (*menu)(string opcion,double t, double x[],double f[],double P[]));
string get_bif_synch(string filename);
string make_synch(int n,double start,double elim[],double x[],double xout[],
    double params[],double t,double dt, double lim,string sistema,double definicion,
    void (*menu)(string opcion,double t, double x[],double f[],double P[]));
