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

}
