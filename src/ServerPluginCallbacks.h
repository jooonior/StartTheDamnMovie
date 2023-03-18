#pragma once

#include <engine/iserverplugin.h>

/// <summary>
/// Implements default callbacks for the <see cref="IServerPluginCallbacks"/> interface.
/// </summary>
class ServerPluginCallbacks : public IServerPluginCallbacks
{
public:
	virtual void Pause(void) {};
	virtual void UnPause(void) {};
	virtual void LevelInit(char const *pMapName) {};
	virtual void ServerActivate(edict_t *pEdictList, int edictCount, int clientMax) {};
	virtual void GameFrame(bool simulating) {};
	virtual void LevelShutdown(void) {};
	virtual void ClientActive(edict_t *pEntity) {};
	virtual void ClientDisconnect(edict_t *pEntity) {};
	virtual void ClientPutInServer(edict_t *pEntity, char const *playername) {};
	virtual void SetCommandClient(int index) {};
	virtual void ClientSettingsChanged(edict_t *pEdict) {};
	virtual PLUGIN_RESULT ClientConnect(bool *bAllowConnect, edict_t *pEntity, const char *pszName, const char *pszAddress, char *reject, int maxrejectlen) { return PLUGIN_CONTINUE; };
	virtual PLUGIN_RESULT ClientCommand(edict_t *pEntity, const CCommand &args) { return PLUGIN_CONTINUE; };
	virtual PLUGIN_RESULT NetworkIDValidated(const char *pszUserName, const char *pszNetworkID) { return PLUGIN_CONTINUE; };
	virtual void OnQueryCvarValueFinished(QueryCvarCookie_t iCookie, edict_t *pPlayerEntity, EQueryCvarValueStatus eStatus, const char *pCvarName, const char *pCvarValue) {};
	virtual void OnEdictAllocated(edict_t *edict) {};
	virtual void OnEdictFreed(const edict_t *edict) {};
};
