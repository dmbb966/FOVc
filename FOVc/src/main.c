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

int main()
{

	mt_seed32new(mt_seed());

	//base();
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


void test3()
{
	int a;
	printf ("Test three: RandDistMap, 10000x10000, 10000^2 runs, offset w/ Axial\n");
	startTest = clock();
	for (a = 0; a < 10000 * 10000; a++)
	{
		RandDistMap_Offset(10000, 10000);
	}
	endTest = clock();
	printf ("Test three completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
}

void test4()
{
	int a;
	printf ("Test four: RandDistMap, 10000x10000, 10000^2 runs, cubic\n");
	startTest = clock();
	for (a = 0; a < 10000 * 10000; a++)
	{
		RandDistMap_Cube(10000, 10000);
	}
	endTest = clock();
	printf ("Test two completed in %0.2f seconds.\n", calcSeconds (startTest, endTest));
}

double calcSeconds (clock_t start, clock_t finish)
{
	return (finish - start) / (double)(CLOCKS_PER_SEC);
}
