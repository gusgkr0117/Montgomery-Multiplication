#include <windows.h>
#include <stdint.h>

constexpr auto NUMBER_OF_BYTES = 16;

typedef uint32_t fp[NUMBER_OF_BYTES];
typedef fp proj[2];

extern fp p;

void __stdcall fp_mul(fp c, const fp a, const fp b);
void __stdcall reduce_once(fp a);
void __stdcall fp_enc(fp c, const fp a);
void __stdcall fp_dec(fp c, const fp a);
void __stdcall fp_mul(fp c, const fp a, const fp b);