#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <sched.h>
#include <errno.h>

#define __NR_isolate_cpu 451

long isolate_cpu(int pid){
	return syscall(__NR_isolate_cpu);
}

/************************************************************
Do not modify this file other than 
the part where you are supposed to add your code
************************************************************/

long long func() {
	long long ans = 0;
	for(int i = 0; i < 100000; i++) {
		for(int j = 0; j < 1000000; j++) {
			int res = i * j;
			ans = ans + res;
		}
	}
	return ans;
}

double measureTime() {
	time_t start,end;
 	double cpu_time_used;
 	start = time(NULL);
 	func();
	end = time(NULL);
	cpu_time_used = (double)(end - start);
 	return cpu_time_used;
}

int main(int argc, char *argv[])
{

	//Invoke your system call here, to isolate CPU 0
	//YOUR CODE START HERE 
	
	//long ret;
	
	
	//YOUR CODE END HERE
 
	int c1pid = fork();
	int c2pid;
	double cpu_time_used;
	if(!c1pid) {
		// Assign this process to core 0 and change priority to highest priority
		//YOUR CODE START HERE

		if(isolate_cpu(c1pid)>=0)
		{
			printk("Call executed successully\n");
		}
		else{
			printk("Call failed!\n");
			exit(1);
		}

		//YOUR CODE END HERE
 
		cpu_time_used = measureTime();
		printf("Process 1 used %lf seconds\n", cpu_time_used);
	}
	else {
		c2pid = fork();
		if(!c2pid) {
			// Assign this process to core 0 and change priority to lowest priority
			// YOUR CODE START HERE 
		if(isolate_cpu(c1pid)>=0)
		{
			printk("Call executed successully\n");
		}
		else{
			printk("Call failed!\n");
			exit(1);
		}

			//YOUR CODE END HERE

			cpu_time_used = measureTime();
			printf("Process 2 used %lf seconds\n", cpu_time_used);
		}
	}

	return 0;
}
