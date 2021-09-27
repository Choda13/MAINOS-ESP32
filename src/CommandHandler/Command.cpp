#include "../../include/MAINOS.h"
#include "../../include/CommandHandler/Command.h"
#include "../../include/TypeConversions/TypeConversions.h"
#include <iostream>
using namespace TypeConversions;
Command::Command(std::vector<uint8_t> bytes) {
	*this = Command::Decode(bytes);
}

Command::Command(uint8_t ApiID, uint8_t CommandID, std::vector<uint8_t>Arguments) {
	this->ApiID = ApiID;
	this->CommandID = CommandID;
	this->Arguments = Arguments;
}

std::vector<uint8_t> Command::Encode() {
	return Command::Encode(*this);
}

std::vector<uint8_t> Command::Encode(Command command) {
	int argsSize = command.Arguments.size();
	std::vector<uint8_t> Result;
	std::vector<uint8_t> sizeInBytes = type_to_bytes(argsSize);
	Result.push_back(command.ApiID);
	Result.push_back(command.CommandID);
	Result.insert(Result.end(), sizeInBytes.begin(), sizeInBytes.end());
	Result.insert(Result.end(), command.Arguments.begin(), command.Arguments.end());

	return Result;
}

Command Command::Decode(std::vector<uint8_t> data) {
	int dataSize = data.size();
	int position = 0;

	//Creates zero initialized Command with isCommandValid flag set to zero if there is not enough data to create object
	if (dataSize < HEADER_SIZE) {
		auto com = Command(0, 0, std::vector<uint8_t>());
		com.isCommandValid = false;
		return com;
	}
	
	uint8_t ApiID = bytes_to_type<uint8_t>(std::vector<uint8_t>(data.begin() + position, data.begin() + position + sizeof(ApiID)));
	position += sizeof(ApiID);

	uint8_t CommandID = bytes_to_type<uint8_t>(std::vector<uint8_t>(data.begin() + position, data.begin() + position + sizeof(CommandID)));
	position += sizeof(CommandID);

	unsigned int ArgsSize = bytes_to_type<uint8_t>(std::vector<uint8_t>(data.begin() + position, data.begin() + position + sizeof(ArgsSize)));
	position += sizeof(ArgsSize);

	//Creates zero initialized Command with isCommandValid flag set to zero if there is not enough data to create object
	if (data.size() - HEADER_SIZE < ArgsSize) {
		auto com = Command(0, 0, std::vector<uint8_t>());
		com.isCommandValid = false;
		return com;
	}
		
	std::vector<uint8_t> Arguments;
	if (ArgsSize)
		Arguments.insert(Arguments.end(), data.begin() + position, data.begin() + position + ArgsSize);

	return Command(ApiID, CommandID, Arguments);
}

std::string Command::toString() {
	std::string result = "";
	std::string hexvalues = "";
	
	result += "API ID: " + int_to_string(ApiID) + "\n";
	result += "Command ID: " + int_to_string(CommandID) + "\n";
	result += "Size of args: " + int_to_string(Arguments.size()) + "\n";
	result += "Hexadecimal representaion of arguments:\n";
	
	for (unsigned int i = 0; i < Arguments.size(); i++) {
		hexvalues += byte_to_hex<uint8_t>(Arguments.at(i));
		switch (i % 8) {
			case 7:hexvalues += '\n'; break;
			case 3:	hexvalues += "  "; break;
			default:hexvalues += ' ';
		}
	}
	return result + hexvalues;
}

int Command::size() {
	return HEADER_SIZE + this->Arguments.size();
}