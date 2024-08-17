#pragma once

#include <windows.h>

class mouseController {
public:
	BYTE NtUserSendInput_Bytes[30];
	//BYTE NtUserGetAsyncKeyState_Bytes[30];

	mouseController() {
		LPVOID NtUserSendInput_address = GetProcAddress(GetModuleHandle(L"win32u"), "NtUserSendInput");
		if (!NtUserSendInput_address) {

			NtUserSendInput_address = GetProcAddress(GetModuleHandle(L"user32"), "NtUserSendInput");
			if (!NtUserSendInput_address) {
				//windows 7 or older
				NtUserSendInput_address = GetProcAddress(GetModuleHandle(L"user32"), "SendInput");
			}
		}

		memcpy(NtUserSendInput_Bytes, NtUserSendInput_address, 30);
	}


	BOOLEAN WINAPI NtUserSendInput(UINT cInputs, LPINPUT pInputs, int cbSize);

	//UINT WINAPI NtUserGetAsyncKeyState(UINT Key);

	BOOLEAN WINAPI moveAbs(int x, int y);
	BOOLEAN WINAPI moveRel(int x, int y);
};
