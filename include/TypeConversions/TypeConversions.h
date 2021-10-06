#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <ArduinoJson.h>
#include "CommandHandler/Command.h"

namespace TypeConversions
{
	//Declaration
	template <typename T>static std::string byte2hex(T val);
	template <typename T>static std::vector<uint8_t> type2bytes(T value);
	template <typename T>static T bytes2type(std::vector<uint8_t> bytes, bool ignoreSize = true);
	template <typename T>static T ExtractType(std::vector<uint8_t> &bytes, bool ignoreSize = true);
	static std::string int2string(int value);
	static void hex2bin(const char *src, uint8_t *target);
	static int char2int(char input);
	static bool validateHex(const char *data);
	static Command jsonObject2Command(JsonObject jsonObject);
	static bool validateObject(JsonObject &obj, std::vector<std::string> keysToValidate);

	//Definition
	template <typename T>static std::string byte2hex(T val)
	{
		std::string result = "";
		std::vector<uint8_t> bytes = type2bytes<T>(val);
		char const hex_chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		for (auto it = bytes.begin(); it != bytes.end(); ++it)
		{
			char const byte = *it;
			result += hex_chars[(byte & 0xF0) >> 4];
			result += hex_chars[(byte & 0x0F) >> 0];
		}
		return result;
	}
	template <typename T>static std::vector<uint8_t> type2bytes(T value)
	{
		std::vector<uint8_t> result(sizeof(T));
		std::copy(reinterpret_cast<uint8_t *>(&value), reinterpret_cast<uint8_t *>(&value) + sizeof(T), result.data());
		return result;
	}
	template <typename T>static T bytes2type(std::vector<uint8_t> bytes, bool ignoreSize)
	{
		T value;
		std::copy(bytes.data(), bytes.data() + sizeof(T), reinterpret_cast<uint8_t *>(&value));
		//if (!ignoreSize && sizeof(T) != bytes.size())
		//Serial print "Exception at bytes2type(std::vector<uint8_t>bytes): bytes size doesnt equal the size of type T"
		return value;
	}
	template <typename T>static T ExtractType(std::vector<uint8_t> &bytes, bool ignoreSize)
	{
		auto value = bytes2type<T>(bytes);
		for (int i = 0; i < sizeof(T); i++)
			bytes.erase(bytes.begin());
		return value;
	}
	static std::string int2string(int value)
	{
		std::stringstream s;
		s << value;
		return s.str();
	}
	static void hex2bin(const char *src, uint8_t *target)
	{
		while (*src && src[1])
		{
			*(target++) = char2int(*src) * 16 + char2int(src[1]);
			src += 2;
		}
	}
	static int char2int(char input)
	{
		if (input >= '0' && input <= '9')
			return input - '0';
		if (input >= 'A' && input <= 'F')
			return input - 'A' + 10;
		if (input >= 'a' && input <= 'f')
			return input - 'a' + 10;
		return -1;
	}
	static bool validateHex(const char *data)
	{
		while (*data)
		{
			if (char2int(data[0]) == -1)
				return false;
			data++;
		}
		return true;
	}
	static Command jsonObject2Command(JsonObject jsonObject)
	{
		uint8_t API_ID = jsonObject["api"];
		uint8_t CMD_ID = jsonObject["command"];
		std::string args = jsonObject["args"];
		std::vector<uint8_t> bytes;

		if (!args.empty())
		{
			if (args.length() % 2 || !validateHex(args.c_str()))
				Serial.println("Vrednost parametara mora biti u hex formati majmune glupi");
			else
			{
				bytes.resize(args.length() / 2);
				hex2bin(args.c_str(), bytes.data());
				Serial.println("Uspesno parsirani argumenti");
			}
		}
		Serial.println(API_ID);
		Serial.println(CMD_ID);

		return Command(API_ID, CMD_ID, bytes);
	}
	static bool validateObject(JsonObject &obj, std::vector<std::string> keysToValidate)
	{
		for (auto &&i : keysToValidate)
			if (!obj.containsKey(i))
				return false;
		return true;
	}
}
