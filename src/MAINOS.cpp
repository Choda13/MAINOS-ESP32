#include "../include/MAINOS.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

int mainos_init() {
	CommandService = commserv::CommandHandler();
	CommandService.RegisterAPI(new api::API());
	return codes::Success;
}

template< typename T >
std::string byte_to_hex(T i)
{
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(sizeof(T) * 2)
		<< std::hex << (int)i;
	return stream.str();
}

template<typename T>
T bytes_to_type(std::vector<uint8_t>bytes, bool ignoreSize) {
	T value;
	std::copy(bytes.data(), bytes.data() + sizeof(T), reinterpret_cast<uint8_t*>(&value));
	//if (!ignoreSize && sizeof(T) != bytes.size())
		//Serial print "Exception at bytes_to_type(std::vector<uint8_t>bytes): bytes size doesnt equal the size of type T"
	return value;
}

template<typename T>
std::vector<uint8_t> type_to_bytes(T value) {
	std::vector<uint8_t> result(sizeof(T));
	std::copy(reinterpret_cast<uint8_t*>(&value), reinterpret_cast<uint8_t*>(&value) + sizeof(T), result.data());
	return result;
}