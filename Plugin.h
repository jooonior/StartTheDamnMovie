#pragma once

#define CLIENT_DLL
#include "cbase.h"

#define PLUGIN_NAME "Plugin Template"
#define PLUGIN_VERSION_MAJOR 1
#define PLUGIN_VERSION_MINOR 0

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)

#define PLUGIN_VERSION "v" STR(PLUGIN_VERSION_MAJOR) "." STR(PLUGIN_VERSION_MINOR)
#define PLUGIN_DESC PLUGIN_NAME " " PLUGIN_VERSION
#define PLUGIN_PREFIX "[" PLUGIN_NAME "] "

class Plugin : public IServerPluginCallbacks
{
public:
	Plugin();
	~Plugin();

	virtual bool Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory);
	virtual void Unload(void);
	virtual void Pause(void);
	virtual void UnPause(void);
	virtual const char *GetPluginDescription(void);
	virtual void LevelInit(char const *pMapName);
	virtual void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax);
	virtual void GameFrame(bool simulating);
	virtual void LevelShutdown(void);
	virtual void ClientActive(edict_t *pEntity);
	virtual void ClientDisconnect(edict_t *pEntity);
	virtual void ClientPutInServer(edict_t *pEntity, char const *playername);
	virtual void SetCommandClient(int index);
	virtual void ClientSettingsChanged(edict_t *pEdict);
	virtual PLUGIN_RESULT ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen);
	virtual PLUGIN_RESULT ClientCommand(edict_t *pEntity, const CCommand &args);
	virtual PLUGIN_RESULT NetworkIDValidated(const char *pszUserName, const char *pszNetworkID);
	virtual void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue);
	virtual void OnEdictAllocated(edict_t *edict);
	virtual void OnEdictFreed(const edict_t *edict);
};
