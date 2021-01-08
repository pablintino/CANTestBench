#pragma once
#include <memory>

#include "../CANBusInterface/CanInterfaceChannel.h"

class TestBenchTest
{
public:
	TestBenchTest(std::string name);
	std::string name(void);
	virtual ~TestBenchTest() {};
	virtual bool run(std::shared_ptr<CanInterfaceChannel> channel) = 0;
};
