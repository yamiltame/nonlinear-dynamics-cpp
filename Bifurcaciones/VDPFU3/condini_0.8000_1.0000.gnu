set terminal cairolatex png font ',14' standalone
set output 'bify.tex'
set xlabel "$\\omega$"
set ylabel "limit values"
plot 'Bifurcaciones/VDPFU3/condini_0.8000_1.0000.txt' using 2:6 w p ps 0.01 pt 7 lc 8 notitle
unset output
