#include "../Headers/libs.hpp"
#include "../Headers/sistemas.hpp"
using namespace std;

//para cortar strings
string Sstr(double d){
    string S=to_string(d);
    string r="";
    for(int i=0;i<6;i++){
        r+=S[i];
    }
    return r;
}

//print array
string print_array(int n, double A[]){
    string vec="[";
    for(int i=0;i<(n-1);i++){
        vec+=Sstr(A[i])+",";
    }
    vec+=Sstr(A[n-1])+"]";
    return vec;

}

//pedir int al ususario
int getnum(string mess){
        cout<<mess;
        int num;
        while(!(cin>>num)||num<0){
                cout<<"numero invalido\n";
                cin.clear(); cin.ignore(100,'\n');}
        return num;
    }

//pedir double al usuario
double getdouble(string mess){
        cout<<mess;
        double num;
        while(!(cin>>num)){
                cout<<"numero invalido\n";
                cin.clear(); cin.ignore(100,'\n');}
        return num;
        }


double* parametros(string filename){
    int p;
    ifstream filetoread(filename.c_str());
    filetoread>>p;
    static double *P;
    for(int i=0;i<p;i++){
        filetoread >> *(P+i);
    }
    filetoread.close();
    return P;
}

/*
Runge-Kutta 4th order
you give dimension n, vector y of inputs or initial conditions, dt step of time, yout auxiliar vector
t initial time, parmams[] parameters, string sistema is the name of the system
menu is the function caller of systems previously defined.
*/
void rk4(int n,double y[], double dt, double yout[], double t,double params[],string sistema,
	void (*menu)(string opcion,double t, double x[],double f[],double P[])){

    int j;
    double k1[n];
    double k2[n];
    double k3[n];
    double k4[n];
    double f[n];
    double yt[n];
    menu(sistema,t,y,f,params);
    for(j=0;j<n;j++){
        k1[j]=dt*f[j];
        yt[j]=y[j] + 0.5*k1[j];
        }
    menu(sistema,t+0.5*dt,yt,f,params);
    for(j=0;j<n;j++){
        k2[j]=dt*f[j];
        yt[j]=y[j] + 0.5*k2[j];
        }
    menu(sistema,t+0.5*dt,yt,f,params);
    for(j=0;j<n;j++){
        k3[j]=dt*f[j];
        yt[j]=y[j] + k3[j];
        }
    menu(sistema,t+dt,yt,f,params);
    for(j=0;j<n;j++){
        k4[j]=dt*f[j];
        }
    for(j=0;j<n;j++){
        yout[j]=y[j] +(1.0/6.0)*(k1[j]+2.0*k2[j]+2.0*k3[j]+k4[j]);
        }
//    cout<<"\n yout[]="<<print_array(n,yout)<<endl;
    }

//entgradas n es dimension del sistema, x[] es el vector de variables con condiciones iniciales, xout[] es un arreglo auxiliar
//params[] es el arreglo de parametros, t el tiemmpo inicial, dt el tmaño del paso, lim es el tiempo finaly sistema es la funcion
//que corressponde al sistema de ecuaciones

bool check4nan(double x[],int n){
    bool g=false;
    for(int j=0;j<n;j++){
        if(isnan(x[j])){g=true;cout<<"VALIÓ PITO BANDA"<<endl;break;}
    }
    return g;

}


