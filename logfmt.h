#ifndef LOGFMT
#define LOGFMT

#include <string>
#include <unordered_map>

namespace logfmt {
	void parse(const std::string& data, std::unordered_map<std::string, std::string>& m);
}

#endif
