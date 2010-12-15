#if !defined(NAVFUNCTIONS)
#define NAVFUNCTIONS

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>



//#define   BAM_270_DEG       0xc0000000L    // BAM representation of 270 deg 
//#define   BAM_180_DEG       0x80000000L    // BAM representation of 180 deg 
//#define   NOT_BAM_180_DEG   0x7fffffffL    // BAM representation of 180 deg-
//#define   BAM_90_DEG        0x40000000L    // BAM representation of  90 deg 
//#define   MINUS_BAM_90_DEG  0xc0000000L    // BAM representation of -90 deg 
//#define   R                 3.43775e+05    // Radius of earth in 1/100 NM   
//#define   TWO_R             6.87550e+05    // Diameter of earth in 1/100 NM 
//#define   TWO_R_SQUARED     4.72725e+11    // TWO_R * TWO_R                 
//#define   TWO_R_HP          6.87550e+07    // Diam. of earth in 1/10000 NM  
//#define   SQUARED_TWO_R_HP  4.72725e+15    // TWO_R_HP * TWO_R_HP           
//#define BAM_TO_RAD 1.462918079e-9          // BAM to radians 
//#define RAD_TO_BAM 6.835652757e+8          // Radians to BAM       
#ifndef PI
#define PI               3.14159265358979323846 
#endif
//#define RAD_TO_BAM_DIV_2  0.5*RAD_TO_BAM


#define EARTH_DIAMETER				12733426.0				// Diameter of earth in meters 
#define SQUARED_EARTH_DIAMETER		162140137697476.0		// Diameter of earth in meters (EARTH_DIAMETER*EARTH_DIAMETER)
#ifndef DEG_TO_RAD
#define DEG_TO_RAD					0.0174532925199432958
#define RAD_TO_DEG					57.2957795131
#endif

	void xXY_to_LL(double Lat_TP, double Lon_TP, double X_int, double Y_int, double *Lat, double *Lon);
	void xLL_to_XY(double Lat_TP, double Lon_TP, double Lat_Pnt, double Lon_Pnt, double *X, double *Y);
	void xXY_Brg_Rng(double X_1, double Y_1, double X_2, double Y_2, double *Bearing, double *Range);
	void xBrg_Rng_XY(double X_RefPos, double Y_RefPos, double Bearing, double Range, double *X, double *Y);
	void xCrs_Spd_to_VxVy(double Crs, double Spd, double *Vx, double *Vy);
	void xVxVy_to_Crs_Spd(double Vx, double Vy, double *Crs, double *Spd);
	void LL_to_BearRange(double Lat_TP, double Long_TP, double Lat_Pnt, double Long_Pnt, double *Bearing, double *Range);
#endif
