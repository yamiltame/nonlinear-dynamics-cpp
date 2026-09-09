set terminal epslatex font ',14' standalone
set output 'Solutions/VDPFU4/espaciofase.tex'
set xlabel "$x_1(t)$" font ',16'
 set ylabel "$x_2(t)$" font ',16'
 set tics font ',12'
plot 'Solutions/VDPFU4/condini_-2.000_0.8000.txt' using 2:3 w l lw 2 lc 8 notitle
 unset output
unset output
set output 'Solutions/VDPFU4/sol1.tex
set xlabel "$t$" font ',16'
 set ylabel "$x_1(t)$" font ',16'
 set tics font ',12'
plot 'Solutions/VDPFU4/condini_-2.000_0.8000.txt' u 1:2 w l lw 0.5 lc 8 notitle
unset output
set output 'Solutions/VDPFU4/sol2.tex
set xlabel "$t$" font ',16'
 set ylabel "$x_2(t)$" font ',16'
 set tics font ',12'
plot 'Solutions/VDPFU4/condini_-2.000_0.8000.txt' u 1:3 w l lw 0.5 lc 8 notitle
unset output
