#include "../Headers/tools.hpp"
#include "../Headers/sistemas.hpp"
using namespace std;

int main(int argc,char *argv[]){
	string archivo=argv[1];
//	cout<<get_bif_synch(archivo)<<endl;
	system(get_bif_synch(archivo).c_str());
	if(system("open e1bify.ps && open e2bify.ps")!=0){
		cout<<"Whoopsie... usando xdg-open"<<endl;
		if(system("xdg-open e1bify.ps && xdg-open e2bify.ps")!=0){
			cout<<"La imagen es el archivo 'e1bify.ps' y 'e2bify.ps'"<<endl;
		}
	}
	}
