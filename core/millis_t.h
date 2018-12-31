#pragma once
#include <stdint.h>
typedef uint32_t millis_t;

#define PENDING(NOW,SOON) ((int32_t)(NOW-(SOON))<0)
