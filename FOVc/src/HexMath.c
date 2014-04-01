#include <math.h>

#include "HexMath.h"


int OffDistCube (OffCoord origin, OffCoord target)
{
	return CubeDist(OffToCube(origin), OffToCube(target));
}

// This is about 8% more efficient than OffDistCube
int OffDistAx (OffCoord origin, OffCoord target)
{
	return AxDist(OffToAx(origin), OffToAx(target));
}

// Determines distance in hexes between two cube coordinates
// Algorithm from www.redblobgames.com/grids/hexagons
int CubeDist (CubeCoord origin, CubeCoord target)
{
	return (abs(origin.x - target.x) +
			abs(origin.y - target.y) +
			abs(origin.z - target.z)) / 2;
}

int AxDist (AxCoord origin, AxCoord target)
{
	int interim_z1 = -origin.x - origin.y;
	int interim_z2 = -target.x - target.y;

	return (abs(origin.x - target.x) +
			abs(origin.y - target.y) +
			abs(interim_z1 - interim_z2)) / 2;
}


// ------------------- Conversions between hex systems --------------------//

// Converts an even-r offset coordinate (x, y) into an axial hex coordinate (x, y)
AxCoord OffToAx (OffCoord off)
{
	AxCoord output;
	output.y = off.y;
	output.x = off.x - (off.y + (off.y & 1)) / 2.0;

	return output;
}

// Converts a cube hex coordinate (x, y, z) into an axial hex coordinate (x, y)
// Algorithm from www.redblobgames.com/grids/hexagons
AxCoord CubeToAx (CubeCoord cube)
{
	AxCoord output;
	output.x = cube.x;
	output.y = cube.z;

	return output;
}

// Converts an axial hex coordinate into a cube coordinate (x, y, z)
CubeCoord AxToCube (AxCoord ax)
{
	CubeCoord output;
	output.x = ax.x;
	output.z = ax.y;
	output.y = -ax.x - ax.y;

	return output;
}

// Converts an even-r offset (x, y) hex coordinate into cube coordinates (x, y, z)
// Algorithm from www.redblobgames.com/grids/hexagons
CubeCoord OffToCube (OffCoord off)
{
	CubeCoord output;
	output.x = off.x - (off.y + (off.y & 1)) / 2.0;
	output.z = off.y;
	output.y = -output.x -output.z;

	return output;
}

// Converts an axial hex coordinate into an even-r offset hex coordinate
OffCoord AxToOff (AxCoord ax)
{
	OffCoord output;
	output.y = ax.y;
	output.x = ax.x + (ax.y + (ax.y & 1)) / 2.0;

	return output;
}

// Converts a cube hex coordinate (x, y, z) into even-r offset (x, y)
// Algorithm from www.redblobgames.com/grids/hexagons
OffCoord CubeToOff (CubeCoord cube)
{
	OffCoord output;
	output.x = cube.x + (cube.z + (cube.z & 1)) / 2.0;
	output.y = cube.z;

	return output;
}


// ------------------- Azimuth calculations --------------------//

// Calculates the normalized azimuth in degrees between two axial coordinates
float AzimuthAx (AxCoord origin, AxCoord target)
{
	float result;
	int deltaX = target.x - origin.x;
	int deltaY = target.y - origin.y;

	// Converts first to an absolute x/y coordinate system
	float x = sqrt(3) * (deltaX + (deltaY / 2.0));
	float y = 1.5 * deltaY;


	result = atan2f(x, -y) * (180 / M_PI);
	if (result < 0) result += 360;

	return result;
}

// Calculates the normalized azimuth in degrees between two cubic coordinates
float AzimuthCube (CubeCoord origin, CubeCoord target)
{
	float result;
	int deltaX = target.x - origin.x;
	int deltaY = target.z - origin.z;

	// Converts first to an absolute x/y coordinate system
	float x = sqrt(3) * (deltaX + (deltaY / 2.0));
	float y = 1.5 * deltaY;


	result = atan2f(x, -y) * (180 / M_PI);
	if (result < 0) result += 360;

	return result;
}

// Calculates the normalized azimuth in degrees between two offset coordinates
// Uses the even-r offset
float AzimuthOff (OffCoord origin, OffCoord target)
{
	float result;
	int deltaX = target.x - origin.x;
	int deltaY = target.y - origin.y;

	// Converts first to an absolute x/y coordinate system
	float x = sqrt(3) * (deltaX - 0.5 * (deltaY & 1));
	float y = 1.5 * deltaY;


	result = atan2f(x, -y) * (180 / M_PI);
	if (result < 0) result += 360;

	return result;
}
