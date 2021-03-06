/*	MIT License
 *
 *	Copyright(c) 2020 Pablo Rodriguez Nava, @pablintino
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files(the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions :
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */


#ifndef TEST_BENCH_OPTIONS_H
#define TEST_BENCH_OPTIONS_H


#include <memory>
#include <string>

#include "CanTypes.h"

class TestBenchOptions
{
public:

	static std::unique_ptr<TestBenchOptions> parse(int argc, char** argv);
	std::string interface_type();
    std::string test_name();
	unsigned int interface_channel();
	CanBitrates baudrate();
	std::string command();

private:
	std::string interface_type_ = "";
	unsigned int interface_channel_ = 0;
	std::string test_name_ = "";
	CanBitrates baudrate_ = CanBitrates::CAN500K;
	std::string command_ = "";
};

#endif
