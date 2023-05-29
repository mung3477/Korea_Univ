#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sched.h>
#include <errno.h>
#include <signal.h>
#define ROW (100)
#define COL ROW

typedef struct proc_info {
	int			proc_num;
	int			calc_count;
	int			calc_total;
	int			total_epoch_dur;	// millisecond
} Proc_info;

struct sched_attr {
	uint32_t	size;
	uint32_t	sched_policy;
	uint64_t	sched_flags;
	int32_t		sched_nice;
	uint32_t	sched_priority;
	uint64_t	sched_runtime;
	uint64_t	sched_deadline;
	uint64_t	sched_period;
};

int			forked_procs;
Proc_info	info;
int			epoch_time;
int			pid = -1;
int			status;

void init_info(Proc_info *info) {
	info->proc_num = -1;
	info->calc_count = 0;
	info->calc_total = 0;
	info->total_epoch_dur = 0;
}

void calc(void) {
	int matrixA[ROW][COL];
	int matrixB[ROW][COL];
	int matrixC[ROW][COL];
	int i, j, k;

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			for (k = 0; k < COL; k++) {
				matrixC[i][j] += matrixA[i][j] * matrixB[i][j];
			}
		}
	}
}

void print_msg(int proc, int count, int time, int is_total) {
	printf("PROCESS #%d  ", proc);
	if (is_total)
		printf("total");
	printf("Count = %d  Time = %d\n", count, time);
}

int	time_diff(struct timespec* begin, struct timespec* end) {
	if (!begin)
		return (end->tv_sec * 1000 + end->tv_nsec / 1000000);
	return (end->tv_sec - begin->tv_sec) * 1000 + (end->tv_nsec - begin->tv_nsec) / 1000000;
}

void end_process(int signo) {
	if (pid == 0) {
		info.total_epoch_dur += epoch_time;
		print_msg(info.proc_num, info.calc_total, info.total_epoch_dur, 1);
		exit(1);
	}
	else {
		for (int i = 1; i <= forked_procs; i++)
			wait(&status);
	}
}

int main(int argc, char* argv[]) {
	int					total_procs = atoi(argv[1]);
	int					exec_time = atoi(argv[2]) * 1000;
	struct timespec		init, clk_proc, clk_glb;
	struct sched_attr	attr;

	signal(SIGINT, (void *)end_process);
	pid = getpid();
	init_info(&info);
	clock_gettime(CLOCK_MONOTONIC, &init);
	memset(&attr, 0, sizeof(attr)); // 구조체 초기화
	attr.size = sizeof(attr);
	attr.sched_policy = SCHED_RR;; // Round robin으로 설정
	attr.sched_priority = 10;;  // 현재 프로세스 및 이후 fork되는 프로세스의 priority를 10으로 설정

	// set scheduling policy
	if (syscall(SYS_sched_setattr, getpid(), &attr, 0) == -1) {
		printf("Error while setting scheduling policy: %d\n", errno);
		return (1);
	}

	// create {procs_num} processes
	while (info.proc_num < total_procs - 1) {
		printf("Creating Process: #%d\n", ++info.proc_num);
		pid = fork();
		if (pid == -1) {
			printf("Error while running fork\n");
			return (1);
		}
		if (pid == 0)
			break;
		forked_procs += 1;
	}

	if (pid == 0) {
		// record time duration
		while (1) {
			calc();
			info.calc_total += 1;
			clock_gettime(CLOCK_MONOTONIC, &clk_glb);
			clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &clk_proc);
			epoch_time = time_diff(0, &clk_proc) - info.total_epoch_dur;

			// record every 100ms
			if (epoch_time >= 100) {
				info.total_epoch_dur += epoch_time;
				print_msg(info.proc_num, info.calc_total, epoch_time, 0);
				epoch_time = 0;
			}

			// if the program is executed more than given execution time, stops running.
			if (time_diff(&init, &clk_glb) > exec_time)
				end_process(SIGINT);
		}
	}
	else
		end_process(SIGINT);
	return (0);
}
