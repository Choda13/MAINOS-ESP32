#pragma once
#include <vector>
#include "../API/API.h"

namespace apireg {
	class APIRegistar {
	public:
		std::vector<api::API> APIList;
		APIRegistar();
	};
}