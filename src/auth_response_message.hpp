/*
  Copyright 2014 DataStax

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#ifndef __CASS_AUTH_RESPONSE_MESSAGE_HPP_INCLUDED__
#define __CASS_AUTH_RESPONSE_MESSAGE_HPP_INCLUDED__

#include "message_body.hpp"
#include "serialization.hpp"

namespace cass {

struct AuthResponseMessage : public MessageBody {
  AuthResponseMessage()
      : MessageBody(CQL_OPCODE_AUTH_RESPONSE) {}

  bool consume(char* buffer, size_t size) { return true; }

  bool prepare(size_t reserved, char** output, size_t& size) {
  size = reserved + sizeof(int32_t);

  size += strlen(username_);
  size += strlen(password_);
  size += 1;
  size += 1;

  *output = new char[size];

  char* buffer = *output+reserved;
  buffer = encode_credentials(buffer, username_, password_);

  return true;
  }

  const char* username_;
  const char* password_;
};

} // namespace cass

#endif