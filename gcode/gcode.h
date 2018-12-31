#pragma once
#include "../inc/MarlinConfig.h"
#include "parser.h"
#ifdef HOST_KEEPALIVE_FEATURE
    /**
     * States for managing Marlin and host communication
     * Marlin sends messages if blocked or busy
     */
enum MarlinBusyState{
    NOT_BUSY,   // Not in a handler
    IN_HANDLER, // Processing a GCode
    IN_PROCESS, // Known to be blocking command input (as in G29)
    PAUSED_FOR_USER,    // Blocking pending any input
    PAUSED_FOR_INPUT    // Blocking pending text input (concept)
};
void GcodeSuite_host_keepalive();
#define KEEPALIVE_STATE(n) gcode.busy_state=n
#else
#define KEEPALIVE_STATE(n) NOOP
#endif

struct GcodeSuite{
    millis_t previous_move_ms;
    unsigned char axis_relative_modes[4];
#ifdef HOST_KEEPALIVE_FEATURE
    enum MarlinBusyState busy_state;
    uint8_t host_keepalive_interval;
#endif
} gcode={.axis_relative_modes=AXIS_RELATIVE_MODES};
extern inline void GcodeSuite_reset_stepper_timeout(){
    gcode.previous_move_ms = millis;
}
int8_t GcodeSuite_get_target_extruder_from_command();
void GcodeSuite_get_destination_from_command();
void GcodeSuite_process_parsed_command();
void GcodeSuite_process_next_command();
extern inline void home_all_axes(){
    //GcodeSuite_G28(true); //TODO
}
void GcodeSuite_dwell(millis_t time);
void GcodeSuite_G0_G1(unsigned char fast_move); //default false
void GcodeSuite_G2_G3(const unsigned char clockwise);
void GcodeSuite_G28(const unsigned char always_home_all);

void GcodeInit();
