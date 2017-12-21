#!/bin/sh
#SBATCH --job-name="Singularity"
#SBATCH --qos=bsc_cs
#SBATCH --time=00-01:00:00
#SBATCH --error=job.err
#SBATCH --output=job.out

#SBATCH -D /home/bsc15/bsc15556/MIRI/BRKGA

#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --tasks-per-node=1
#SBATCH --cpus-per-task=48

#SBATCH --exclusive

module load gcc/7.2.0

rm -rf set-0
rm -f TRACE.*

./nurses data/stats.dat < instances/Nurse0.dat