string make_retrato_limite(int n, double x[], double P[],int np,int index,double finp,double dp,
    double t,double dt,double t1,double lim, string sistema, string param_name,double ps, int delay,
    void (*menu)(string opcion,double t, double x[],double f[],double P[])){
    auto start=chrono::steady_clock::now();
	string dir="Gifs";
	struct stat sb;
	if(stat(dir.c_str(),&sb)!=0){
		string dirr="mkdir "+dir;
		system(dirr.c_str());
	}
	dir+="/"+sistema;
	if(stat(dir.c_str(),&sb)!=0){
		string dirr="mkdir "+dir;
		system(dirr.c_str());
	}
    string nombre="Gifs/"+sistema+"/condin";
    for(int i=0;i<n;i++){
        nombre+="_"+Sstr(x[i]);
    }
    string gnuname=nombre+".gnu";
    nombre+=".txt";
    ofstream bifurcacion,gnufile;
    int i;
    double f[n], xout[n], xt[n];
    cout<<"Sistema: "<<sistema<<"Retratos fase en gif, condiciones iniciales ti="
        <<t<<", con paso de tiempo dt="
        <<dt<<", el cilo comienza en t0="<<t1<<"termina en t1="<<lim<<endl;
    bifurcacion.open(nombre.c_str());
    gnufile.open(gnuname.c_str());
    gnufile<<"set terminal gif animate delay "<<delay<<endl;
    gnufile<<"set output '"<<dir<<"/retrato_limite.gif'"<<endl;
    gnufile<<"set xlabel \"$x_3(t)$\""<<endl;
    gnufile<<"set ylabel \"$x_4(t)$\""<<endl;
    double p;
	int inicioevery=0,finevery=0;
    for(p=P[index];p<=finp;p+=dp){
//		cout<<"CONDICIONES INICIALES INICIANDO"<<endl;
        for(int i=0;i<n;i++){
			xt[i]=x[i];
//			cout<<" "<<xt[i]<<endl;
		}
        double P2[np],tax;
        for(int i=0;i<np;i++){ P2[i]=P[i];}
        P2[index]=p;
        for(tax=t;tax<=lim;tax+=dt){
            if(tax>=t1){
                bifurcacion<<tax<<" "<<p<<" ";
                for(i=0;i<n;i++){ bifurcacion<<xt[i]<<" ";}
                bifurcacion<<endl;
				finevery+=1;
            }
            rk4(n,xt,dt,xout,tax,P2,sistema,menu);
            if(check4nan(xout,n)){break;}
            for(int i=0;i<n;i++){ xt[i] = xout[i];}
        }
	    gnufile<<"plot '"+nombre+"' every ::"<<inicioevery<<"::"<<finevery<<" using 5:6 w l lw "<<ps<<" lc 8 title '"<<param_name<<"="<<p<<"'"<<endl;
		inicioevery=finevery;
    }
    gnufile<<"\n unset output"<<endl;
    bifurcacion.close();
    gnufile.close();
    string cmd="gnuplot "+gnuname;
    auto stop=chrono::steady_clock::now();
    auto times=chrono::duration_cast<chrono::seconds>(stop-start).count();
    auto timem=chrono::duration_cast<chrono::minutes>(stop-start).count();
	cout<<"Tiempo de ejcución algoritmo: ";
    cout<<" "<<times<<"Seg = "<<timem<<"Min"<<endl;
    start=chrono::steady_clock::now();
    system(cmd.c_str());
    stop=chrono::steady_clock::now();
    times=chrono::duration_cast<chrono::seconds>(stop-start).count();
    timem=chrono::duration_cast<chrono::minutes>(stop-start).count();
	cout<<"Tiempo de ejcución gnuplot: ";
    cout<<" "<<times<<"Seg = "<<timem<<"Min"<<endl;
	cmd="open "+dir+"/retrato_limite.gif";
	system(cmd.c_str());
    return "operación exitosa";
    }

