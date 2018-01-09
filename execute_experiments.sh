
seq -s "; " 1 250 >> iterations.csv
seq -s "; " 1 250 >> time.csv

for instance in instances/*.dat
do

    for i in `seq 1 5`
    do
        ./nurses i 250 p 100 e 25 n 45 < $instance
    done

done
