/*******************************************************************************
* Time Functions Library (implementation)
*
* Description:
*     A library to handle various time-related functions and operations.
*
* Author:
*     Renato Mancuso <rmancuso@bu.edu>
*
* Affiliation:
*     Boston University
*
* Creation Date:
*     September 10, 2023
*
* Last Update:
*     September 9, 2024
*
* Notes:
*     Ensure to link against the necessary dependencies when compiling and
*     using this library. Modifications or improvements are welcome. Please
*     refer to the accompanying documentation for detailed usage instructions.
*
*******************************************************************************/

#include "timelib.h"

/* Return the number of clock cycles elapsed when waiting for
 * wait_time seconds using sleeping functions */
uint64_t get_elapsed_sleep(long sec, long nsec)
{
	/* IMPLEMENT ME! */

	uint64_t start_clock;
	uint64_t end_clock;

	struct timespec ts;
	ts.tv_sec = sec;
	ts.tv_nsec = nsec;

	get_clocks(start_clock);

	nanosleep(&ts, NULL);

	get_clocks(end_clock);

	return (end_clock - start_clock);
	
}

/* Return the number of clock cycles elapsed when waiting for
 * wait_time seconds using busy-waiting functions */
uint64_t get_elapsed_busywait(long sec, long nsec)
{

	uint64_t start_clock;
	uint64_t end_clock;

	struct timespec ts, current_timestamp;
	ts.tv_sec = sec;
	ts.tv_nsec = nsec;
	
	struct timespec min_time;
	clock_gettime(CLOCK_MONOTONIC, &min_time);
	timespec_add(&min_time, &ts);


	struct timespec begin_timestamp;
	clock_gettime(CLOCK_MONOTONIC, &begin_timestamp);

	get_clocks(start_clock);

	while(1){
	
		clock_gettime(CLOCK_MONOTONIC, &current_timestamp);
		if (timespec_cmp(&current_timestamp, &min_time) == 1){
			break; 
		}

	}

	get_clocks(end_clock);

	return (end_clock - start_clock);
}

/* Utility function to add two timespec structures together. The input
 * parameter a is updated with the result of the sum. */
void timespec_add (struct timespec * a, struct timespec * b)
{
	/* Try to add up the nsec and see if we spill over into the
	 * seconds */
	time_t addl_seconds = b->tv_sec;
	a->tv_nsec += b->tv_nsec;
	if (a->tv_nsec > NANO_IN_SEC) {
		addl_seconds += a->tv_nsec / NANO_IN_SEC;
		a->tv_nsec = a->tv_nsec % NANO_IN_SEC;
	}
	a->tv_sec += addl_seconds;
}

/* Utility function to compare two timespec structures. It returns 1
 * if a is in the future compared to b; -1 if b is in the future
 * compared to a; 0 if they are identical. */
int timespec_cmp(struct timespec *a, struct timespec *b)
{
	if(a->tv_sec == b->tv_sec && a->tv_nsec == b->tv_nsec) {
		return 0;
	} else if((a->tv_sec > b->tv_sec) ||
		  (a->tv_sec == b->tv_sec && a->tv_nsec > b->tv_nsec)) {
		return 1;
	} else {
		return -1;
	}
}

/* Busywait for the amount of time described via the delay
 * parameter */
uint64_t busywait_timespec(struct timespec delay)
{
	/* IMPLEMENT ME! (Optional but useful) */
}
