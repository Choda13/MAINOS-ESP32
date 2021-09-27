#pragma once
#include <iostream>
#include <cstdint>
#include <vector>

//TODO: MAKE FLEXIBLE AND EASILY CHANGING COMMAND HEADER SIZE
//TODO: Make header parser
//TODO: Move type_to_bytes and bytes_to_type somewhere else

class Command {
public:
	static const int API_ID_SIZE = sizeof(uint8_t);
	static const int COMMAND_ID_SIZE = sizeof(uint8_t);
	static const int ARGS_SIZE = sizeof(int);
	static const int HEADER_SIZE = API_ID_SIZE + COMMAND_ID_SIZE + ARGS_SIZE;

	bool isCommandValid = true;

	uint8_t ApiID;
	uint8_t CommandID;
	std::vector<uint8_t> Arguments;

	Command(std::vector<uint8_t> bytes);
	Command(uint8_t ApiID, uint8_t CommandID, std::vector<uint8_t>Arguments);

	//Converts object to its string representation
	std::string toString();

	//Gets size of command in bytes
	int size();

	//Convert object to its byte array equivalent
	std::vector<uint8_t> Encode();
	static std::vector<uint8_t> Encode(Command command);

	//Convert byte array to class object equivalent if possible
	static Command Decode(std::vector<uint8_t> data);
};