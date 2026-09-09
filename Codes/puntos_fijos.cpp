#include "../Headers/tools.hpp"
#include "../Headers/sistemas.hpp"
using namespace std;

int main(int argc,char *argv[]){
	string archivo=argv[1];
	int p;
	double ini,dt,fin;
	ifstream datos;
	datos.open(archivo.c_str());
	string name;
	datos>>name;
	datos>>ini;
	datos>>fin;
	datos>>dt;
	cout<<archivo<<" puta\n";
	datos>>p;
	double P[p];
	for(int i=0;i<p;i++){
		datos>>P[i];
	}
	double x[3];
	cout << name<<endl;
	ofstream salida(name.c_str());
	double promedio[3];
	for(double t=ini;t<=fin;t+=dt){
		double P2[]={P[0],P[1],P[2],-P[3]*cos(P[4]*t)};
		resuelve_cubica(P2,x);
		salida<<t<<" "<<x[0]<<" "<<x[1]<<" "<<x[2]<<endl;
	}
	datos.close();
	salida.close();
	}
