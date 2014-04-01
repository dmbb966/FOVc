#include <stdio.h>
#include <time.h>

#include "FOVc.h"
#include "mtwist.h"

void base();
void test_LOS1();
void test_LOS2();
void test_FOV1();
void test_FOV2();
void test_FOV3();
void test_FOV4();
void test_Azimuth();
double calcSeconds (clock_t start, clock_t finish);

clock_t startTest;
clock_t endTest;
clock_t timePassed;
double seconds;
const bool USE_TIMER = true;		// Calculates time to run each test case

const int NUM_ITERATIONS = 10000 * 10000;	// Number of times the test function is run
									// within the test case
const int X_RANGE = 1000;			// Horizontal map size, from 0 to X_RANGE
const int Y_RANGE = 1000;			// Vertical map size, from 0 to Y_RANGE

int main()
{
	int a;

	mt_seed32new(mt_seed());

	//base();
	//test_LOS1();
	//test_LOS2();
	//test_FOV1();
	//test_FOV2();
	test_FOV3();
	test_FOV4();

	//for (a = 0; a < 5; a++)
	//	test_Azimuth();

	return 0;
}

void base()
{
	int base;
	int belongToUs = 0;

	if (USE_TIMER) startTest = clock();

	for (base = 0; base < 1000000000; base++)
		belongToUs += base;

	if (USE_TIMER) {
		endTest = clock();
		printf ("Base function completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
	} else printf ("Base function completed.\n");
}


// Generates random coordinate pairs and calculates LOS information
// between the two (distance, azimuth, list of hexes along that azimuth)
void test_LOS1()
{
	int i;

	printf ("TEST ONE: Line of Sight calculations between two random points\n");
	printf ("Intended to test performance diff between offset and axial coordinates.\n");

	if (USE_TIMER) startTest = clock();

	for (i = 0; i < NUM_ITERATIONS; i++)
		LOS_Calc(RandCoord_Off(X_RANGE, Y_RANGE), RandCoord_Off(X_RANGE, Y_RANGE));

	if (USE_TIMER) {
		endTest = clock();
		printf ("Test one completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
	} else printf ("Test one completed.\n");
}

// Generates random coordinate pairs and calculates LOS information
// between the two (distance, azimuth, list of hexes along that azimuth)
void test_LOS2()
{
	printf ("TEST TWO: Line of Sight calculations between two random points\n");
	printf ("Intended to test performance diff between offset and cubic coordinates.\n");
	if (USE_TIMER) startTest = clock();
	ScanDistMap_Offset(10000, 10000);
	if (USE_TIMER) {
		endTest = clock();
		printf ("Test two completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
	} else printf ("Test one completed.\n");
}




void test_FOV1()
{
	int a;
	int result;
	OffCoord origin;
	OffCoord target;

	printf ("TEST THREE: Distance calculations between two random hexes using OffDistAx\n");
	if (USE_TIMER) startTest = clock();
	for (a = 0; a < NUM_ITERATIONS; a++)
	{
		origin = RandCoord_Off(X_RANGE, Y_RANGE);
		target = RandCoord_Off(X_RANGE, Y_RANGE);
		result = OffDistAx(origin, target);
	}
	if (USE_TIMER) {
		endTest = clock();
		printf ("Test three completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
	} else 	printf ("Test three completed.\n");
}

void test_FOV2()
{
	int a;
	int result;
	OffCoord origin;
	OffCoord target;

	printf ("TEST FOUR: Distance calculations between two random hexes using OffDistCube\n");
	if (USE_TIMER) startTest = clock();
	for (a = 0; a < NUM_ITERATIONS; a++)
	{
		origin = RandCoord_Off(X_RANGE, Y_RANGE);
		target = RandCoord_Off(X_RANGE, Y_RANGE);
		result = OffDistAx(origin, target);
	}
	if (USE_TIMER) {
		endTest = clock();
		printf ("Test four completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
	} else 	printf ("Test four completed.\n");
}

void test_FOV3()
{
	int a;
	OffCoord origin;
	OffCoord target;

	printf ("TEST FIVE: Azimuth calculations between two iterated hexes using AzimuthOff\n");
	if (USE_TIMER) startTest = clock();
	for (a = 0; a < NUM_ITERATIONS; a++)
	{
		origin.x = a % X_RANGE;
		origin.y = a % Y_RANGE;

		target.x = a % X_RANGE;
		target.y = a % Y_RANGE;

		AzimuthOff(origin, target);
	}
	if (USE_TIMER) {
		endTest = clock();
		printf ("Test five completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
	} else 	printf ("Test five completed.\n");
}

void test_FOV4()
{
	int a;
	AxCoord origin;
	AxCoord target;

	printf ("TEST SIX: Distance calculations between two iterated hexes using AzimuthAx\n");
	if (USE_TIMER) startTest = clock();
	for (a = 0; a < NUM_ITERATIONS; a++)
	{
		origin.x = a % X_RANGE;
		origin.y = a % Y_RANGE;

		target.x = a % X_RANGE;
		target.y = a % Y_RANGE;

		AzimuthAx(origin, target);
	}
	if (USE_TIMER) {
		endTest = clock();
		printf ("Test six completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
	} else 	printf ("Test six completed.\n");
}

double calcSeconds (clock_t start, clock_t finish)
{
	return (finish - start) / (double)(CLOCKS_PER_SEC);
}

void test_Azimuth()
{
	OffCoord origin;
	OffCoord target;

	printf ("Enter Origin x: ");
	scanf ("%d", &origin.x);
	printf ("Enter Origin y: ");
	scanf ("%d", &origin.y);

	printf ("Enter target x: ");
	scanf ("%d", &target.x);
	printf ("Enter target y: ");
	scanf ("%d", &target.y);

	//printf ("Axial: %0.3f\n", AzimuthAx(OffToAx(origin), OffToAx(target)));
	printf ("Offset: %0.3f\n", AzimuthOff(origin, target));
	//printf ("Cubic: %0.3f\n", AzimuthCube(OffToCube(origin), OffToCube(target)));


}
