#pragma once

#define CLIENT_DLL
#include "cbase.h"

#define PLUGIN_NAME "Plugin Template"
#define PLUGIN_VERSION_MAJOR 1
#define PLUGIN_VERSION_MINOR 0
#define PLUGIN_VERSION_PATCH 0

#define QUOTE(name) #name
#define STR(macro) QUOTE(macro)

#define PLUGIN_VERSION "v" STR(PLUGIN_VERSION_MAJOR) "." STR(PLUGIN_VERSION_MINOR) "." STR(PLUGIN_VERSION_PATCH)
#define PLUGIN_DESC PLUGIN_NAME " " PLUGIN_VERSION
#define PLUGIN_PREFIX "[" PLUGIN_NAME "] "
