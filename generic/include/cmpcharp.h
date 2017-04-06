#ifndef CMPCHARP_H
#define CMPCHARP_H

#include <cstring>

struct cmpcharp {
	bool operator()(char const* a, char const* b) const {
		return std::strcmp(a, b) < 0;
	}
};

#endif
