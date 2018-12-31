#include "motion.h"

/** 
 * Cartesian Current Position
 *   Used to track the native machine position as moves are queued.
 *   Used by 'buffer_line_to_current_position' to do a move after changing it.
 *   used by 'sync_plan_position' to update 'planner.position'.
 */
float current_position[XYZE] = { 0 };

/**
 * Cartesian Destination
 *   The destination for a move, filled in by G-code movement commands,
 *   and expected by functions like 'prepare_move_to_destination'.
 *   Set with 'get_destination_from_command' or 'set_destination_from_current'.
 */
float destination[XYZE] = { 0 };

/**
 * The feedrate for the current move, often used as the default if 
 * no other feedrate is specified. Overridden for special moves.
 * Set by the last G0 through G5 command's "F" parameter.
 * Functions that override this for custom moves *must always* restore it!
 */
float feedrate_mm_s = MMM_TO_MMS(1500.0f);