/*
n dimensión
x[] es el arreglo que contiene las soluciones
xout[] es el auxiliar de x[] para computar
params[] parametros del sistema
t es el tiempo
dt es el paso del tiempo
l1 es el tiempo donde comienza a registrar la simulación en el archivo
lim es el límite de tiempo que corre la simulación
sistema es el nombre del sistema
*menu es una funcion cualquiera que corresponde al sistema de ecuaciones.
*/
string make_solution(int n,double x[],double xout[],
	double params[],double t,double dt,double l1, double lim,string sistema,
	void (*menu)(string opcion,double t, double x[],double f[],double P[])){

//establece el directorio "Solutions" para guardar lo que se genera en la simulación
	string dir="Solutions";

//struct stat sb da info sobre el directorio sistema. 
	struct stat sb;

//checar que exista "Solutions", si no lo crea
	if(stat(dir.c_str(),&sb)!=0){
		string dirr="mkdir "+dir;
		system(dirr.c_str());
	}

//Busca directorio del sistema específico, si no lo crea.
	dir+="/"+sistema;
	if(stat(dir.c_str(),&sb)!=0){
		string dirr="mkdir "+dir;
		system(dirr.c_str());
	}

//crea un nombre para los resultados de la simulación
//lleva los valores de las condiciones iniciales de las variables.
    string nombre=dir+"/condini";
    for(int i=0;i<n;i++){
        nombre+="_"+Sstr(x[i]);
    }

//crea nombre para archivo gnu para graficar
    string gnuname=nombre+".gnu";
    nombre+=".txt";
    ofstream solucion,gnufile;
    int i;
	double f[n];

//Abre el archivo para instrucciones de gnuplot
//-----gnuplot-----
    gnufile.open(gnuname.c_str());
    gnufile<<"set terminal epslatex font ',14' standalone"<<endl;
    gnufile<<"set output '"<<dir<<"/espaciofase.tex'"<<endl;
    gnufile<<"set xlabel \"$x_1(t)$\" font ',16'\n set ylabel \"$x_2(t)$\" font ',16'\n set tics font ',12'\n";
    gnufile<<"plot '"+nombre+"' using 2:3 w l lw 2 lc 8 notitle\n unset output\n";
    gnufile<<"unset output\n";
    //se generan  multiples archivos con los valores de cada variable respecto al tiempo.
    // n archivos para cada x[i]
    //cada uno soli.tex
    for(int i=1;i<n+1;i++){
        gnufile<<"set output '"<<dir<<"/sol"+to_string(i)+".tex"<<endl;
        gnufile<<"set xlabel \"$t$\" font ',16'\n set ylabel \"$x_"+to_string(i)+"(t)$\" font ',16'\n set tics font ',12'\n";
    	gnufile<<"plot '"+nombre+"' u 1:"+to_string(i+1)+" w l lw 0.5 lc 8 notitle"<<endl;
	    gnufile<<"unset output"<<endl;
    }
    gnufile.close();

//el ciclo principal, empieza en t y termina en lim
//La solución se empieza a escribir desde l1.
//-----rk4-----
    solucion.open(nombre.c_str());
    for(;t<=lim;t+=dt){
    	if(t>=l1){
		    solucion<<t<<" ";
            for(i=0;i<n;i++){
                solucion<<x[i]<<" ";
                }
            solucion<<endl;
	       }
        rk4(n,x,dt,xout,t,params,sistema,menu);
        if(check4nan(xout,n)){
            break;
        }
        for(int i=0;i<n;i++){ x[i] = xout[i];}
        }
    solucion.close();

//corre el comando guardado en archivo gnuname
    string cmd="gnuplot "+gnuname;
    cout<<"\n se correrá el commando: \n"<<cmd<<"\n";
    system(cmd.c_str());
    cout<<"se logró"<<endl;

//lo llama espaciofase, lo compila con latex y después 
//compila los dvi. Luego compila los archivos de sol 
	string filename=dir+"/espaciofase";
    cmd="latex -interaction=nonstopmode "+filename+".tex"
    system(cmd.c_str());
    cmd="dvips "+filename+".dvi && ";
    for(int i=0;i<n;i++){
		filename=dir+"/sol"+to_string(i+1);
		cmd+="latex -interaction=nonstopmode "+filename+".tex && ";
	}
//mover los archivos auxiliares a la carpeta
	cmd+="mv *.aux *.dvi *.log "+dir+" && ";
    for(int i=0;i<n-1;i++){
		filename=dir+"/sol"+to_string(i+1);
		cmd+="dvips "+filename+".dvi && ";
	}
	filename=dir+"/sol"+to_string(n);

	cmd+="dvips "+filename+".dvi";
    cout<<"\n se correrá el commando: \n"<<cmd<<"\n";
	system(cmd.c_str());

	cmd="mv *.ps "+dir;
    cout<<"\n se correrá el commando: \n"<<cmd<<"\n";
	system(cmd.c_str());

//abre los archivos ps 
	cmd="open "+dir+"/espaciofase.ps && open "+dir+"/sol4.ps";
    cout<<"\n se correrá el commando: \n"<<cmd<<"\n";
	system(cmd.c_str());

    return "Operación exitosa";
    }


//funcion para normalizar
void normalize(double f[],double N[],double dt){
	double norm=sqrt(f[0]*f[0]+f[1]*f[1]);
	N[0]=f[0]/norm;
	N[1]=f[1]/norm;
	f[0]=N[0]*dt;
	f[1]=N[1]*dt;
	}

