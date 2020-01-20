/*
 * TeamSpeak 3 demo plugin
 *
 * Copyright (c) TeamSpeak Systems GmbH
 */
#include "stdafx.h"
#include "plugin.h"
#include <cstdlib>
#include <cstring>
#include "menu.h"
#include <thread>

#ifdef _WIN32
#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
#define snprintf sprintf_s
#else
#define _strcpy(dest, destSize, src) { strncpy(dest, src, destSize-1); (dest)[destSize-1] = '\0'; }
#endif

#define PLUGIN_API_VERSION 23

#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

static char* pluginID = nullptr;

/* Unique name identifying this plugin */
const char* ts3plugin_name()
{
  return "Werti Plugin 420 - Debug";
}

/* Plugin version */
const char* ts3plugin_version()
{
  return "0.0";
}

/* Plugin API version. Must be the same as the clients API major version, else the plugin fails to load. */
int ts3plugin_apiVersion()
{
  return PLUGIN_API_VERSION;
}

/* Plugin author */
const char* ts3plugin_author()
{
  /* If you want to use wchar_t, see ts3plugin_name() on how to use */
  return "TeamSpeak Systems GmbH";
}

/* Plugin description */
const char* ts3plugin_description()
{
  /* If you want to use wchar_t, see ts3plugin_name() on how to use */
  return "This plugin demonstrates the TeamSpeak 3 client plugin architecture.";
}

/* Set TeamSpeak 3 callback functions */
void ts3plugin_setFunctionPointers( const struct TS3Functions funcs )
{
  ts3Functions = funcs;
}

int ts3plugin_init()
{
  char appPath[PATH_BUFSIZE];
  char resourcesPath[PATH_BUFSIZE];
  char configPath[PATH_BUFSIZE];
  char pluginPath[PATH_BUFSIZE];

  /* Example on how to query application, resources and configuration paths from client */
  /* Note: Console client returns empty string for app and resources path */
  ts3Functions.getAppPath(appPath, PATH_BUFSIZE);
  ts3Functions.getResourcesPath(resourcesPath, PATH_BUFSIZE);
  ts3Functions.getConfigPath(configPath, PATH_BUFSIZE);
  ts3Functions.getPluginPath(pluginPath, PATH_BUFSIZE, pluginID);

  ts3Functions.logMessage("oeuf", LogLevel_ERROR, "", 0);

  return 0;  /* 0 = success, 1 = failure, -2 = failure but client will not show a "failed to load" warning */
/* -2 is a very special case and should only be used if a plugin displays a dialog (e.g. overlay) asking the user to disable
 * the plugin again, avoiding the show another dialog by the client telling the user the plugin failed to load.
 * For normal case, if a plugin really failed to load because of an error, the correct return value is 1. */
}

/* Custom code called right before the plugin is unloaded */
void ts3plugin_shutdown() {

  /*
   * Note:
   * If your plugin implements a settings dialog, it must be closed and deleted here, else the
   * TeamSpeak client will most likely crash (DLL removed but dialog from DLL code still open).
   */

   /* Free pluginID if we registered it */
  if (pluginID) {
    free(pluginID);
    pluginID = NULL;
  }
}

/*
 * If the plugin wants to use error return codes, plugin commands, hotkeys or menu items, it needs to register a command ID. This function will be
 * automatically called after the plugin was initialized. This function is optional. If you don't use these features, this function can be omitted.
 * Note the passed pluginID parameter is no longer valid after calling this function, so you must copy it and store it in the plugin.
 */
void ts3plugin_registerPluginID(const char* id) 
{
  const size_t sz = strlen(id) + 1;
  pluginID = (char*)malloc(sz * sizeof(char));
  _strcpy(pluginID, sz, id);  /* The id buffer will invalidate after exiting this function */
}

/* Required to release the memory for parameter "data" allocated in ts3plugin_infoData and ts3plugin_initMenus */
void ts3plugin_freeMemory(void* data) 
{
  free(data);
}

/*
* Initialize plugin menus.
* This function is called after ts3plugin_init and ts3plugin_registerPluginID.A pluginID is required for plugin menus to work.
* Both ts3plugin_registerPluginID and ts3plugin_freeMemory must be implemented to use menus.
* If plugin menus are not used by a plugin, do not implement this function or return NULL.
*/
void ts3plugin_initMenus(struct PluginMenuItem*** menuItems, char** menuIcon) 
{
  ts3Functions.logMessage("Hi", LogLevel_ERROR, "", 0);

  MenuItem::initMenus(menuItems, menuIcon);
}

void ts3plugin_onMenuItemEvent( uint64 serverConnectionHandlerID, PluginMenuType type, int menuItemID,
  uint64 selectedItemID )
{
  ts3Functions.logMessage("Hi", LogLevel_ERROR, "", serverConnectionHandlerID);

  MenuItem::onMenuItemEvent(serverConnectionHandlerID, type, menuItemID, selectedItemID);
}

void ts3plugin_onTalkStatusChangeEvent( uint64 serverConnectionHandlerID, int status, int isReceivedWhisper,
  anyID clientID )
{
  uint64 channelID;
  anyID myClientID;

  char* channelName[256];

  ts3Functions.getChannelOfClient(serverConnectionHandlerID, clientID, &channelID);

  ts3Functions.getChannelVariableAsString(serverConnectionHandlerID, channelID, CHANNEL_NAME, channelName);

  ts3Functions.getClientID(serverConnectionHandlerID, &myClientID);

  ts3Functions.requestClientPoke(serverConnectionHandlerID, myClientID, *channelName, nullptr);
}
