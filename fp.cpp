#include "fp.h"

fp p = { 0x33c6c87b, 0x1b81b905, 0x57aca835, 0xc2721bf4, 0x1f0b4f25, 0x516730cc, 0x67f35507, 0xa7aac6c5, 0x9322c9cd, 0x5afbfcc6, 0xedc88c42, 0xb42d083a, 0x5e3e4c4a, 0xfc8ab0d1, 0x740f89bf, 0x65b48e8f };
fp r_squared_modp = { 0x2ffc1724, 0x36905b57, 0x25f1f27d, 0x67086f45, 0xd22370ca, 0x4faf3fbf, 0xbcc584b1, 0x192ea214, 0x2f5de3d0, 0x5dae03ee, 0x1776b371, 0x1e924873, 0x20e4f52d, 0xad5f166e, 0xa6f3917e, 0x4ed759ae };
fp uintbig_1 = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// this is not constant time version
void __stdcall reduce_once(fp a) {
	fp tmp = { 0, };
	DWORD no_carry = 0;

	__asm {
		mov esi, [a]
		mov eax, [esi + 0]
		sbb eax, [p + 0]
		mov[tmp + 0], eax
		mov eax, [esi + 4]
		sbb eax, [p + 4]
		mov[tmp + 4], eax
		mov eax, [esi + 8]
		sbb eax, [p + 8]
		mov[tmp + 8], eax
		mov eax, [esi + 12]
		sbb eax, [p + 12]
		mov[tmp + 12], eax
		mov eax, [esi + 16]
		sbb eax, [p + 16]
		mov[tmp + 16], eax
		mov eax, [esi + 20]
		sbb eax, [p + 20]
		mov[tmp + 20], eax
		mov eax, [esi + 24]
		sbb eax, [p + 24]
		mov[tmp + 24], eax
		mov eax, [esi + 28]
		sbb eax, [p + 28]
		mov[tmp + 28], eax
		mov eax, [esi + 32]
		sbb eax, [p + 32]
		mov[tmp + 32], eax
		mov eax, [esi + 36]
		sbb eax, [p + 36]
		mov[tmp + 36], eax
		mov eax, [esi + 40]
		sbb eax, [p + 40]
		mov[tmp + 40], eax
		mov eax, [esi + 44]
		sbb eax, [p + 44]
		mov[tmp + 44], eax
		mov eax, [esi + 48]
		sbb eax, [p + 48]
		mov[tmp + 48], eax
		mov eax, [esi + 52]
		sbb eax, [p + 52]
		mov[tmp + 52], eax
		mov eax, [esi + 56]
		sbb eax, [p + 56]
		mov[tmp + 56], eax
		mov eax, [esi + 60]
		sbb eax, [p + 60]
		mov[tmp + 60], eax

		setnc al
		movzx eax, al
		mov no_carry, eax
	}

	if (no_carry) {
		for (int i = 0; i < NUMBER_OF_BYTES; i++) {
			a[i] = tmp[i];
		}
	}
}

void __stdcall fp_enc(fp c, const fp a) {
	fp_mul(c, a, r_squared_modp);
}

void __stdcall fp_dec(fp c, const fp a) {
	fp_mul(c, a, uintbig_1);
}

