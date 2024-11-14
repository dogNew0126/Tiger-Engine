#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <string>

namespace tiger {
	class FileUtils {
	public:
		static std::string readFile(const char* filepath);
	};
}