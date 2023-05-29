#!/usr/bin/bash
ITER=5
EXEC_TIME=300

cd /sys/fs/cgroup/cpuset
mkdir -p mycpu; cd mycpu
echo 0 > cpuset.cpus
echo 0 > cpuset.mems
echo $$ > tasks
cat tasks

sudo dmesg -C

cd ~/Desktop/KU/COSE341_OS/assignment2
touch 1ms_result.txt
touch 10ms_result.txt
touch 100ms_result.txt
gcc cpu.c

# 1ms timeslice
sudo echo 1 > /proc/sys/kernel/sched_rr_timeslice_ms
sudo ./a.out 2 $EXEC_TIME | sed -n '/total/p' > 1ms_output.txt
for (( c=2; c<=$ITER; c++))
do
	sudo ./a.out 2 $EXEC_TIME | sed -n '/total/p' >> 1ms_output.txt
done

# 1ms output data analysis
grep "#0  totalCount" 1ms_output.txt | awk -v ITER=$ITER '{sum_1 += $5} END { printf "PROCESS #0 average calculation on 1ms: %s\n", sum_1 /= ITER > "1ms_result.txt" }'
grep "#1  totalCount" 1ms_output.txt | awk -v ITER=$ITER '{sum_2 += $5} END { printf "PROCESS #1 average calculation on 1ms: %s\n", sum_2 /= ITER >> "1ms_result.txt" }'

awk '{total += $7} END { printf "Total calculation: %s\n", total >> "1ms_result.txt"}' 1ms_result.txt
sudo dmesg -s 32000000 | grep "CPUburst" | awk '{sum += $5} END { printf "Total CPUburst: %s\n", sum >> "1ms_result.txt"}'
cat 1ms_result.txt
grep "Total" 1ms_result.txt | awk '{ arr[NR] = $3 } END { print arr[1] / arr[2] }'

sudo dmesg -C

# 10ms timeslice
sudo echo 10 > /proc/sys/kernel/sched_rr_timeslice_ms
sudo ./a.out 2 $EXEC_TIME | sed -n '/total/p' > 10ms_output.txt
for (( c=2; c<=$ITER; c++))
do
	sudo ./a.out 2 $EXEC_TIME | sed -n '/total/p' >> 10ms_output.txt
done

# 10ms output data analysis
grep "#0  totalCount" 10ms_output.txt | awk -v ITER=$ITER '{sum_1 += $5} END { printf "PROCESS #0 average calculation on 10ms: %s\n", sum_1 /= ITER > "10ms_result.txt" }'
grep "#1  totalCount" 10ms_output.txt | awk -v ITER=$ITER '{sum_2 += $5} END { printf "PROCESS #1 average calculation on 10ms: %s\n", sum_2 /= ITER >> "10ms_result.txt" }'

awk '{total += $7} END { printf "Total calculation: %s\n", total >> "10ms_result.txt"}' 10ms_result.txt
sudo dmesg -s 32000000 | grep "CPUburst" | awk '{sum += $5} END { printf "Total CPUburst: %s\n", sum >> "10ms_result.txt"}'
cat 10ms_result.txt
grep "Total" 10ms_result.txt | awk '{ arr[NR] = $3 } END { print arr[1] / arr[2] }'

sudo dmesg -C

# 100ms timeslice
sudo echo 100 > /proc/sys/kernel/sched_rr_timeslice_ms
sudo ./a.out 2 $EXEC_TIME | sed -n '/total/p' > 100ms_output.txt
for (( c=2; c<=$ITER; c++))
do
	sudo ./a.out 2 $EXEC_TIME | sed -n '/total/p' >> 100ms_output.txt
done

# 100ms output data analysis
grep "#0  totalCount" 100ms_output.txt | awk -v ITER=$ITER '{sum_1 += $5} END { printf "PROCESS #0 average calculation on 100ms: %s\n", sum_1 /= ITER > "100ms_result.txt" }'
grep "#1  totalCount" 100ms_output.txt | awk -v ITER=$ITER '{sum_2 += $5} END { printf "PROCESS #1 average calculation on 100ms: %s\n", sum_2 /= ITER >> "100ms_result.txt" }'

awk '{total += $7} END { printf "Total calculation: %s\n", total >> "100ms_result.txt"}' 100ms_result.txt
sudo dmesg -s 32000000 | grep "CPUburst" | awk '{sum += $5} END { printf "Total CPUburst: %s\n", sum >> "100ms_result.txt"}'
cat 100ms_result.txt
grep "Total" 100ms_result.txt | awk '{ arr[NR] = $3 } END { print arr[1] / arr[2] }'

