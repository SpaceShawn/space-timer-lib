#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

#define WINDOW_TIMEOUT 			5
#define RESEND_TIMEOUT 			2

// make sure to compile with -lrt

// Create a new interval timer
// Returns the ID of the new timer
//
// We can choose to use a signal handler when the timer expires in the future
// We would register to the signal handler by passing a function pointer to this function
timer_t timer_get();

// Arms or disarms the timer specified by timerid
// The timer will expire at the given timeout value
// Entering a timeout of 0 will disarm the timer
// The function resets the time when it is called to the timeout value
void timer_start(timer_t * timerid, uint32_t timeout);

// Returns true if the timer has expired
bool timer_complete(timer_t * timer);

int main(int argc, char* argv[]) {

	timer_t resend_timer = timer_get();
	timer_t window_timer = timer_get();
	timer_start(&resend_timer, RESEND_TIMEOUT);
	timer_start(&window_timer, WINDOW_TIMEOUT);

	while(1)
	{
		getchar();
		if(timer_complete(&resend_timer))
			printf("Resend timer complete\n");

		if(timer_complete(&window_timer))
			printf("Window timer complete\n");

	}


	return EXIT_SUCCESS;
}

void timer_start(timer_t * timer, uint32_t timeout)
{
	printf("timer starting\n");
    struct itimerspec it_val;
    it_val.it_value.tv_sec = timeout;
    it_val.it_value.tv_nsec = 0;

    // timer expires once
    it_val.it_interval.tv_sec = 0;
    it_val.it_interval.tv_nsec = 0;

	 if (timer_settime(*timer, 0, &it_val, NULL) == -1) {
			perror("Could not start timer\n");
			exit(EXIT_FAILURE);
	 }
}

timer_t timer_get()
{
	timer_t timer;
    struct sigevent sev;

    /*
    struct sigaction sa;
    // register to signal handler
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIG, &sa, NULL) == -1)
        errExit("Failed to register to signal handler");
    */

	// create timer
    sev.sigev_notify = SIGEV_NONE;
    sev.sigev_signo = SIGCONT;
    sev.sigev_value.sival_ptr = &timer;

	 if (timer_create(CLOCK_MONOTONIC, &sev, &timer) == -1) {
		perror("Could not create timer\n");
		exit(EXIT_FAILURE);
	 }

	 return timer;

}

bool timer_complete(timer_t * timer)
{
	struct itimerspec curr_val;
	if(timer_gettime(*timer, &curr_val) == -1) {
		perror("Could not create timer\n");
		exit(EXIT_FAILURE);
	}

	if(curr_val.it_value.tv_sec == 0)
		return true;
	else
		return false;
}



