#!/usr/bin/gnuplot
set terminal png size 1200,1200 enhanced font "Helvetica,20"
set output 'r.png'

set xlabel "n^2/9"
set ylabel "Intersections for n"
set logscale xy
set yrange [0.01:]
set title "Number of intersections vs n^2/9"
plot 'report.csv' u 2:3 title "intersections" w lp 
