#include <stdio.h>
#include <time.h>

#include "FOVc.h"
#include "mtwist.h"

// VERSION 2 - uses cubic coordinates

void base();
void test1();
void test2();
void test3();
void test4();

double calcSeconds (clock_t start, clock_t finish);
clock_t startTest;
clock_t endTest;
clock_t timePassed;
double seconds;
const bool USE_TIMER = true;		// Calculates time to run each test case


const int NUM_ITERATIONS = 10000;// Number of times the test function is run
									   // when calculating LOS
const int X_RANGE = 1000;			// Horizontal map size, from 0 to X_RANGE
const int Y_RANGE = 100;			// Vertical map size, from 0 to Y_RANGE

int main()
{
	mt_seed32new(mt_seed());

	base();
	test1();
	test2();
	test3();
	test4();

	return 0;
}

void base()
{
	int base;
	int belongToUs = 0;

	if (USE_TIMER) startTest = clock();

	printf ("Starting base function.\n");

	for (belongToUs = 0; belongToUs < NUM_ITERATIONS * 4000; belongToUs++)
	{
		for (base = 0; base < 300000000; base++)
			belongToUs += base;
	}

	if (USE_TIMER) {
		endTest = clock();
		printf ("Base function completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
	} else printf ("Base function completed.\n\n");
}

void test1()
{
	int i;

	if (USE_TIMER) startTest = clock();

	printf ("TEST ONE: Line of Sight calculations between two iterated points\n");

	for (i = 0; i < NUM_ITERATIONS / 4000; i++)
		ScanLOSCalc(X_RANGE, Y_RANGE);

	if (USE_TIMER) {
		endTest = clock();
		printf ("Test one completed in %0.2f seconds.\n\n", calcSeconds (startTest, endTest));
	} else printf ("Test one completed.\n\n");
}

void test2()
{
	int i;

	if (USE_TIMER) startTest = clock();

	printf ("TEST TWO: Line of Sight calculations between two random points\n");

	for (i = 0; i < NUM_ITERATIONS / 4000; i++)
		RandLOSCalc(X_RANGE, Y_RANGE, X_RANGE * Y_RANGE);

	if (USE_TIMER) {
			endTest = clock();
			printf ("Test two completed in %0.2f seconds.\n\n", calcSeconds (startTest, endTest));
	} else printf ("Test two completed.\n\n");
}

void test3()
{
	int i;

	if (USE_TIMER) startTest = clock();

	printf ("TEST THREE: Only does distance and azimuth calculations between two random points.\n");

	for (i = 0; i < NUM_ITERATIONS / 12; i++)
		RandLOSCalcMin(X_RANGE, Y_RANGE, X_RANGE * Y_RANGE);

	if (USE_TIMER) {
			endTest = clock();
			printf ("Test three completed in %0.2f seconds.\n\n", calcSeconds (startTest, endTest));
	} else printf ("Test three completed.\n\n");
}

void test4()
{
	int i;

	if (USE_TIMER) startTest = clock();

	printf ("TEST FOUR: Prints random coordinates in even-r offset format.\n");

	for (i = 0; i < NUM_ITERATIONS / 4; i++)
		RandDisplayCoord(X_RANGE, Y_RANGE, X_RANGE * Y_RANGE);

	if (USE_TIMER) {
			endTest = clock();
			printf ("Test four completed in %0.2f seconds.\n\n", calcSeconds (startTest, endTest));
	} else printf ("Test four completed.\n\n");
}

double calcSeconds (clock_t start, clock_t finish)
{
	return (finish - start) / (double)(CLOCKS_PER_SEC);
}