/*
This function makes a bifurcation diagram of a given dynamical system. It takes in 
dimention, vectors x for variables, vector P[] for parameters, np number of parameters
index must be the index of the parameter to iterate, finp is superior limit for the parameter,
dp is the step in the parameter variation, t time, dt step of time, t1 is the start of the file,
lim is time limit, sistema is the systems name, param_name is the parameter name, 
ps is pont size i guess. and then again the menu function that contains the system functions.
*/
string diagrama_bifurcacion(int n, double x[], double P[],int np,int index,double finp,double dp,
    double t,double dt,double t1,double lim, string sistema, string param_name,double ps,
    void (*menu)(string opcion,double t, double x[],double f[],double P[])){
    
//start the clock to check hoy many time it took
    auto start=chrono::steady_clock::now();

//Open a file to save the simulation
	string dir="Bifurcaciones";
	struct stat sb;
	if(stat(dir.c_str(),&sb)!=0){
		string dirr="mkdir "+dir;
		system(dirr.c_str());
	}
	dir+="/"+sistema;
	if(stat(dir.c_str(),&sb)!=0){
		string dirr="mkdir "+dir;
		system(dirr.c_str());
	}
    //nombre is the name of the file where bifurcation data goes.
    string nombre=dir+"/condini";
    for(int i=0;i<n;i++){
        nombre+="_"+Sstr(x[i]);
    }
    string gnuname=nombre+".gnu";
    nombre+=".txt";
    ofstream bifurcacion,gnufile;
    int i;
    double f[n], xout[n], xt[n];

//little message to the terminal about what you are doing
    cout<<"Diagrama de bifurcacion, condiciones iniciales ti="<<t<<endl;
        for(int i=0;i<n;i++){
			cout<<" "<<x[i];
		}
    cout<<", con paso de tiempo dt="<<dt<<", hasta el tiempo t="<<lim<<endl;

//open files to save data
    bifurcacion.open(nombre.c_str());
    gnufile.open(gnuname.c_str());
    double p;

//main loop for bifurcation diagram. Solves for the limit values and 
    for(p=P[index];p<=finp;p+=dp){
        //set initial values for xt[]
        for(int i=0;i<n;i++){
			xt[i]=x[i];
		}
        //create array of parámeters and an auxiliary time
        double P2[np],tax;
        for(int i=0;i<np;i++){ P2[i]=P[i];}
        P2[index]=p;
        int c=0;
        //loop for solving the system
        for(tax=t;tax<=lim;tax+=dt){
            //if we are in the range of t1<tax<lim
            if(tax>=t1){
                bifurcacion<<tax<<" "<<p<<" ";
                for(i=0;i<n;i++){ bifurcacion<<xt[i]<<" ";}
                bifurcacion<<endl;
            }
            //solving the system with runge kutta 4th order
            rk4(n,xt,dt,xout,tax,P2,sistema,menu);
            if(check4nan(xout,n)){break;}
            //update xt[] with xout[] what comes out of rk4
            for(int i=0;i<n;i++){ xt[i] = xout[i];}
            c++;
        }
    }
    bifurcacion.close();
//---End of limit calculation of bifurcation

    //gnuplot commands to style the diagram
    gnufile<<"set terminal cairolatex png font ',14' standalone"<<endl;
    gnufile<<"set output 'bify.tex'"<<endl;
    gnufile<<"set xlabel "<<param_name<<endl;
    gnufile<<"set ylabel \"limit values\""<<endl;
    gnufile<<"plot '"+nombre+"' using 2:6 w p ps "<<ps<<" pt 7 lc 8 notitle";
    gnufile<<"\nunset output"<<endl;
    gnufile.close();
    string cmd="gnuplot "+gnuname;
    auto stop=chrono::steady_clock::now();
    auto times=chrono::duration_cast<chrono::seconds>(stop-start).count();
    auto timem=chrono::duration_cast<chrono::minutes>(stop-start).count();
	cout<<"Tiempo de ejcución algoritmo: ";
    cout<<" "<<times<<"Seg = "<<timem<<"Min"<<endl;
    start=chrono::steady_clock::now();
    system(cmd.c_str());
    stop=chrono::steady_clock::now();
    times=chrono::duration_cast<chrono::seconds>(stop-start).count();
    timem=chrono::duration_cast<chrono::minutes>(stop-start).count();
	cout<<"Tiempo de ejcución gnuplot: ";
    cout<<" "<<times<<"Seg = "<<timem<<"Min"<<endl;
	string filename="bify";
    return "pdflatex "+filename+".tex";
}

