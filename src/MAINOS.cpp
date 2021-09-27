#include "../include/MAINOS.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

int mainos_init() {
	CommandService = commserv::CommandHandler();
	CommandService.RegisterAPI(api::API());
	return codes::Success;
}