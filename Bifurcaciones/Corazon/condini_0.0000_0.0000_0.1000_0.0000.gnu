set terminal cairolatex png font ',14' standalone
set output 'bify.tex'
set xlabel "$H$"
set ylabel "$x_4(t)$"
plot 'Bifurcaciones/Corazon/condini_0.0000_0.0000_0.1000_0.0000.txt' using 2:6 w p ps 0.05 pt 7 lc 8 notitle
unset output
