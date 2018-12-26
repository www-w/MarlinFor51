#pragma once
/**
  * parser.h - Parser for a GCode line, providing a parameter interface.
  *	          Codes like M149 control the way the GCode parser behaves,
  *           so settings for these codes are located in this class.
  */

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

}paser;

extern inline bool GCodeParser_valid_signless(const char * const p){
	return NUMERIC(p[0]) || (p[0] == '.' && NUMERIC(p[1])); //.?[0-9]
}
extern inline bool GCodeParser_valid_float(const char * const p){
	return valid_signless(p) || ((p[0] == '-' || p[0] == '+') && valid_signless(&p[1])); //[+-]?[0-9]?.?[0-9]
}

/** Code is found in the string. If not found, value_ptr is unchanged.
  * This allows "if (seen('A')||seen('B'))" to use the last-found value.
  */
extern inline bool GCodeParser_seen(const char c){
	char *p = strchr(paser.command_args, c);
	if(p) paser.value_ptr = GCodeParser_valid_float(&p[1]) ? &p[1] : (char*)NULL;
	return !!p;
}

extern inline bool GCodeParser_seen_any(){
	return *(paser.command_args) == '\0';
}

#define SEEN_TEST(L) !!strchr(paser.command_args, L)
extern inline bool GCodeParser_seen_axis(){
	return SEEN_TEST('X') || SEEN_TEST('Y') || SEEN_TEST('Z') || SEEN_TEST('E');
}

// Populate all fields by parsing a single line of GCode
// This uses 54 bytes of SRAM to speed up seen/value
void parse(char *p);

// The code value pointer was set
extern inline bool has_value(){
	return parser.value_ptr != Null;
}

// Seen a parameter with a value
extern inline bool seenval(const char c) {
	return GCodeParser_seen(c) && has_value();
}
