#include "gcode.h"
void GcodeInit(){
#ifdef HOST_KEEPALIVE_FEATURE
    gcode.busy_state=NOT_BUSY;
    gcode.host_keepalive_interval=DEFAULT_KEEPALIVE_INTERVAL;
#endif
}

/**
 * Get the target extruder from the T parameter or the active_extruder
 * Return -1 if the T parameter is out of range
 * Current just using one extruder
 */
int8_t GcodeSuite_get_target_extruder_from_command(){
    return 0;
}

/**
  * SET XYZE destination and feedrate from the current GCode command
  *
  * - Set destination from included axis codes
  * - Set to current for missing axis codes
  * - Set the feedrate, if included
  */
void GcodeSuite_get_destination_from_command(){
	LOOP_XYZE(i){
	}
}
