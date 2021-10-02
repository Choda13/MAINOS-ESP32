#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace TypeConversions
{
	static std::string int_to_string(int value);
	template <typename T>
	static std::string byte_to_hex(T val);
	template <typename T>
	static std::vector<uint8_t> type_to_bytes(T value);
	template <typename T>
	static T bytes_to_type(std::vector<uint8_t> bytes, bool ignoreSize = true);
	template <typename T>
	static T ExtractType(std::vector<uint8_t> &bytes, bool ignoreSize = true);

	static std::string int_to_string(int value)
	{
		std::stringstream s;
		s << value;
		return s.str();
	}
	template <typename T>
	static std::string byte_to_hex(T val)
	{
		std::string result = "";
		std::vector<uint8_t> bytes = type_to_bytes<T>(val);
		char const hex_chars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		for (auto it = bytes.begin(); it != bytes.end(); ++it)
		{
			char const byte = *it;
			result += hex_chars[(byte & 0xF0) >> 4];
			result += hex_chars[(byte & 0x0F) >> 0];
		}
		return result;
	}
	template <typename T>
	static std::vector<uint8_t> type_to_bytes(T value)
	{
		std::vector<uint8_t> result(sizeof(T));
		std::copy(reinterpret_cast<uint8_t *>(&value), reinterpret_cast<uint8_t *>(&value) + sizeof(T), result.data());
		return result;
	}
	template <typename T>
	static T bytes_to_type(std::vector<uint8_t> bytes, bool ignoreSize)
	{
		T value;
		std::copy(bytes.data(), bytes.data() + sizeof(T), reinterpret_cast<uint8_t *>(&value));
		//if (!ignoreSize && sizeof(T) != bytes.size())
		//Serial print "Exception at bytes_to_type(std::vector<uint8_t>bytes): bytes size doesnt equal the size of type T"
		return value;
	}
	template <typename T>
	static T ExtractType(std::vector<uint8_t> &bytes, bool ignoreSize)
	{
		auto value = bytes_to_type<T>(bytes);
		for(int i=0; i<sizeof(T); i++)
			bytes.erase(bytes.begin());
		return value;
	}
}
