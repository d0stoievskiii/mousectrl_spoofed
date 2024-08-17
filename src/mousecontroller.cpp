#include "mousecontroller.h"


BOOLEAN WINAPI mouseController::NtUserSendInput(UINT cInputs, LPINPUT pInputs, int cbSize) {
	LPVOID NtUserSendInput_Spoof = VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (!NtUserSendInput_Spoof) return FALSE;

	memcpy(NtUserSendInput_Spoof, NtUserSendInput_Bytes, 30);
	NTSTATUS result = reinterpret_cast<NTSTATUS(NTAPI*)(UINT, LPINPUT, int)>(NtUserSendInput_Spoof)(cInputs, pInputs, cbSize);

	ZeroMemory(NtUserSendInput_Spoof, 0x1000);
	VirtualFree(NtUserSendInput_Spoof, 0, MEM_RELEASE);
	return (result > 0);
}

BOOLEAN WINAPI mouseController::moveAbs(int x, int y) {
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
	input.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
	input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
	return NtUserSendInput(1, &input, sizeof(input));
}

BOOLEAN WINAPI mouseController::moveRel(int x, int y) {
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.mouseData = 0;
	input.mi.time = 0;
	input.mi.dx = x;
	input.mi.dy = y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK ;
	return NtUserSendInput(1, &input, sizeof(input));
}