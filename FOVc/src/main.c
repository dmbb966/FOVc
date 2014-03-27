#include <stdio.h>
#include <time.h>

#include "FOVc.h"
#include "mtwist.h"

void base();
void test1();
void test2();
double calcSeconds (clock_t start, clock_t finish);

clock_t startTest;
clock_t endTest;
clock_t timePassed;
double seconds;

int main()
{

	mt_seed32new(mt_seed());

	//base();
	test1();
	test2();

	return 0;
}

void base()
{
	int base;
	int belongToUs = 0;

	startTest = clock();

	for (base = 0; base < 1000000000; base++)
		belongToUs += base;

	endTest = clock();
	printf ("Base function completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
}

void test1()
{
	printf ("Test one: ScanDistMap, 10000x10000, offset w/ Axial\n");
	startTest = clock();
	ScanDistMap_Offset(10000, 10000);
	endTest = clock();
	printf ("Test one completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
}

void test2()
{
	printf ("Test two: ScanDistMap, 10000x10000, cubic\n");
	startTest = clock();
	ScanDistMap_Cube(10000, 10000);
	endTest = clock();
	printf ("Test two completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
}

double calcSeconds (clock_t start, clock_t finish)
{
	return (finish - start) / (double)(CLOCKS_PER_SEC);
}
