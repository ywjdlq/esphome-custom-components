/*
  CustomAudioFileSourceHTTPStream
  Connect to a HTTP based streaming service

  Copyright (C) 2017  Earle F. Philhower, III

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include <string>
#include <Arduino.h>
#include <HTTPClient.h>
#include "AudioFileSource.h"

namespace esphome {
namespace audio_player {

class CustomAudioFileSourceHTTPStream : public AudioFileSource {
  friend class AudioFileSourceICYStream;

 public:
  CustomAudioFileSourceHTTPStream();
  CustomAudioFileSourceHTTPStream(const char *url);
  virtual ~CustomAudioFileSourceHTTPStream() override;

  virtual bool open(const char *url) override;
  virtual uint32_t read(void *data, uint32_t len) override;
  virtual uint32_t readNonBlock(void *data, uint32_t len) override;
  virtual bool seek(int32_t pos, int dir) override;
  virtual bool close() override;
  virtual bool isOpen() override;
  virtual uint32_t getSize() override;
  virtual uint32_t getPos() override;
  bool SetReconnect(int tries, int delayms) {
    reconnectTries = tries;
    reconnectDelayMs = delayms;
    return true;
  }
  void useHTTP10() { http.useHTTP10(true); }
  std::string contentType() { return std::string(http.header("Content-Type").c_str()); }

  enum { STATUS_HTTPFAIL = 2, STATUS_DISCONNECTED, STATUS_RECONNECTING, STATUS_RECONNECTED, STATUS_NODATA };

 private:
  virtual uint32_t readInternal(void *data, uint32_t len, bool nonBlock);
  WiFiClient client;
  HTTPClient http;
  int pos;
  int size;
  int reconnectTries;
  int reconnectDelayMs;
  char saveURL[128];
  int chunked_size;
  bool chunked;
};

}  // namespace audio_player
}  // namespace esphome