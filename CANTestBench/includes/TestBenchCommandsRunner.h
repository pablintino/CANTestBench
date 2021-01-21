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


#ifndef TESTBENCHCOMMANDSRUNNER_H
#define TESTBENCHCOMMANDSRUNNER_H

#include <string>
#include <map>
#include <CanInterface.h>
#include "TestBenchCommandConstants.h"
#include "TestBenchOptions.h"

typedef int (*FuncType)(std::unique_ptr<TestBenchOptions> opts, std::unique_ptr<CanInterface> iface);

class TestBenchCommandsRunner {
    public:
        TestBenchCommandsRunner(void);
        int run(std::unique_ptr<TestBenchOptions> opts, std::unique_ptr<CanInterface> iface);
    private:
        static int list_channels_command(std::unique_ptr<TestBenchOptions>  opts, std::unique_ptr<CanInterface> iface);
        static int run_test_command(std::unique_ptr<TestBenchOptions>  opts, std::unique_ptr<CanInterface> iface);
        std::map<std::string, FuncType> commands_map;
};


#endif //TESTBENCHCOMMANDSRUNNER_H
