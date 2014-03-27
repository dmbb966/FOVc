#ifndef HEXMATH_H_
#define HEXMATH_H_

typedef struct
{
	int x;
	int y;
} OffCoord;

typedef struct
{
	int x;
	int y;
} AxCoord;

typedef struct
{
	int x;
	int y;
	int z;
} CubeCoord;

// Distance calculations
int AxDist (AxCoord origin, AxCoord target);
int OffDistAx (OffCoord origin, OffCoord target);
int OffDistCube (OffCoord origin, OffCoord target);
int CubeDist (CubeCoord origin, CubeCoord target);

// Conversion calculations
AxCoord CubeToAx (CubeCoord cube);
AxCoord OffToAx (OffCoord off);

CubeCoord AxToCube (AxCoord ax);
CubeCoord OffToCube (OffCoord off);

OffCoord AxToOff (AxCoord ax);
OffCoord CubeToOff (CubeCoord cube);


#endif /* HEXMATH_H_ */
