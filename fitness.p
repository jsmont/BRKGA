# Gnuplot script file for plotting the fitness function
set autoscale
unset log
unset label
set key noenhanced
set xtic auto
set ytic auto
#set yr [0:*]
set style data lines
set title "Fitness per iteration"
set xlabel "Iteration"
set ylabel "Fitness"
plot "stats.dat" using 1:2 title 'Fitness' 
