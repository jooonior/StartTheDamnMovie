#include "stdafx.hpp"

#include "Plugin.hpp"

#include "ServerPluginCallbacks.hpp"
#include "hooks.hpp"

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)

#define PLUGIN_VERSION STR(PLUGIN_VERSION_MAJOR) "." STR(PLUGIN_VERSION_MINOR) "." STR(PLUGIN_VERSION_PATCH)

void *ivgui;

class Plugin : public ServerPluginCallbacks
{
public:
	Plugin();
	~Plugin();

	virtual bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory);
	virtual void Unload(void);
	virtual const char *GetPluginDescription(void);
};

EXPOSE_SINGLE_INTERFACE(Plugin, IServerPluginCallbacks, INTERFACEVERSION_ISERVERPLUGINCALLBACKS);

Plugin::Plugin() {}
Plugin::~Plugin() {}

bool Plugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	PluginMsg("Loading version %s\n", PLUGIN_VERSION);

	ivgui = interfaceFactory(VENGINE_VGUI_VERSION, nullptr);
	if (!ivgui)
	{
		PluginWarning("Cannot find interface '%s'\n.", VENGINE_VGUI_VERSION);
		return false;
	}

	if (!install_hooks(ivgui))
	{
		PluginWarning("Failed to install hooks.\n");
		return false;
	}

	return true;
}

void Plugin::Unload(void)
{
	if (remove_hooks(ivgui))
	{
		PluginWarning("Failed to remove hooks.\n");
	}
}

const char *Plugin::GetPluginDescription(void)
{
	return PLUGIN_NAME " v" PLUGIN_VERSION;
}
