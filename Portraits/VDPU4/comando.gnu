set terminal epslatex font ',14' standalone
set output 'retrato.tex'
set xlabel "$x$"
set xlabel "$x$"
set ylabel "$u$"
set xrange[-2:2]
set yrange[-1:1]
plot 'retrato_VDPU4' w vec head filled size 0.0444444,10 lc 8 notitle
unset output
