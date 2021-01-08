
#ifndef TEST_BENCH_TEST_H
#define TEST_BENCH_TEST_H


#include <memory>

#include "CanInterfaceChannel.h"

class TestBenchTest
{
public:
	TestBenchTest(std::string name);
	std::string name(void);
	virtual ~TestBenchTest() {};
	virtual bool run(std::shared_ptr<CanInterfaceChannel> channel) = 0;
};

#endif
