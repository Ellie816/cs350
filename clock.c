/*******************************************************************************
* CPU Clock Measurement Using RDTSC
*
* Description:
*     This C file provides functions to compute and measure the CPU clock using
*     the `rdtsc` instruction. The `rdtsc` instruction returns the Time Stamp
*     Counter, which can be used to measure CPU clock cycles.
*
* Author:
*     Renato Mancuso
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
*     Ensure that the platform supports the `rdtsc` instruction before using
*     these functions. Depending on the CPU architecture and power-saving
*     modes, the results might vary. Always refer to the CPU's official
*     documentation for accurate interpretations.
*
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "timelib.h"

int main (int argc, char ** argv)
{
	long sec = atol(argv[1]);
	long nsec = atol(argv[2]);
	char wait_method = argv[3][0];
	long clocks_elapsed;

	// Time in nsec
	double time = nsec + (sec * NANO_IN_SEC);

	double clock_speed;


	if (wait_method == 's'){
		clocks_elapsed = get_elapsed_sleep(sec, nsec);
		printf("\nWaitMethod: SLEEP");
	}

	else if (wait_method == 'b'){
		clocks_elapsed = get_elapsed_busywait(sec, nsec);
		printf("\nWaitMethod: BUSYWAIT");

	}
	else{
		printf("Invalid, choose s or b");
		return 0;
	}



	//Frequency in megahertz (clock cycles per nanosecond)
	clock_speed = ((double)clocks_elapsed/ (time/1000));


	printf("\nWaitTime: %ld %ld", sec, nsec);
	printf("\nClocksElapsed: %llu", clocks_elapsed);
	printf("\nClockSpeed: %lf \n", clock_speed);

	return EXIT_SUCCESS;
}







// hint: getop function?
// 
