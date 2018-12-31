#include "gcode.h"
#include "../module/motion.h"
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
        if (GCodeParser_seen(axis_codes[i])) {
            const float v = value_axis_units((enum AxisEnum)i);
            //destination[i] = (axis_relative_modes[i] || relative_mode)?
            //    current_position[i]+v
            //    : (i == E_AXIS) ? v : LOGICAL_TO_NATIVE(v, i);
            destination[i] = (i==E_AXIS) ? v: LOGICAL_TO_NATIVE(v, i);
        }
        else{
            destination[i] = current_position[i];
        }
    }
    if(linearval('F',0)>0){
        feedrate_mm_s = MMM_TO_MMS(value_feedrate());
    }
}
