/**
 * motion.h
 *
 * High-level motion commands to feed the planner
 * some of these methods may migrate to the planner class.
 */
#pragma once
#include "../inc/MarlinConfig.h"


#define LOGICAL_TO_NATIVE(POS, AXIS) (POS)

extern float current_position[XYZE]; // High-level current tool position
extern float destination[XYZE]; // Destination for a move


/**
 * Feed rates are often configured with mm/m
 * but the planner and stepper like mm/s units.
 */
extern float feedrate_mm_s;
