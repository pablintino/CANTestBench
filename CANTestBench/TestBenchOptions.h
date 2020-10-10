#pragma once
#include <memory>
#include <string>

#include "../CANBusInterface/CanTypes.h"

class TestBenchOptions
{
public:

	static std::unique_ptr<TestBenchOptions> parse(int argc, char** argv);
	std::string interface_type();
	unsigned int interface_channel();
	CanBitrates baudrate();
	
private:
	std::string interface_type_ = "";
	unsigned int interface_channel_ = 0;
	CanBitrates baudrate_ = CanBitrates::CAN500K;
};
