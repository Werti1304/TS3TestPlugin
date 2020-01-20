#pragma once
#include <list>
#include <utility>
#include "include/teamspeak/public_definitions.h"

#ifdef _WIN32
#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
#define snprintf sprintf_s
#else
#define _strcpy(dest, destSize, src) { strncpy(dest, src, destSize-1); (dest)[destSize-1] = '\0'; }
#endif

#define PLUGIN_MENU_BUFSZ 128

enum PluginMenuType
{
  Global = 0,
  Channel,
  Client
};

/**
 * \brief Structure of a clickable menu-item in TeamSpeak.
 * Do not change the names!
 */
struct PluginMenuItem 
{
  enum PluginMenuType type;
  int id;
  char text[PLUGIN_MENU_BUFSZ];
  char icon[PLUGIN_MENU_BUFSZ];
};

enum MenuItemID
{
  GlobalItem1,
  GlobalItem2,
  GlobalItem3,
  ChannelChangeCodesToNormal,
  ChannelChangeCodecToMusic,
  ClientFakeBan
};

class MenuItem
{
public:
  static std::list<MenuItem> menuItems;

  static void initMenus( PluginMenuItem*** aMenuItems, char** menuIcon );

  static void onMenuItemEvent(uint64 serverConnectionHandlerID, enum PluginMenuType type, int menuItemID, uint64 selectedItemID);
  static void menuItemClickEventGlobal(uint64 serverConnectionHandlerID, MenuItemID menuItemID);
  static void menuItemClickEventChannel(uint64 serverConnectionHandlerID, MenuItemID menuItemID, uint64 channelID);
  static void menuItemClickEventClient(uint64 serverConnectionHandlerID, MenuItemID menuItemID, uint64 clientID);

  explicit MenuItem(std::string name, MenuItemID menuItemId, PluginMenuType menuType, std::string resourcePath) :
    id(menuItemId), menuType(menuType), name(std::move(name)), resourcePath(std::move(resourcePath))
  {
    menuItems.push_back(*this);
  }

  // Resource-Paths are not always needed, std::strings are automatically initialized with "", which is (maybe) perfect for our use case
  explicit MenuItem(std::string name, MenuItemID menuItemId, PluginMenuType menuType) :
    id(menuItemId), menuType(menuType), name(std::move(name))
  {
    menuItems.push_back(*this);
  }

  uint16_t getId() const
  {
    return id;
  }
  __declspec(property(get = getId)) uint16_t Id;

  PluginMenuType getMenuType() const
  {
    return menuType;
  }
  __declspec(property(get = getMenuType)) PluginMenuType MenuType;

  std::string getName() const
  {
    return name;
  }
  __declspec(property(get = getName)) std::string Name;

  std::string getResourcePath() const
  {
    return resourcePath;
  }
  __declspec(property(get = getResourcePath)) std::string IconPath;

private:
  uint16_t id{ };
  PluginMenuType menuType;
  std::string name;
  std::string resourcePath;
};

