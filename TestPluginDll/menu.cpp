#include "menu.h"
#include <cassert>

// Static members have to be declared in a .cpp file
std::list<MenuItem> MenuItem::menuItems;
uint16_t MenuItem::elementCount = 0;

MenuItem item1(PLUGIN_MENU_TYPE_GLOBAL, "Hi");
MenuItem item2(PLUGIN_MENU_TYPE_GLOBAL, "Hallo");
MenuItem item3(PLUGIN_MENU_TYPE_GLOBAL, "Halloooooooooo?");

void MenuItem::getMenuItems( struct PluginMenuItem*** aMenuItems )
{
  const auto allocateSize = getCount() + 1;

  const auto menuItems = new struct PluginMenuItem*[allocateSize];
  
  auto i = 0;
  for (auto menuItem : MenuItem::menuItems)
  {
    auto menuItemStruct = new PluginMenuItem();
    menuItemStruct->type = menuItem.MenuType;
    menuItemStruct->id = menuItem.Id;
    _strcpy(menuItemStruct->text, PLUGIN_MENU_BUFSZ, menuItem.Name.c_str());
    _strcpy(menuItemStruct->icon, PLUGIN_MENU_BUFSZ, menuItem.IconPath.c_str());
    menuItems[i++] = menuItemStruct;
  }
  menuItems[i] = nullptr;

  *aMenuItems = menuItems;
}
