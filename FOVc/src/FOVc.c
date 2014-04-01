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

	distance = OffDistAx(Origin, Target);

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
	int x, y;
	bool axial = true;

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
			if (axial) OffDistAx(Origin, Target);
			else OffDistCube(Origin, Target);
		}
}

// Calculates distance from origin (0, 0) to each hex in the map
// Throws away results.  Uses the cube hex coordinate system
void ScanDistMap_Cube(int mapSize_x, int mapSize_y)
{

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
			CubeDist(Origin, Target);
		}
}

// Generates a random offset coordinate pair within an ([0, x], [0, y]) range
OffCoord RandCoord_Off(int x_range, int y_range)
{
	OffCoord result;
	result.x = mt_drand() * x_range;
	result.y = mt_drand() * y_range;

	return result;
}

// Generates a random axial coordinate pair within an ([0, x], [0, y]) range
// Range is given in offset coordinates, function will convert internally
AxCoord RandCoord_Ax(int x_range, int y_range)
{
	return OffToAx(RandCoord_Off(x_range, y_range));
}

// Generates a random cubic coordinate pair within an ([0, x], [0, y]) range
// Range is given in offset coordinates, function will convert internally
CubeCoord RandCoord_Cube(int x_range, int y_range)
{
	return OffToCube(RandCoord_Off(x_range, y_range));
}


// Calculates the LOS between the origin and target coordinates
// Includes range and azimuth calculations, also determines
// a list of hexes along that azimuth.
void LOS_CalcOff(OffCoord origin, OffCoord target)
{
	int distance = OffDistAx(origin, target);
	float azimuth = AzimuthOff(origin, target);


	//printf ("Distance between (%d, %d) and (%d, %d) using OffDistAx is %d.\n",
	//		origin.x, origin.y, target.x, target.y, distance);
	//printf ("Azimuth between the hexes is: %0.2f degrees.\n", azimuth);

	HexesBetweenOff(origin, target);
}

void LOS_CalcAx(AxCoord origin, AxCoord target)
{
	int distance = AxDist(origin, target);
	float azimuth = AzimuthAx(origin, target);
	HexesBetweenAx(origin, target);
}

void LOS_CalcCube(CubeCoord origin, CubeCoord target)
{
	int distance = CubeDist(origin, target);
	float azimuth = AzimuthCube(origin, target);
	HexesBetweenCube(origin, target);
}
