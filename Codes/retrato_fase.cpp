#include "../Headers/tools.hpp"
#include "../Headers/sistemas.hpp"
using namespace std;

int main(int argc,char *argv[]){
	string archivo=argv[1];
	system(Retrato_fase(archivo).c_str());
	if(system("open retrato.ps")!=0){
		cout<<"Whoopsie... usando xdg-open"<<endl;
		if(system("xdg-open retrato.ps")!=0){
			cout<<"La imagen es el archivo 'retrato.ps'"<<endl;
		}
	}
}
