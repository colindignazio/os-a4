#include "types.h"
#include "user.h"
		
typedef enum{
	CPU = 0,
	SCPU = 1,
	IO = 2
} PROC_TYPE;

static const char CPU_NAME[] = "CPU";
static const char SCPU_NAME[] = "SCPU";
static const char IO_NAME[] = "I/O";

void cpuBoundProcess(){
	int i, j;

	for(i = 0; i < 100; i++){
		for(j = 0; j < 1000000; j++);
	}
}

void scpuBoundProcess(){
	int i, j;

	for(i = 0; i < 100; i++) {
		for(j = 0; j < 1000000; j++);
		yield();
	}

}

void ioBoundProcess(){
	int i;

	for(i = 0; i < 100; i++){
		sleep(1);
	}
}

PROC_TYPE getProcType(int pid){
	return (PROC_TYPE) pid % 3;
}

const char *getProcTypeName(int pid){
	switch(getProcType(pid)){
		case CPU: return CPU_NAME;
		case SCPU: return SCPU_NAME;
		case IO: return IO_NAME;
		default: return 0;
	}
}

void sanity(int n) {
	int retime, rutime, stime, i, pid, cpid;
	int proc_count = 0;
	int tSleepTime = 0;
	int tReadyTime = 0;
	int tTurnaroundTime = 0;

	for(i = 0; i < n; i++){
		pid = fork();

		if(pid == 0){
			cpid = getpid();
			switch(getProcType(cpid)){
				case CPU:
					cpuBoundProcess();
					break;
				case SCPU:
					scpuBoundProcess();
					break;
				case IO:
					ioBoundProcess();
					break;
				default:
					exit();
			}
			exit();
		}
	}

	pid = wait2(&retime, &rutime, &stime);
	
	while(pid != -1){
		proc_count++;
		tReadyTime += retime;
		tSleepTime += stime;
		tTurnaroundTime += stime + retime + rutime;

		printf(1, "PID: %d\n", pid);
		printf(1, "TYPE: %s\n", getProcTypeName(pid));
		printf(1, "Ticks spent waiting: %d\n", retime);
		printf(1, "Ticks spent running: %d\n", rutime);
		printf(1, "Ticks spent waiting for I/O: %d\n\n", stime);
		pid = wait2(&retime, &rutime, &stime);
	}

	printf(1, "Average ticks spent sleeping: %d\n", tSleepTime/proc_count);
	printf(1, "Average ticks spent waiting: %d\n", tReadyTime/proc_count);
	printf(1, "Average ticks for turnaround: %d\n", tTurnaroundTime/proc_count);
}

int main(int argc, char *argv[]){
	int n;

	if(argc != 2)
		exit();

	n = atoi(argv[1]);

	if(n > 0)
		sanity(3 * n);

	exit();
}