string get_bifurcacion(string filename){
    ifstream datos(filename.c_str());
    string sistema,param_name;
    int n,np,index;
    double t,dt,lim,t1,finp,dp,ps;
    getline(datos,sistema);
    datos>>n;
    datos>>np;
    datos>>index;
    datos>>finp;
    datos>>dp;
    datos>>t;
    datos>>dt;
    datos>>t1;
    datos>>lim;
    double x[n],xout[n],P[np];
    for(int i=0;i<n;i++){
        datos>>x[i];
    }

    for(int i=0;i<np;i++){
        datos>>P[i];
    }
    datos>>ps;
    datos>>param_name;
    datos.close();
    return diagrama_bifurcacion(n,x,P,np,index,finp,dp,t,dt,t1,lim,sistema,param_name,ps,menu);

}

string get_retrato_limite(string filename){
    ifstream datos(filename.c_str());
    string sistema,param_name;
    int n,np,index,delay;
    double t,dt,lim,t1,finp,dp,ps;
    getline(datos,sistema);
    datos>>n;
    datos>>np;
    datos>>index;
    datos>>finp;
    datos>>dp;
    datos>>t;
    datos>>dt;
    datos>>t1;
    datos>>lim;
    double x[n],xout[n],P[np];
    for(int i=0;i<n;i++){
        datos>>x[i];
    }

    for(int i=0;i<np;i++){
        datos>>P[i];
    }
    datos>>ps;
    datos>>param_name;
	datos>>delay;
    datos.close();
    return make_retrato_limite(n,x,P,np,index,finp,dp,t,dt,t1,lim,sistema,param_name,ps,delay,menu);
}


string phase_portrait(int n,double t,double dt,double lim,double I[][2],
	double dx,string sistema,double params[], int p,
	void (*menu)(string opcion,double t,double x[],double f[],double P[])){

	int color=1;
	ofstream file,comando;
    double minx,maxx,miny,maxy;
	string name,dir,cmd;
    dir="Portraits/"+sistema;
	cmd="mkdir "+dir;
	system(cmd.c_str());
	double x[n],xout[n],f[n],taux,N[n];
    string gnuname=dir+"/comando.gnu";
	comando.open(gnuname.c_str());
    comando<<"set terminal epslatex font ',14' standalone"<<endl;
    comando<<"set output 'retrato.tex'"<<endl;
    comando<<"set xlabel \"$x$\""<<endl;
    comando<<"set ylabel \"$u$\""<<endl;
    comando<<"set xrange["<<I[0][0]<<":"<<I[0][1]<<"]"<<endl;
	comando<<"set yrange["<<I[1][0]<<":"<<I[1][1]<<"]"<<endl;
	comando<<"plot ";
    name="retrato_"+sistema;
    file.open(name.c_str());
    double hs=abs((I[0][0]-I[0][1])/90);
	for(double l=I[0][0];l<=I[0][1];l+=dx){
			//color++;
		for(double k=I[1][0];k<=I[1][1];k+=dx){
			taux=t; x[0]=l; x[1]=k; int z=0;
			for(;taux<lim;taux+=dt){
				rk4(n,x,dt,xout,taux,params,sistema,menu);
                if(check4nan(xout,n)){break;}
				f[0]=xout[0]-x[0];
				f[1]=xout[1]-x[1];
				file<<x[0]<<" "<<x[1]<<" "<<f[0]<<" "<<f[1]<<endl;
				for(int i=0;i<n;i++){ x[i]=xout[i];}
                z++;
				}
                file<<"\n\n";
//			    comando<<"'"<<name<<"'"<<" w vec head filled size "<<hs<<",10 linecolor black notitle,";
			}
		}
    file.close();
    comando<<"'"<<name<<"'"<<" w vec head filled size "<<hs<<",10 lc 8 notitle\n";
    comando<<"unset output\n";
    comando.close();
    string cmdo="gnuplot "+gnuname;
    system(cmdo.c_str());
    return "latex retrato.tex && dvips retrato.dvi";
}

