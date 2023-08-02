#include "stdafx.hpp"

#include "hooks.hpp"

#include <Windows.h>

#include <set>

bool(__thiscall *IsConsoleVisible)(void *);

bool __fastcall IsConsoleVisible_override(void *self)
{
	return IsConsoleVisible(self);
}

void *swap_vptr(void *target, int index, void *vptr)
{
	auto vtable = *static_cast<PVOID **>(target);

	DWORD old_protect;
	if (!VirtualProtect(vtable + index, sizeof(PVOID), PAGE_EXECUTE_READWRITE, &old_protect))
		return nullptr;

	PVOID old_vptr = InterlockedExchangePointer(vtable + index, vptr);
	VirtualProtect(vtable + index, sizeof(PVOID), old_protect, &old_protect);

	return old_vptr;
}

bool install_hooks(void *ivgui)
{
	IsConsoleVisible = static_cast<decltype(IsConsoleVisible)>(swap_vptr(ivgui, VPTR_INDEX, IsConsoleVisible_override));
	return IsConsoleVisible != nullptr;
}

bool remove_hooks(void *ivgui)
{
	return swap_vptr(ivgui, VPTR_INDEX, IsConsoleVisible) != nullptr;
}
