#include "../Headers/tools.hpp"
#include "../Headers/sistemas.hpp"
using namespace std;

int main(int argc,char *argv[]){
	string archivo=argv[1];
	system(get_retrato_limite(archivo).c_str());
	}
