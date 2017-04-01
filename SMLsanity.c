#include "types.h"
#include "user.h"


int
main(int argc, char *argv[])
{
  int i;
  int j = 0;
  int k;
  int loops = 20;
  int readyTime;
  int runTime;
  int sleepTime;
  int runTime1 = 0;
  int readyTime1 = 0;
  int sleepTime1 = 0;
  int runTime2 = 0;
  int readyTime2 = 0;
  int sleepTime2 = 0;
  int runTime3 = 0;
  int readyTime3 = 0;
  int sleepTime3 = 0;
  int pid;

  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
        for (i = 0; i < 3 * loops; i++) {
          j = i % 3;
          pid = fork();
          if (pid == 0) {
            j = (getpid() - 4) % 3;
            #ifdef SML
            switch(j) {
            case 0:
              set_prio(1);
              break;
            case 1:
              set_prio(2);
              break;
            case 2:
              set_prio(3);
              break;
            }
            #endif

            for (k = 0; k < 100; k++){
              for (j = 0; j < 1000000; j++){}
            }
	      exit();
            }

           continue;
	}

	for (i = 0; i < 3 * loops; i++) {
          pid = wait2(&readyTime, &runTime, &sleepTime);
          int res = (pid - 4) % 3;
            switch(res) {
              case 2: 
              printf(1, "Priority 3: Pid: %d, Running Time: %d, Ready Time: %d, Sleeping Time: %d, Total: %d\n", pid, runTime, readyTime, sleepTime, readyTime + runTime + sleepTime);
              runTime3 += runTime;
              readyTime3 += readyTime;
              sleepTime3 += sleepTime;
              break;
              case 1:
              printf(1, "Priority 2: Pid: %d, Running Time: %d, Ready Time: %d, Sleeping Time: %d, Total: %d\n", pid, runTime, readyTime, sleepTime, readyTime + runTime + sleepTime);
              runTime2 += runTime;
              readyTime2 += readyTime;
              sleepTime2 += sleepTime;
              break;
              case 0:
              printf(1, "Priority 1, Pid: %d, Running Time: %d, Ready Time: %d, Sleeping Time: %d, Total: %d\n", pid, runTime, readyTime, sleepTime, readyTime + runTime + sleepTime);
              runTime1 += runTime;
              readyTime1 += readyTime;
              sleepTime1 += sleepTime;
              break; 
            }
        }

              printf(1, "\nPriority 3:\nAverage run time: %d\nAverage ready time: %d\nAverage sleeping time: %d\nAverage total time: %d\n\n", runTime3/loops, readyTime3/loops, sleepTime3/loops, runTime3/loops + readyTime3/loops + sleepTime3/loops);
              printf(1, "Priority 2:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage total time: %d\n\n", runTime2/loops, readyTime2/loops, sleepTime2/loops, runTime2/loops + readyTime2/loops + sleepTime2/loops);
              printf(1, "Priority 1:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage total time: %d\n\n", runTime1/loops, readyTime1/loops, sleepTime1/loops, runTime1/loops + readyTime1/loops + sleepTime1/loops);
      
  exit();
}
