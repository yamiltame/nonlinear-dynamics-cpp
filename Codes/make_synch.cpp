#include "../Headers/tools.hpp"
#include "../Headers/sistemas.hpp"
using namespace std;

int main(int argc,char *argv[]){
	string archivo=argv[1];
//	cout<<get_synch(archivo)<<endl;
	system(get_synch(archivo).c_str());
	if(system("open imagen.ps")!=0){
		cout<<"Whoopsie... usando xdg-open"<<endl;
		if(system("xdg-open imagen.ps")!=0){
			cout<<"La imagen es el archivo 'imagen.ps'"<<endl;
			}
		}
	}
