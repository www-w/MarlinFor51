#pragma once
/**
  * parser.h - Parser for a GCode line, providing a parameter interface.
  *	          Codes like M149 control the way the GCode parser behaves,
  *           so settings for these codes are located in this class.
  */

#include "../inc/MarlinConfig.h"

/**
  * GCode parser
  *  - Parse a single gcode line for its letter, code, subcode, and parameters
  *  - FASTER_GCODE_PARSER:
  *    - Flags existing params (1 bit each)
  *	   - Stores value offsets (1 byte each)
  *  - Provide accessors for parameters:
  *    - Parameter exists
  *    - Parameter has value
  *    - Parameter value in different units and types
  */
struct GCodeParser {
	char* value_ptr;		// Set by seen, used to fetch the value
	char* command_args;		// Args start here, for slow scan

	char* command_ptr;		// The command, so it can be echoed
	char* string_arg;		// string of command line
	char command_letter;	// G, M, or T
	int codenum;			// 123

}parser;

extern inline bool GCodeParser_valid_signless(const char * const p){
	return NUMERIC(p[0]) || (p[0] == '.' && NUMERIC(p[1])); //.?[0-9]
}
bool GCodeParser_valid_float(const char * const p){
	return GCodeParser_valid_signless(p) || ((p[0] == '-' || p[0] == '+') && GCodeParser_valid_signless(&p[1])); //[+-]?[0-9]?.?[0-9]
}

/** Code is found in the string. If not found, value_ptr is unchanged.
  * This allows "if (seen('A')||seen('B'))" to use the last-found value.
  */
extern inline bool GCodeParser_seen(const char c){
	char *p = strchr(parser.command_args, c);
	if(p){
        parser.value_ptr = GCodeParser_valid_float(&p[1]) ? &p[1] : (char*)NULL;
    }
	return !!p;
}

extern inline bool GCodeParser_seen_any(){
	return *(parser.command_args) == '\0';
}

#define SEEN_TEST(L) !!strchr(parser.command_args, L)
extern inline bool GCodeParser_seen_axis(){
	return SEEN_TEST('X') || SEEN_TEST('Y') || SEEN_TEST('Z') || SEEN_TEST('E');
}

// Populate all fields by parsing a single line of GCode
// This uses 54 bytes of SRAM to speed up seen/value
void parse(char *p);

// The code value pointer was set
extern inline bool has_value(){
	return parser.value_ptr != NULL;
}

// Seen a parameter with a value
bool GCodeParser_seenval(const char c) {
	return GCodeParser_seen(c) && has_value();
}

extern inline float value_float(){
    if(parser.value_ptr)
        return atof(parser.value_ptr);
    else
        return 0;

}

extern inline int32_t value_long(){
    return parser.value_ptr ? strtol(parser.value_ptr, NULL, 10) : 0L; 
}
extern inline uint32_t value_ulong(){
    return parser.value_ptr ? strtoul(parser.value_ptr, NULL, 10) : 0UL;
}
extern inline int16_t value_int(){
    return (int16_t)value_long();
}
extern inline uint16_t value_ushort(){
    return (uint16_t)value_long();
}
extern inline uint8_t value_byte(){
    return (uint8_t)constrain(value_long(), 0, 255);
}

// Bool is true with no value or non-zero . ps: only zero false
extern inline bool value_bool(){
    return !has_value() || !!value_byte();
}


extern inline float mm_to_linear_unit(const float mm){return mm;}
extern inline float mm_to_volumetric_unit(const float mm){return mm;}
extern inline float linear_value_to_mm(const float v){return v;}
extern inline float axis_value_to_mm(const enum AxisEnum axis,const float v){UNUSED(axis);return v;}
extern inline float per_axis_value(const enum AxisEnum axis, const float v){UNUSED(axis);return v;}


extern inline float value_linear_units() { return linear_value_to_mm(value_float());}
extern inline float value_axis_units(const enum AxisEnum axis) {
    //return axis_value_to_mm(axis, value_float());
    UNUSED(axis);
    return value_float();
}

extern inline float value_feedrate() { 
    //return value_linear_units(); 
    return value_float();
}

float linearval(const char c, const float dval) {
    //return GCodeParser_seenval(c)?value_linear_units():dval;
    return GCodeParser_seenval(c)?value_float():dval;
}
