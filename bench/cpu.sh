#!/bin/bash

# Settings
CC=icc
PROJECT_DIR=/home/alexandrelucchesi/Development/miht/
PREFIXES_FILE=/home/alexandrelucchesi/Development/ip-datasets/ipv6/basic/as65000/prefixes.txt
ADDRS_FILE=/home/alexandrelucchesi/Development/ip-datasets/ipv6/randomAddrs.txt
ALGS_SERIAL=("miht-v6")
ALGS_PARALLEL=("miht-v6_par")
THREADS=(2 4 8 12 16 20 24 28 32)
#THREADS=(32)
SCHED_CHUNKSIZE="dynamic,1"
OUTPUT_FILE=bench/res-v6-exectime/cpu/lookup.csv # Benchmark output file.

cd $PROJECT_DIR
mkdir -p bench/res-v6-exectime/cpu/

# Clean old data files...
data_files=$(ls bench/res-v6-exectime/cpu)
if [ ${#data_files} -gt 0 ]; then
	rm -f bench/res-v6-exectime/cpu/*
fi


export OMP_SCHEDULE="$SCHED_CHUNKSIZE"

# Write headers to output file.
printf "Algorithm, # Threads, Execs...\n" >> $OUTPUT_FILE

# Write data to output file.
# Serial
for a in "${ALGS_SERIAL[@]}"
do
		printf "$a, 1: "
		printf "$a, 1" >> $OUTPUT_FILE

		for e in $(seq 1 3)  # Number of times to execute.
		do
			exec_time=$(./bin/$a -p $PREFIXES_FILE -r $ADDRS_FILE)

			printf "."
			printf ", $exec_time" >> $OUTPUT_FILE
		done
		printf "\n"
		printf "\n" >> $OUTPUT_FILE
done

# Parallel
for a in "${ALGS_PARALLEL[@]}"
do
	for t in "${THREADS[@]}"
	do
		export OMP_NUM_THREADS=$t
		printf "$a, $t: "
		printf "$a, $t" >> $OUTPUT_FILE

			for e in $(seq 1 3)  # Number of times to execute.
			do
				# Assure the OpenMP environment variables are set and non-empty.
				: ${OMP_SCHEDULE:?"Need to set OMP_SCHEDULE non-empty."}
				: ${OMP_NUM_THREADS:?"Need to set OMP_NUM_THREADS non-empty."}

				# Execute for input size 2^26 (67108864).
				exec_time=$(./bin/$a -p $PREFIXES_FILE -r $ADDRS_FILE)

				printf "."
				printf ", $exec_time" >> $OUTPUT_FILE
			done
		printf "\n"
		printf "\n" >> $OUTPUT_FILE
	done
done

