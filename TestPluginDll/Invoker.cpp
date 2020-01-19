#include "stdafx.h"
#include "Invoker.h"
#include "include/teamspeak/public_errors.h"
#include "Logger.h"
#include <sstream>

bool Invoker::Channel::setName(uint64 serverConnectionHandlerID, uint64 channelID, const std::string
  & value)
{
  return setVariableAsString(serverConnectionHandlerID, channelID, CHANNEL_NAME, value);
}

bool Invoker::Channel::setTopic(uint64 serverConnectionHandlerID, uint64 channelID, const std::string
  & value)
{
  return setVariableAsString(serverConnectionHandlerID, channelID, CHANNEL_TOPIC, value);
}

bool Invoker::Channel::setPassword(uint64 serverConnectionHandlerID, uint64 channelID, const std::string
  & value)
{
  return setVariableAsString(serverConnectionHandlerID, channelID, CHANNEL_PASSWORD, value);
}

bool Invoker::Channel::setCodecQuality(uint64 serverConnectionHandlerID, uint64 channelID, int value)
{
  // Quality of codec must be between 0-10
  if(value < 0 || value > 10)
  {
    return false;
  }

  return setVariableAsInt(serverConnectionHandlerID, channelID, CHANNEL_CODEC_QUALITY, value);
}

bool Invoker::Channel::setCodec( uint64 serverConnectionHandlerID, uint64 channelID, CodecType codecType )
{
  return setVariableAsInt( serverConnectionHandlerID, channelID, CHANNEL_CODEC, codecType );
}

bool Invoker::Channel::applyAllChanges(uint64 serverConnectionHandlerID, uint64 channelID)
{
  // ReturnCode wasn't working with char* or char-array and isn't documented, so we just don't use it
  const auto ts3Error = ts3Functions.flushChannelUpdates(serverConnectionHandlerID, channelID, nullptr);

  if (ts3Error != ERROR_ok)
  {
    reportError(ts3Error);
    return false;
  }
  return true;
}

bool Invoker::Channel::setVariableAsString(uint64 serverConnectionHandlerID, uint64 channelID, ChannelProperties flag, const std::string
  & value)
{
  const auto ts3Error = ts3Functions.setChannelVariableAsString(serverConnectionHandlerID, channelID, flag, value.c_str());

  if (ts3Error != ERROR_ok)
  {
    reportError(ts3Error);
    return false;
  }
  return true;
}

bool Invoker::Channel::setVariableAsInt(uint64 serverConnectionHandlerID, uint64 channelID, ChannelProperties flag, int value)
{
  const auto ts3Error = ts3Functions.setChannelVariableAsInt(serverConnectionHandlerID, channelID, flag, value);

  if (ts3Error != ERROR_ok)
  {
    reportError(ts3Error);
    return false;
  }
  return true;
}

void Invoker::reportError(const unsigned ts3Error)
{
  char* generatedErrorMessage = nullptr;
  ts3Functions.getErrorMessage(ts3Error, &generatedErrorMessage);

  std::stringstream errorMessage;
  errorMessage << "An error occured: ";
  errorMessage << std::hex << ts3Error << std::dec;
  errorMessage << " " << generatedErrorMessage;

  Logger::error(errorMessage.str());
}

