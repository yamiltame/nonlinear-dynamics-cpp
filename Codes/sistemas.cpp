#include "../Headers/sistemas.hpp"
using namespace std;



//Forced Van der Pol-Duffing oscillator with quartic potential energy function. 
void VDPFU4(double t, double x[], double f[],double P[]){
	f[0]=x[1];
	f[1]=P[0]*(1-pow(x[0],2))*x[1]-P[3]*x[0]-P[2]*pow(x[0],2)-P[1]*pow(x[0],3)+P[4]*cos(P[5]*t);
}

//Forced duffing oscillator single well potential
void DuffingFU(double t, double x[], double f[],double P[]){
	f[0]=x[1];
	f[1]=-P[0]*x[1]-P[3]*x[0]-P[2]*pow(x[0],2.0)-P[1]*pow(x[0],3.0)+P[4]*cos(P[5]*t);
}

//Master-Slave control dynamic
void control(double t, double m[],double s[],double f[],double K,int i){
	f[0]=0;
	f[1]=K*(m[i]-s[i]);
}

//Elastic synchronization of system Duffing and Vanderpol. Master-Slave
void Duf_Van_elastic(double t, double x[],double f[],double P[]){
	f[0]=x[1];
	f[1]=(-1)*P[0]*x[1]-P[3]*x[0]-P[2]*pow(x[0],2.0)-P[1]*pow(x[0],3.0)+P[4]*cos(P[5]*t);
	f[2]=x[3];
	f[3]=P[6]*(1-pow(x[2],2))*x[3]-P[9]*x[2]-P[8]*pow(x[2],2.0)-P[7]*pow(x[2],3.0)+P[10]*cos(P[11]*t)+P[12]*(x[0]-x[2]);
}

//Dissipative coupling master-slave configuration vander pol and duffing oscillators
void Duf_Van_dissipative(double t, double x[],double f[],double P[]){
	f[0]=x[1];
	f[1]=(-1)*P[0]*x[1]-P[3]*x[0]-P[2]*pow(x[0],2.0)-P[1]*pow(x[0],3.0)+P[4]*cos(P[5]*t);
	f[2]=x[3];
	f[3]=P[6]*(1-pow(x[2],2))*x[3]-P[9]*x[2]-P[8]*pow(x[2],2.0)-P[7]*pow(x[2],3.0)+P[10]*cos(P[11]*t)+P[12]*(x[1]-x[3]);
}

//Mixed synchronization dissipative and elastic on vanderpol and duffing oscillator
void Duf_Van_mixed(double t, double x[],double f[],double P[]){
	f[0]=x[1];
	f[1]=(-1)*P[0]*x[1]-P[3]*x[0]-P[2]*pow(x[0],2.0)-P[1]*pow(x[0],3.0)+P[4]*cos(P[5]*t);
	f[2]=x[3]+P[12]*(x[0]-x[2]);
	f[3]=P[6]*(1-pow(x[2],2))*x[3]-P[9]*x[2]-P[8]*pow(x[2],2.0)-P[7]*pow(x[2],3.0)+P[10]*cos(P[11]*t)+P[13]*(x[1]-x[3]);
}

//vanderpol duffing master-slave with elastic coupling
void Van_Duf_elastic(double t, double x[],double f[],double P[]){
	f[0]=x[1];
	f[1]=(-1)*P[0]*x[1]-P[3]*x[0]-P[2]*pow(x[0],2.0)-P[1]*pow(x[0],3.0)+P[4]*cos(P[5]*t)+P[12]*(x[2]-x[0]);
	f[2]=x[3];
	f[3]=P[6]*(1-pow(x[2],2))*x[3]-P[9]*x[2]-P[8]*pow(x[2],2.0)-P[7]*pow(x[2],3.0)+P[10]*cos(P[11]*t);
}

void Van_Duf_dissipative(double t, double x[],double f[],double P[]){
	f[0]=x[1];
	f[1]=(-1)*P[0]*x[1]-P[3]*x[0]-P[2]*pow(x[0],2.0)-P[1]*pow(x[0],3.0)+P[4]*cos(P[5]*t)+P[12]*(x[3]-x[1]);
	f[2]=x[3];
	f[3]=P[6]*(1-pow(x[2],2))*x[3]-P[9]*x[2]-P[8]*pow(x[2],2.0)-P[7]*pow(x[2],3.0)+P[10]*cos(P[11]*t);
}

//Heart modeling oscillator
void Corazon(double t, double x[],double f[],double P[]){
	f[0]=x[0]-x[1]-P[0]*x[0]*x[1]-x[0]*pow(x[1],2);
	f[1]=P[1]*x[0]-3*x[1]+P[0]*x[0]*x[1]+x[0]*pow(x[1],2)+P[2]*(x[3]-x[1]);
	f[2]=x[2]-x[3]-P[0]*x[2]*x[3]-x[2]*pow(x[3],2);
	f[3]=P[1]*x[2]-3*x[3]+P[0]*x[2]*x[3]+x[2]*pow(x[3],2)+P[2]*2*(x[1]-x[3]);
}

void Van_Duf_mixed(double t, double x[],double f[],double P[]){
	f[0]=x[1]+P[12]*(x[2]-x[0]);
	f[1]=(-1)*P[0]*x[1]-P[3]*x[0]-P[2]*pow(x[0],2.0)-P[1]*pow(x[0],3.0)+P[4]*cos(P[5]*t)+P[13]*(x[3]-x[1]);
	f[2]=x[3];
	f[3]=P[6]*(1-pow(x[2],2))*x[3]-P[9]*x[2]-P[8]*pow(x[2],2.0)-P[7]*pow(x[2],3.0)+P[10]*cos(P[11]*t);
}

//menu that calls other functions, 
//this looks dumb. Not sure why i couldn't get around. with a dictionary 
//or something
void menu(string opcion,double t,double x[],double f[],double P[]){
	if(opcion.compare("VDPFU4")==0){ 
		VDPFU4(t,x,f,P);
	}
	if(opcion.compare("DuffingFU")==0){ 
		DuffingFU(t,x,f,P);
	}
	if(opcion.compare("Duf_Van_elastic")==0){
		Duf_Van_elastic(t,x,f,P);
	}
	if(opcion.compare("Duf_Van_dissipative")==0){
		Duf_Van_dissipative(t,x,f,P);
	}
	if(opcion.compare("Duf_Van_mixed")==0){
		Duf_Van_mixed(t,x,f,P);
	}
	if(opcion.compare("Van_Duf_elastic")==0){
		Van_Duf_elastic(t,x,f,P);
	}
	if(opcion.compare("Van_Duf_dissipative")==0){
		Van_Duf_dissipative(t,x,f,P);
	}
	if(opcion.compare("Van_Duf_mixed")==0){
		Van_Duf_mixed(t,x,f,P);
	}
	if(opcion.compare("Corazon")==0){
		Corazon(t,x,f,P);
	}

}
