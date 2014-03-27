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

#endif /* FOVC_H_ */
