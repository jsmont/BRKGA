

seq -s "; " 0 250 > iterations.csv
seq -s "; " 0 250 > time.csv

:<<'END'
#BASE PER ITERATION
for instance in instances/good/*.dat
do

    for i in `seq 1 5`
    do
        ./nurses i 500 p 150 e $((150/4)) n $((150/20*9)) < $instance
    done

done

mv iterations.csv stats/
#PER POPULATION 


for population in `seq 50 50 500`
do
    for i in `seq 1 5`
    do
        ./nurses i 200 p $population e $(($population/4)) n $(($population/20*9)) < $instance
    done

    mv iterations.csv "stats/$(echo $population)_population.csv"
done
#PER ELITE
for elite in `seq 1 2 10`
do
    for i in `seq 1 5`
    do
        ./nurses i 200 p 150 e $((150*$elite/20)) n $((150/20*9*3/4)) < $instance
    done

    mv iterations.csv "stats/$(echo $elite)_elite.csv"
done
END

instance="Diya.dat"
#PER NORMIES
for normies in `seq 2 2 12`
do
    for i in `seq 1 5`
    do
        ./nurses i 200 p 150 e $((150/4)) n $(($normies/20*150*3/4)) < $instance
    done

    mv iterations.csv "stats/$(echo $normies)_normies.csv"
done
