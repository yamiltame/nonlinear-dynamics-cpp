set terminal epslatex font ',14' standalone
set output 'retrato.tex'
set xlabel "$x$"
set xlabel "$x$"
set ylabel "$u$"
set xrange[-0.5:2]
set yrange[-1:1]
plot 'retrato_VDPFU3' w vec head filled size 0.0277778,10 lc 8 notitle
unset output