void __stdcall fp_mul(fp c, const fp a, const fp b) {
	uint32_t t[NUMBER_OF_BYTES + 1] = { 0, };
	uint32_t invp = 0x632e294d;
#define MACRO(k, I0, I1, I2, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12, I13, I14, I15, I16) {\
	__asm mov esi, dword ptr [a] \
	__asm mov edx, dword ptr [esi + 0] \
	__asm mov esi, dword ptr [b] \
	__asm mulx eax, edx, [esi + k] \
	__asm add edx, [t + I0] \
	__asm mulx eax, edx, invp\
	__asm xor eax, eax\
	__asm xor ecx, ecx\
	__asm mov edi, dword ptr [t + I0]\
	__asm mulx ebx, eax, dword ptr [p + 0]\
	__asm adcx edi, eax\
	__asm mov [t + I0], edi\
	__asm mov edi, dword ptr [t + I1]\
	__asm mulx ecx, eax, dword ptr[p + 4]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I1], edi\
	__asm mov edi, dword ptr [t + I2]\
	__asm mulx ebx, eax, dword ptr[p + 8]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I2], edi\
	__asm mov edi, dword ptr [t + I3]\
	__asm mulx ecx, eax, dword ptr[p + 12]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I3], edi\
	__asm mov edi, dword ptr [t + I4]\
	__asm mulx ebx, eax, dword ptr[p + 16]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I4], edi\
	__asm mov edi, dword ptr [t + I5]\
	__asm mulx ecx, eax, dword ptr[p + 20]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I5], edi\
	__asm mov edi, dword ptr [t + I6]\
	__asm mulx ebx, eax, dword ptr[p + 24]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I6], edi\
	__asm mov edi, dword ptr [t + I7]\
	__asm mulx ecx, eax, dword ptr[p + 28]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I7], edi\
	__asm mov edi, dword ptr [t + I8]\
	__asm mulx ebx, eax, dword ptr[p + 32]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I8], edi\
	__asm mov edi, dword ptr [t + I9]\
	__asm mulx ecx, eax, dword ptr[p + 36]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I9], edi\
	__asm mov edi, dword ptr [t + I10]\
	__asm mulx ebx, eax, dword ptr[p + 40]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I10], edi\
	__asm mov edi, dword ptr [t + I11]\
	__asm mulx ecx, eax, dword ptr[p + 44]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I11], edi\
	__asm mov edi, dword ptr [t + I12]\
	__asm mulx ebx, eax, dword ptr[p + 48]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I12], edi\
	__asm mov edi, dword ptr [t + I13]\
	__asm mulx ecx, eax, dword ptr[p + 52]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I13], edi\
	__asm mov edi, dword ptr [t + I14]\
	__asm mulx ebx, eax, dword ptr[p + 56]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I14], edi\
	__asm mov edi, dword ptr [t + I15]\
	__asm mulx ecx, eax, dword ptr[p + 60]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I15], edi\
	__asm mov eax, 0\
	__asm mov edi, dword ptr [t + I16]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I16], edi\
	__asm mov esi, dword ptr [b] \
	__asm mov edx, dword ptr [esi + k]\
	__asm xor eax,eax\
	__asm mov esi, dword ptr [a] \
	__asm mov edi, dword ptr [t + I0]\
	__asm mulx ebx, eax, dword ptr[esi + 0]\
	__asm adcx edi, eax\
	__asm mov [t + I0], edi\
	__asm mov edi, dword ptr [t + I1]\
	__asm mulx ecx, eax, dword ptr[esi + 4]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I1], edi\
	__asm mov edi, dword ptr[t + I2]\
	__asm mulx ebx, eax, dword ptr[esi + 8]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I2], edi\
	__asm mov edi, dword ptr [t + I3]\
	__asm mulx ecx, eax, dword ptr[esi + 12]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I3], edi\
	__asm mov edi, dword ptr[t + I4]\
	__asm mulx ebx, eax, dword ptr[esi + 16]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I4], edi\
	__asm mov edi, dword ptr [t + I5]\
	__asm mulx ecx, eax, dword ptr[esi + 20]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I5], edi\
	__asm mov edi, dword ptr[t + I6]\
	__asm mulx ebx, eax, dword ptr[esi + 24]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I6], edi\
	__asm mov edi, dword ptr [t + I7]\
	__asm mulx ecx, eax, dword ptr[esi + 28]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I7], edi\
	__asm mov edi, dword ptr[t + I8]\
	__asm mulx ebx, eax, dword ptr[esi + 32]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I8], edi\
	__asm mov edi, dword ptr [t + I9]\
	__asm mulx ecx, eax, dword ptr[esi + 36]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I9], edi\
	__asm mov edi, dword ptr[t + I10]\
	__asm mulx ebx, eax, dword ptr[esi + 40]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I10], edi\
	__asm mov edi, dword ptr [t + I11]\
	__asm mulx ecx, eax, dword ptr[esi + 44]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I11], edi\
	__asm mov edi, dword ptr[t + I12]\
	__asm mulx ebx, eax, dword ptr[esi + 48]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I12], edi\
	__asm mov edi, dword ptr [t + I13]\
	__asm mulx ecx, eax, dword ptr[esi + 52]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I13], edi\
	__asm mov edi, dword ptr[t + I14]\
	__asm mulx ebx, eax, dword ptr[esi + 56]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I14], edi\
	__asm mov edi, dword ptr [t + I15]\
	__asm mulx ecx, eax, dword ptr[esi + 60]\
	__asm adcx edi, ebx\
	__asm adox edi, eax\
	__asm mov [t + I15], edi\
	__asm mov eax, 0\
	__asm mov edi, dword ptr[t + I16]\
	__asm adcx edi, ecx\
	__asm adox edi, eax\
	__asm mov [t + I16], edi\
}

	__asm {
		MACRO(0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 0)
		MACRO(4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 0, 4)
		MACRO(8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 0, 4, 8)
		MACRO(12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 0, 4, 8, 12)
		MACRO(16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 0, 4, 8, 12, 16)
		MACRO(20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 0, 4, 8, 12, 16, 20)
		MACRO(24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 0, 4, 8, 12, 16, 20, 24)
		MACRO(28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 0, 4, 8, 12, 16, 20, 24, 28)
		MACRO(32, 36, 40, 44, 48, 52, 56, 60, 64, 0, 4, 8, 12, 16, 20, 24, 28, 32)
		MACRO(36, 40, 44, 48, 52, 56, 60, 64, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36)
		MACRO(40, 44, 48, 52, 56, 60, 64, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40)
		MACRO(44, 48, 52, 56, 60, 64, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44)
		MACRO(48, 52, 56, 60, 64, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48)
		MACRO(52, 56, 60, 64, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52)
		MACRO(56, 60, 64, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56)
		MACRO(60, 64, 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60)
	}
	for (int i = 0; i < NUMBER_OF_BYTES; i++) {
		c[i] = t[i];
	}
	reduce_once(c);
}
