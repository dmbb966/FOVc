
To change the length of the tests, change NUM_ITERATIONS in main.c.  The number of iterations on each test has been adjusted so that each test will take roughly the same amount of time.

Differences between the three versions here:

All changes are in FOVC.c.

v1 - represents initial version, using even-r offset coordinates (traditional x, y hex coordinates, origin in upper left hand corner)
v2 - represents supposedly the most efficient but least readable version, using cubic coordinates (x, y, z)
v3 - represents a design compromise between efficiency and readability - it uses 2D axial coordinates (which can translate into cubic coordinates much easier than offset coordinates)

test1() - LOS calculations between two points (iterated)
    
LOS_Calc (all LOS_Calc functions call in turn Dist__, Azimuth__, and HexesBetween__ for each coordinate system)
    v1: LOS_CalcOff 
    v2: LOS_CalcCube
    v3: LOS_CalcAx
    
test2() - LOS calculations between two random points

v1: RandCoord_Off
v2: RandCoord_Cube
v3: RandCoord_Ax
* All random number generation is done in main.c

LOS_Calc (all LOS_Calc functions call in turn Dist__, Azimuth__, and HexesBetween__ for each coordinate system)
    v1: LOS_CalcOff
    v2: LOS_CalcCube
    v3: LOS_CalcAx
       
       
test3() - Only does distance and azimuth calculations between two random points

v1: RandCoord_Off
v2: RandCoord_Cube
v3: RandCoord_Ax
* All random number generation is done in main.c

Dist_Azimuth
    v1: OffDistAx and AzimuthOff
    v2: CubeDist and AzimuthCube
    v3: AxDist and AzimuthAx
    
test4() - Prints random coordinates in even-r offset format

v1: RandCoord_Off
v2: RandCoord_Cube
v3: RandCoord_Ax
* All random number generation is done in main.c

Display_Coord
    v1: No functions called since input is already in offset coordinates
    v2: AxtoOff
    v3: CubetoOff
