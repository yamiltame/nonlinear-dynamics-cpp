#include "../Headers/tools.hpp"
#include "../Headers/sistemas.hpp"
using namespace std;

int main(int argc,char *argv[]){
	string archivo=argv[1];
	system(get_bifurcacion(archivo).c_str());
	if(system("open bify.pdf")!=0){
		cout<<"Whoopsie... usando xdg-open"<<endl;
		if(system("xdg-open bify.pdf")!=0){
			cout<<"La imagen es el archivo 'bify.pdf'"<<endl;
		}
	}
	}
