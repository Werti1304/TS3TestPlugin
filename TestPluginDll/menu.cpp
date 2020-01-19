#include "stdafx.h"
#include "menu.h"
#include "include/teamspeak/public_definitions.h"
#include "Invoker.h"

// Static members have to be declared in a .cpp file
std::list<MenuItem> MenuItem::menuItems;

MenuItem item1("Hi", Item1, Global);
MenuItem item2("Hallo", Item2, Global);
MenuItem item3("Halloooooooooo?", Item3, Global);
MenuItem menuItemChannelChangeCodecToNormal("Voice Codec", ChannelChangeCodesToNormal, Channel);
MenuItem menuItemChannelChangeCodecToMusic("Music  Codec", ChannelChangeCodecToMusic, Channel);

void MenuItem::initMenus( struct PluginMenuItem*** aMenuItems, char** menuIcon )
{
  const auto allocateSize = menuItems.size() + 1;

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

  // Specifies menu icon for sub and main menus of the plugin
  *menuIcon = static_cast<char*>(malloc( PLUGIN_MENU_BUFSZ * sizeof( char ) ));
  _strcpy(*menuIcon, PLUGIN_MENU_BUFSZ, "t.png");
}

void MenuItem::menuItemClickEventGlobal(uint64 serverConnectionHandlerID, MenuItemID menuItemID)
{
  switch (menuItemID)
  {
  case Item1: break;
  case Item2: break;
  case Item3: break;
  default: ;
  }
}

void MenuItem::menuItemClickEventChannel(uint64 serverConnectionHandlerID, MenuItemID menuItemID, uint64 channelID)
{
  switch (menuItemID)
  {
  case ChannelChangeCodesToNormal:
    Invoker::Channel::setCodec(serverConnectionHandlerID, channelID, CODEC_OPUS_VOICE );
    Invoker::Channel::setCodecQuality(serverConnectionHandlerID, channelID, 6 );
    Invoker::Channel::setTopic(serverConnectionHandlerID, channelID, "Automatically configured Voice-Channel");
    Invoker::Channel::applyAllChanges(serverConnectionHandlerID, channelID);
    break;
  case ChannelChangeCodecToMusic: 
    Invoker::Channel::setCodec(serverConnectionHandlerID, channelID, CODEC_OPUS_MUSIC );
    Invoker::Channel::setCodecQuality(serverConnectionHandlerID, channelID, 10);
    Invoker::Channel::setTopic(serverConnectionHandlerID, channelID, "Automatically configured Music-Channel");
    Invoker::Channel::applyAllChanges(serverConnectionHandlerID, channelID);
    break;
  default: ;
  }
}

void MenuItem::menuItemClickEventClient(uint64 serverConnectionHandlerID, MenuItemID menuItemID, uint64 clientID)
{
  switch (menuItemID)
  {
  default: ;
  }
}

void MenuItem::onMenuItemEvent(uint64 serverConnectionHandlerID, enum PluginMenuType type, int menuItemID, uint64 selectedItemID)
{
  ts3Functions.logMessage("Hi2", LogLevel_ERROR, "", serverConnectionHandlerID);

  switch (type) {
  case Global: 
    menuItemClickEventGlobal(serverConnectionHandlerID, static_cast<MenuItemID>(menuItemID));
    break;
  case Channel: 
    menuItemClickEventChannel(serverConnectionHandlerID, static_cast<MenuItemID>(menuItemID), selectedItemID);
    break;
  case Client: 
    menuItemClickEventClient(serverConnectionHandlerID, static_cast<MenuItemID>(menuItemID), selectedItemID);
    break;
  default:;
  }
}
