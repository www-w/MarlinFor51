#pragma once

#define XYZE 4

#define WITHIN(V,L,H) ((V) >= (L) && (V) <= (H))
#define NUMERIC(a) WITHIN(a,'0','9')
/**
 * Arduino constrain macro
 */
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

// Remove compiler warning on an unused variable
#define UNUSED(x) ((void)(x))

#define MMM_TO_MMS(MM_M) ((MM_M)/60.0f)
#define MMS_TO_MMM(MM_S) ((MM_S)*60.0f)
