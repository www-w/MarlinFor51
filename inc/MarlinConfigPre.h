#pragma once
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../Configuration.h"
#include "../Configuration_adv.h"
#include "../core/millis_t.h"
#include "../core/macros.h"
#define NOOP __asm nop __endasm
extern millis_t millis;
