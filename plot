#!/usr/bin/gnuplot
set terminal png size 1200,1200 enhanced font "Helvetica,20"
set output 'time.png'

set xlabel "n"
set ylabel "time"
set title "time vs n"
plot 'points.csv' u 1:2 title "time" w lp 
