
main: sistemas tools retrato solucion puntos bifurca synch biffysynch gif

sistemas:
	g++ -c Codes/sistemas.cpp -o Objects/sistemas.o

tools:
	g++ -c Codes/tools.cpp -o Objects/tools.o

retrato:
	g++ Codes/retrato_fase.cpp Objects/*.o -o retrato_fase

solucion:
	g++ Codes/make_solution.cpp Objects/*.o -o resuelve

puntos:
	g++ Codes/puntos_fijos.cpp Objects/*.o -o puntos_fijos

bifurca:
	g++ Codes/bifurcacion.cpp Objects/*.o -o bifurcacion

gif:
	g++ Codes/limit_prt.cpp Objects/*.o -o limit_prt

synch:
	g++ Codes/make_synch.cpp Objects/*.o -o sincroniza

biffysynch:
	g++ Codes/bifsynch.cpp Objects/*.o -o bifsynch
clean:
	rm *.tex; rm *.aux; rm *.log; rm *.ps; rm *.dvi; rm *.eps; rm *.pdf
