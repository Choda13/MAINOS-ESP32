#include "../include/MAINOS.h"

int mainos_init() {
	CommandService = commserv::CommandHandler();
	CommandService.RegisterAPI(api::API());
	return codes::Success;
}