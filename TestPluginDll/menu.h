#pragma once
#include "include/plugin_definitions.h"
#include <cstdlib>
#include <cstring>
#include <list>
#include <utility>

#ifdef _WIN32
#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
#define snprintf sprintf_s
#else
#define _strcpy(dest, destSize, src) { strncpy(dest, src, destSize-1); (dest)[destSize-1] = '\0'; }
#endif

#define PLUGIN_MENU_BUFSZ 128

enum PluginMenuType
{
  PLUGIN_MENU_TYPE_GLOBAL = 0,
  PLUGIN_MENU_TYPE_CHANNEL,
  PLUGIN_MENU_TYPE_CLIENT
};

/**
 * \brief Structure of a clickable menu-item in TeamSpeak.
 * Do not change the names!
 */
struct PluginMenuItem {
  enum PluginMenuType type;
  int id;
  char text[PLUGIN_MENU_BUFSZ];
  char icon[PLUGIN_MENU_BUFSZ];
};

class MenuItem
{
public:
  static std::list<MenuItem> menuItems;

  static uint16_t getCount()
  {
    return elementCount;
  }

  static void getMenuItems( struct PluginMenuItem*** aMenuItems );

  explicit MenuItem(PluginMenuType menuType, std::string name, std::string resourcePath) :
    id(elementCount++), menuType(menuType), name(std::move(name)), resourcePath(std::move(resourcePath))
  {
    menuItems.push_back(*this);
  }

  // Resource-Paths are not always needed, std::strings are automatically initialized with "", which is (maybe) perfect for our use case
  explicit MenuItem(PluginMenuType menuType, std::string name) :
    id(elementCount++), menuType(menuType), name(std::move(name))
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
  static uint16_t elementCount;

  uint16_t id{ };
  PluginMenuType menuType;
  std::string name;
  std::string resourcePath;
};