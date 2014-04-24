#ifndef FOVC_H_
#define FOVC_H_

#include "HexMath.h"

typedef int bool;
#define true 1
#define false 0

void ScanDistMap(int x, int y);
void ScanDistMap_Offset(int x, int y);
void ScanDistMap_Cube(int x, int y);

void RandDistMap(int x, int y, int reps);
void RandDistMap_Offset(int x, int y);
void RandDistMap_Cube(int x, int y);

// Generates random coordinate sets within an x/y range
// x/y range is in offset coordinates
OffCoord RandCoord_Off(int x_range, int y_range);
AxCoord RandCoord_Ax(int x_range, int y_range);
CubeCoord RandCoord_Cube(int x_range, int y_range);

// Calculates LOS between the origin and target
void LOS_Calc(int x1, int y1, int z1, int x2, int y2, int z2);

void LOS_CalcAx(AxCoord origin, AxCoord target);
void LOS_CalcCube(CubeCoord origin, CubeCoord target);
void LOS_CalcOff(OffCoord origin, OffCoord target);

// Calculates the distance and azimuth between the origin and target
void Dist_Azimuth(int x1, int y1, int z1, int x2, int y2, int z2);

void Display_Coord(int x1, int y1, int z1, int x2, int y2, int z2);

#endif /* FOVC_H_ */