string Retrato_fase(string filename){
    ifstream datos(filename.c_str());
    string sistema;
    int n,p;
    double t,dx,dt,lim;
    getline(datos,sistema);
    datos>>n;
    datos>>p;
    datos>>t;
    datos>>dt;
    datos>>lim;
    datos>>dx;
    double P[p],I[n][2];
    for(int i=0;i<p;i++){
        datos>>P[i];
    }
    for(int i=0;i<n;i++){
        datos>>I[i][0];
        datos>>I[i][1];
    }
    datos.close();
    return phase_portrait(n,t,dt,lim,I,dx,sistema,P,p,menu);
}

/*Esta función lee un archivo 'filename' que contiene los siguentes datos en orden:
sistema es el nombre del sistema de ecuaciones a resolver.
n dimensión del sistema
p numero de parámetros
t es el tiempo de segundos que corre
dt es el paso del tiempo


*/



string get_solucion(string filename){
    ifstream datos(filename.c_str());
    string sistema;
    int n,p;
    double t,dt,l1,lim;
    getline(datos,sistema);
    datos>>n;
    datos>>p;
    datos>>t;
    datos>>dt;
    datos>>l1;
    datos>>lim;
    double x[n],xout[n],P[p];
    for(int i=0;i<n;i++){
        datos>>x[i];
    }

    for(int i=0;i<p;i++){
        datos>>P[i];
    }
    datos.close();

    cout<<"\nDimension="<<n<<"\nCondiciones iniciales x[]="<<print_array(n,x)<<endl;
    cout<<"Parametros P[]="<<print_array(p,P)<<endl;
    cout<<"t="<<t<<"\ndt="<<dt<<"\nl1="<<l1<<"\nlim="<<lim<<"\nsistema="<<sistema<<"\n\n";

    return make_solution(n,x,xout,P,t,dt,l1,lim,sistema,menu);

}


void resuelve_cubica(double A[],double x[]){
    double a=A[1]/A[0]; double b=A[2]/A[0]; double c=A[3]/A[0];
    double p=(3*b-pow(a,2))/3; double q=(2*pow(a,3)-9*a*b+27*c)/27;
    double dt=pow(q,2)/4+pow(p,3)/27;
    if(dt==0){
        if(p==q==0){ 
            x[0]=-a/3;
            x[1]=x[0];
            x[2]=x[0];
        }
        if(p*q!=0){
            x[0]=(-3.0/2.0)*q/p-a/3;
            x[1]=x[0];
            x[2]=(-4.0/9.0)*pow(p,2)/q -a/3;
        }
    }
    if(dt>0){
        double e=1.0/3.0;
        x[0]=pow((-q/2+sqrt(dt)),e)+pow((-q/2-sqrt(dt)),e)-a/3;
        x[1]=x[0];
        x[2]=x[0];
    }
    if(dt<0){
        double pi=acos(-1);
        double th=acos(-q/(2*sqrt(pow(-p/3,3))));
        for(int i=0;i<3;i++){
            x[i]=2*sqrt(-p/3)*cos((th+2*i*pi)/3)-a/3;
        }
    }
    sort(x,x+3);
}


