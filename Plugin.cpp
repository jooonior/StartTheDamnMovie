#include "Plugin.h"

#include "ServerPluginCallbacks.h"

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
	ConColorMsg(Color(0, 255, 0, 255), PLUGIN_PREFIX PLUGIN_DESC " loaded.\n");
	return true;
}

void Plugin::Unload(void)
{
}

const char *Plugin::GetPluginDescription(void)
{
	return PLUGIN_DESC;
}
