#include <stdio.h>
#include <time.h>

#include "FOVc.h"
#include "mtwist.h"

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
const bool USE_TIMER = false;		// Calculates time to run each test case


const int NUM_ITERATIONS = 10000 * 400;// Number of times the test function is run
									// when calculating LOS
const int X_RANGE = 1000;			// Horizontal map size, from 0 to X_RANGE
const int Y_RANGE = 1000;			// Vertical map size, from 0 to Y_RANGE

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

	for (base = 0; base < 1000000000; base++)
		belongToUs += base;

	if (USE_TIMER) {
		endTest = clock();
		printf ("Base function completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
	} else printf ("Base function completed.\n\n");
}

void test1()
{
	int i;
	OffCoord origin;
	OffCoord target;

	printf ("TEST ONE: Line of Sight calculations between two iterated points\n");

	for (i = 0; i < NUM_ITERATIONS * 10; i++)
	{

		origin.x = i % X_RANGE;
		origin.y = i % Y_RANGE;

		target.x = i % X_RANGE;
		target.y = i % Y_RANGE;

		LOS_Calc(origin.x, origin.y, target.x, target.y);
	}

	printf ("Test one complete.\n\n");
}

void test2()
{
	int i;
	OffCoord origin;
	OffCoord target;

	printf ("TEST TWO: Line of Sight calculations between two random points\n");

	for (i = 0; i < NUM_ITERATIONS / 10; i++)
	{

		origin = RandCoord_Off(X_RANGE, Y_RANGE);
		target = RandCoord_Off(X_RANGE, Y_RANGE);

		LOS_Calc(origin.x, origin.y, target.x, target.y);
	}

	printf ("Test two complete.\n\n");
}

void test3()
{
	int i;
	OffCoord origin;
	OffCoord target;

	printf ("TEST THREE: Only does distance and azimuth calculations between two random points.\n");

	for (i = 0; i < NUM_ITERATIONS * 50; i++)
	{

		origin = RandCoord_Off(X_RANGE, Y_RANGE);
		target = RandCoord_Off(X_RANGE, Y_RANGE);

		Dist_Azimuth(origin.x, origin.y, target.x, target.y);
	}

	printf ("Test three complete.\n\n");
}

void test4()
{
	int i;
	OffCoord origin;
	OffCoord target;

	printf ("TEST FOUR: Prints random coordinates in even-r offset format.\n");

	for (i = 0; i < NUM_ITERATIONS * 50; i++)
	{

		origin = RandCoord_Off(X_RANGE, Y_RANGE);
		target = RandCoord_Off(X_RANGE, Y_RANGE);

		Display_Coord(origin.x, origin.y, target.x, target.y);
	}

	printf ("Test four complete.\n\n");
}

double calcSeconds (clock_t start, clock_t finish)
{
	return (finish - start) / (double)(CLOCKS_PER_SEC);
}