string make_synch(int n,double start,double elim[],double x[],double xout[],
    double params[],double t,double dt, double lim,string sistema,double definicion,
    void (*menu)(string opcion,double t, double x[],double f[],double P[])){
    string nombre="Solutions/synch_"+sistema+".txt";
    string nombre2="Solutions/"+sistema+".gnu";
    ofstream solucion,comando;
    int i;
    double f[n];
    solucion.open(nombre.c_str());
    double c=0;
    //IMPRIMIR CONDICIONES INICIALES
    solucion<<t<<" ";
    for(i=0;i<n;i++){
        solucion<<x[i]<<" ";
    }
    //EMPIEZA RUNGE KUTTA
    for(;t<=lim;t+=dt){
        if(c>=definicion){
        //imprimir tiempo
        solucion<<t<<" ";
        //imprimir variables en el tiempo
        for(i=0;i<n;i++){
            solucion<<x[i]<<" ";
            }
        //diferencia de las variables e1 y e2
        solucion<<abs(x[0]-x[2])<<" "<<abs(x[1]-x[3])<<" "<<log10(t)<<endl;
        c=0;
        }
        rk4(n,x,dt,xout,t,params,sistema,menu);
        if(check4nan(xout,n)){break;}
        for(int i=0;i<n;i++){ x[i] = xout[i];}
        c+=dt;
        }
    solucion.close();
    comando.open(nombre2.c_str());
    comando<<"set terminal epslatex font ',14' standalone"<<endl;
    comando<<"set output 'xu.tex'"<<endl;
    comando<<"set xlabel \"$x$\""<<endl;
    comando<<"set ylabel \"$u$\""<<endl;
    comando<<"plot '"<<nombre<<"' skip "<<ceil(start/definicion)<<" u 2:3 w l lc 8 notitle"<<endl;
    comando<<"unset output"<<endl;
    comando<<"set output 'yv.tex'"<<endl;
    comando<<"set xlabel \"$y$\""<<endl;
    comando<<"set ylabel \"$v$\""<<endl;
    comando<<"plot '"<<nombre<<"' skip "<<ceil(start/definicion)<<" u 4:5 w l lc 8 notitle"<<endl;
    comando<<"unset output"<<endl;
    comando<<"set output 'xy.tex'"<<endl;
    comando<<"set xlabel \"$x$\""<<endl;
    comando<<"set ylabel \"$y$\""<<endl;
    comando<<"plot '"<<nombre<<"' skip "<<ceil(start/definicion)<<" u 2:4 w l lc 8 notitle"<<endl;
    comando<<"unset output"<<endl;
    comando<<"set output 'uv.tex'"<<endl;
    comando<<"set xlabel \"$u$\""<<endl;
    comando<<"set ylabel \"$v$\""<<endl;
    comando<<"plot '"<<nombre<<"' skip "<<ceil(start/definicion)<<" u 3:5 w l lc 8 notitle"<<endl;
    comando<<"unset output"<<endl;
    comando<<"set output 'e1t.tex'"<<endl;
    comando<<"set xrange["<<start<<":"<<elim[0]<<"]"<<endl;
    comando<<"set xlabel \"$t$\""<<endl;
    comando<<"set ylabel \"$|x-y|$\""<<endl;
    comando<<"plot '"<<nombre<<"' u 1:6 w l lc 8 notitle"<<endl;
    comando<<"unset output"<<endl;
    comando<<"set output 'e2t.tex'"<<endl;
    comando<<"set xrange["<<start<<":"<<elim[1]<<"]"<<endl;
    comando<<"set xlabel \"$t$\""<<endl;
    comando<<"set ylabel \"$|u-v|$\""<<endl;
    comando<<"plot '"<<nombre<<"' u 1:7 w l lc 8 notitle"<<endl;
    comando<<"unset output"<<endl;
    if(start==0){start=1;}
    comando<<"set output 'e1logt.tex'"<<endl;
    comando<<"set xrange ["<<log10(start)<<":"<<log10(lim)<<"]"<<endl;
    comando<<"set xlabel \"$\\log_{10}(t)$\""<<endl;
    comando<<"set ylabel \"$|x-y|$\""<<endl;
    comando<<"plot '"<<nombre<<"' u 8:6 w l lc 8 notitle"<<endl;
    comando<<"unset output"<<endl;
    comando<<"set output 'e2logt.tex'"<<endl;
    comando<<"set xrange ["<<log10(start)<<":"<<log10(lim)<<"]"<<endl;
    comando<<"set xlabel \"$\\log_{10}(t)$\""<<endl;
    comando<<"set ylabel \"$|u-v|$\""<<endl;
    comando<<"plot '"<<nombre<<"' u 8:7 w l lc 8 notitle"<<endl;
    comando<<"unset output"<<endl;
    comando.close();
    string cmd="gnuplot "+nombre2;
    system(cmd.c_str());
    string r="latex xu.tex && latex yv.tex && latex xy.tex && latex uv.tex && latex e1t.tex && latex e2t.tex && latex e1logt.tex && latex e2logt.tex && dvips xu.dvi && dvips yv.dvi && dvips xy.dvi && dvips uv.dvi && dvips e1t.dvi && dvips e2t.dvi && dvips e1logt.dvi && dvips e2logt.dvi";
    return r;
    }
 


