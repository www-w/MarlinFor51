#pragma once
#include "../inc/MarlinConfig.h"
class GcodeSuite{
    public:
        GcodeSuite(){}
        static bool axis_relative_modes[];
        static millis_t previous_move_ms;
}
