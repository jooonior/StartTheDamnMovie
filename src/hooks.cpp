#include "stdafx.hpp"

#include "hooks.hpp"

#include <Windows.h>

#include <set>

bool(__thiscall *IsConsoleVisible)(void *);

template<int N>
bool match(void *ptr, const short(&pattern)[N])
{
	auto bytes = static_cast<unsigned char *>(ptr);

	for (auto byte : pattern)
	{
		if (byte >= 0 && byte != *bytes)
			return false;

		++bytes;
	}

	return true;
}

bool __fastcall IsConsoleVisible_override(void *self)
{
	auto ret = _ReturnAddress();

	// if (cl_movieinfo.IsRecording() && !Con_IsVisible() && !scr_drawloading)
	static const short CL_TakeSnapshotAndSwap[] = {
		0x84, 0xC0,                  // test        al,al
		0x75, 0x1E,                  // jne short   0x20
		0x38, 0x05, -1, -1, -1, -1,  // cmp         byte ptr ds:[????????],al
		0x75, 0x16,                  // jne short   0x18
	};

	// return (IsReplayRendering() || cl_movieinfo.IsRecording()) && !Con_IsVisible();
	static const short SND_IsRecording[] = {
		0x84, 0xC0,                  // test        al,al
		0x75, 0x03,                  // jne short   0x05
		0xB0, 0x01,                  // mov         al,1
		0xC3,                        // ret
	};

	// Don't know where this one comes from.
	static const short idk[] = {
		0x84, 0xC0,                  // test        al,al
		0x0F, 0x85, -1, -1, -1, -1,  // jne near    ????????
		0x8B, 0x35, -1, -1, -1, -1,  // mov         esi,dword ptr ds:[????????]
		0x8D, 0x1C, 0x36,            // lea         ebx,[esi+esi]
	};

	if (match(ret, CL_TakeSnapshotAndSwap))
		return false;

	if (match(ret, SND_IsRecording))
		return false;

	if (match(ret, idk))
		return false;

#ifdef _DEBUG
	static std::set<void *> seen;
	if (seen.insert(ret).second)
	{
		Msg("%p\n", ret);
	}
#endif

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