string get_synch(string filename){
    ifstream datos(filename.c_str());
    string sistema;
    int n,p;
    double t,dt,lim,start,elim[2],definicion;
    getline(datos,sistema);
    datos>>n;
    datos>>p;
    datos>>t;
    datos>>dt;
    datos>>lim;
    double x[n],xout[n],P[p];
    for(int i=0;i<n;i++){
        datos>>x[i];
    }
    for(int i=0;i<p;i++){
        datos>>P[i];
    }
    datos>>start;
    datos>>elim[0];
    datos>>elim[1];
    datos>>definicion;
    if(start >= elim[0]){ elim[0]=start+elim[0];}
    if(start >= elim[1]){ elim[1]=start+elim[1];}
    datos.close();
    return make_synch(n,start,elim,x,xout,P,t,dt,lim,sistema,definicion,menu);

}

string bif_synch(int n, double x[], double P[],int np,int index,double finp,double dp,
    double t,double dt,double t1,double lim, string sistema, string param_name,double ps,double definicion,
    void (*menu)(string opcion,double t, double x[],double f[],double P[])){
    auto start=chrono::steady_clock::now();
    string nombre="Bifurcaciones/"+sistema+"synch";
    string gnuname=nombre+".gnu";
    nombre+=".txt";
    ofstream bifurcacion,gnufile;
    int i;
    double f[n], xout[n];
    bifurcacion.open(nombre.c_str());
    gnufile.open(gnuname.c_str());
    double p;
    for(p=P[index];p<=finp;p+=dp){
        double P2[np],tax;
        for(int i=0;i<np;i++){ P2[i]=P[i];}
        P2[index]=p;
        double c=0;
        for(tax=t;tax<=lim;tax+=dt){
            if(tax>=t1 && c>=definicion){
//				cout<<c<<endl;
                bifurcacion<<tax<<" "<<p<<" "<<abs(x[0]-x[2])<<" "<<abs(x[1]-x[3])<<endl;
                c=0;
            }
            rk4(n,x,dt,xout,tax,P2,sistema,menu);
            if(check4nan(xout,n)){break;}
            for(int i=0;i<n;i++){ x[i] = xout[i];}
            c+=dt;
        }
    }
    gnufile<<"set terminal cairolatex pdf font ',14' standalone"<<endl;
    gnufile<<"set output 'e1bify.tex'"<<endl;
    gnufile<<"set xlabel "<<param_name<<endl;
    gnufile<<"set ylabel \"$|x-y|$\""<<endl;
    gnufile<<"plot '"+nombre+"' using 2:3 w p ps "<<ps<<" pt 7 lc 8 notitle";
    gnufile<<"\nunset output"<<endl;
    gnufile<<"set output 'e2bify.tex'"<<endl;
    gnufile<<"set xlabel "<<param_name<<endl;
    gnufile<<"set ylabel \"$|u-v|$\""<<endl;
    gnufile<<"plot '"+nombre+"' using 2:4 w p ps "<<ps<<" pt 7 lc 8 notitle";
    gnufile<<"\nunset output"<<endl;
    bifurcacion.close();
    gnufile.close();
    string cmd="gnuplot "+gnuname;
    auto stop=chrono::steady_clock::now();
    auto times=chrono::duration_cast<chrono::seconds>(stop-start).count();
    auto timem=chrono::duration_cast<chrono::minutes>(stop-start).count();
    cout<<"tiempo de exec en segs: "<<times<<endl;
    cout<<"tiempo de exec en mins: "<<timem<<endl;
    system(cmd.c_str());
//    return nombre;
    return "pdflatex e1bify.tex && pdflatex e2bify.tex && pdf2ps e1bify.pdf && pdf2ps e2bify.pdf";
//    return "gnuplot -persist "+gnuname;
}

string get_bif_synch(string filename){
    ifstream datos(filename.c_str());
    string sistema,param_name;
    int n,np,index;
    double t,dt,lim,t1,finp,dp,ps,definicion;
    getline(datos,sistema);
    datos>>n;
    datos>>np;
    datos>>index;
    datos>>finp;
    datos>>dp;
    datos>>t;
    datos>>dt;
    datos>>t1;
    datos>>lim;
    double x[n],xout[n],P[np];
    for(int i=0;i<n;i++){
        datos>>x[i];
    }

    for(int i=0;i<np;i++){
        datos>>P[i];
    }
    datos>>ps;
    datos>>param_name;
    datos>>definicion;
    datos.close();
    return bif_synch(n,x,P,np,index,finp,dp,t,dt,t1,lim,sistema,param_name,ps,definicion,menu);

}

void puntos_fijos(double inicio,double fin,double P[]){}
