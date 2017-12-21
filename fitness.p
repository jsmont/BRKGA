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
FILES = system("ls -1 data/*.dat")
LABELS = system("ls -1 data/*.dat | sed -e 's:data/::' -e 's:.dat::'")
plot for [i=1:words(FILES)] word(FILES,i) using 1:2 title word(LABELS,i)
