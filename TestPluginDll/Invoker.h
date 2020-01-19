#pragma once
#include "include/teamspeak/public_definitions.h"
#include <xstring>

class Invoker
{
public:
  class Channel
  {
  public:
    static bool setName(uint64 serverConnectionHandlerID, uint64 channelID, const std::string& value);
    static bool setTopic(uint64 serverConnectionHandlerID, uint64 channelID, const std::string& value);
    static bool setPassword(uint64 serverConnectionHandlerID, uint64 channelID, const std::string& value);
    static bool setCodecQuality(uint64 serverConnectionHandlerID, uint64 channelID, int value);
    static bool setCodec(uint64 serverConnectionHandlerID, uint64 channelID, CodecType codecType);
    static bool applyAllChanges(uint64 serverConnectionHandlerID, uint64 channelID);

  private:
    static bool setVariableAsString(uint64 serverConnectionHandlerID, uint64 channelID, ChannelProperties flag, const std::string& value);
    static bool setVariableAsInt(uint64 serverConnectionHandlerID, uint64 channelID, ChannelProperties flag, int value);
  };

  static void reportError(unsigned ts3Error);
};
