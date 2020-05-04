#ifndef __LOGGER_H__
#define __LOGGER_H__
#include <iostream>
#define LOGGER_WARN(str) do{ \
		std::cout<<"Warning: " << (str) << std::endl; \
	} \
	while(0) \

#define LOGGER_ERROR(str) do{ \
		std::cout << "Error: " << (str) << std::endl; \
	} \
	while(0) \

#endif
