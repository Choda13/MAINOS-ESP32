#pragma once
#include "API/API.h"
#include "StatusCodes.h"
#include "CommandHandler/Command.h"
#include "CommandHandler/CommandHandler.h"

int mainos_init();
static commserv::CommandHandler CommandService;
template< typename T > static std::string byte_to_hex(T i);
template <typename T>  static std::vector<uint8_t> type_to_bytes(T value);
template <typename T>  static T bytes_to_type(std::vector<uint8_t>bytes, bool ignoreSize=true);