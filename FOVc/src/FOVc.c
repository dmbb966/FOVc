#include <stdio.h>

#include "FOVc.h"
#include "mtwist.h"

const bool DEBUG_HEX = false;

// Calculates distance between two random points in the map
// Throws away the results.  Does (reps) number of iterations.
void RandDistMap(int mapSize_x, int mapSize_y, int reps)
{
	int i;

	for (i = 0; i < reps; i++)
	{
		RandDistMap_Cube(mapSize_x, mapSize_y);
	}
}

// Calculates distance between the origin and every other point
// on the map.  Throws away the results.
void ScanDistMap(int mapSize_x, int mapSize_y)
{
	ScanDistMap_Offset(mapSize_x, mapSize_y);
}

// Calculates distance between two random points in the map
// Throws away the results.  Uses the even-r offset hex coordinate system.
void RandDistMap_Offset(int mapSize_x, int mapSize_y)
{
	int distance = 0;
	OffCoord Origin;
	OffCoord Target;
	Origin.x = mt_drand() * mapSize_x;
	Origin.y = mt_drand() * mapSize_y;

	Target.x = mt_drand() * mapSize_x;
	Target.y = mt_drand() * mapSize_y;

	distance = OffDistCube(Origin, Target);

	if (DEBUG_HEX)
		printf ("Offset (%d, %d) to (%d, %d) is %d hexes.\n", Origin.x, Origin.y,
			Target.x, Target.y, distance);
}

// Calculates distance between two random points in the map
// Throws away the results.  Uses the even-r offset hex coordinate system.
void RandDistMap_Cube(int mapSize_x, int mapSize_y)
{
	int distance = 0;
	CubeCoord Origin;
	CubeCoord Target;
	Origin.x = mt_drand() * mapSize_x;
	Origin.z = mt_drand() * mapSize_y;
	Origin.y = -Origin.x - Origin.z;

	Target.x = mt_drand() * mapSize_x;
	Target.z = mt_drand() * mapSize_y;
	Target.y = -Origin.x - Origin.z;

	distance = CubeDist(Origin, Target);

	if (DEBUG_HEX)
		printf ("Cube (%d, %d, %d) to (%d, %d, %d) is %d hexes.\n", Origin.x,
			Origin.y, Origin.z, Target.x, Target.y, Target.z, distance);
}

// Calculates distance from origin (0, 0) to each hex in the map
// Throws away results.  Uses the even-r offset hex coordinate system.
void ScanDistMap_Offset(int mapSize_x, int mapSize_y)
{
	int distance = 0;
	int x, y;
	bool axial = false;

	// Offset coordinate configuration
	OffCoord Origin;
	OffCoord Target;
	Origin.x = 0;
	Origin.y = 0;

	for (y = 0; y < mapSize_y; y++)
		for (x = 0; x < mapSize_x; x++)
		{
			// Offset coordination configuration
			Target.x = x;
			Target.y = y;
			if (axial) distance = OffDistAx(Origin, Target);
			else distance = OffDistCube(Origin, Target);
		}
}

// Calculates distance from origin (0, 0) to each hex in the map
// Throws away results.  Uses the cube hex coordinate system
void ScanDistMap_Cube(int mapSize_x, int mapSize_y)
{

	int distance = 0;
	int x, y;

	// Cube coordinate configuration
	CubeCoord Origin;
	CubeCoord Target;
	Origin.x = 0;
	Origin.y = 0;
	Origin.z = 0;

	for (y = 0; y < mapSize_y; y++)
		for (x = 0; x < mapSize_x; x++)
		{
			// Cube coordination configuration
			Target.x = x;
			Target.y = y;
			Target.z = -x - y;
			distance = CubeDist(Origin, Target);
		}
}
