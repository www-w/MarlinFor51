#pragma once

/**
  * Axis indices as enumerated constants
  *
  * - X_AXIS, Y_AXIS, and Z_AXIS should be used for axes in Cartesian space
  * - A_AXIS, B_AXIS, and C_AXIS should be used for Steppers, corresponding to XYZ on Cartesians
  * - X_HEAD, Y_HEAD, and Z_HEAD should be used for Steppers on Core kinematics
  */
enum AxisEnum{
	X_AXIS	= 0,
	A_AXIS	= 0,
	Y_AXIS	= 1,
	B_AXIS	= 1,
	Z_AXIS	= 2,
	C_AXIS	= 2,
	E_AXIS	= 3,
	X_HEAD	= 4,
	Y_HEAD	= 5,
	Z_HEAD	= 6,
	ALL_AXES= 0xFE,
	NO_AXIS	= 0xFF
}; 

#define LOOP_S_LE_N(VAR, S, N) for (uint8_t VAR=(S); VAR<=(N); VAR++)

#define LOOP_XYZE(VAR) LOOP_S_LE_N(VAR, X_AXIS, E_AXIS)
