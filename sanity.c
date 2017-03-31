#include "types.h"
#include "user.h"

void cpuBoundProcess() {
	int i, j;

	for(i = 0; i < 100; i++)
		for(j = 0; j < 1000000; j++);
}

void scpuBoundProcess() {
	int i, j;

	for(i = 0; i < 100; i++) {
		for(j = 0; j < 1000000; j++);
		//yield();
	}

}

void ioBoundProcess() {
	int i;

	for(i = 0; i < 100; i++) {
		sleep(1);
	}
}

void sanity(int n) {
	int retime, rutime, stime, i, pid, cpid;

	for(i = 0; i < n; i++) {
		pid = fork();

		if(pid == 0) {
			cpid = getpid();
			if(cpid % 3 == 0)
				cpuBoundProcess();
			else if(cpid % 3 == 1)
				scpuBoundProcess();
			else if(cpid % 3 == 2)
				ioBoundProcess();
			exit();
		}
	}

	//NOT FULLY WORKING YET

	do {
		pid = wait2(&retime, &rutime, &stime);
		printf(1, "RUNNABLE TIME: %d\n", retime);
		printf(1, "RUNNING TIME: %d\n", rutime);
		printf(1, "SLEEPING TIME: %d\n", stime);
	} while(pid != -1);
}

int main(int argc, char *argv[]) {
	int n;

	if(argc != 2)
		exit();

	n = atoi(argv[1]);

	if(n > 0)
		sanity(3 * n);

	exit();
}