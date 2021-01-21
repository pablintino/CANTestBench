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


#include <ConsolePrinter.h>
#include <spdlog/spdlog.h>
#include <TestBenchTest.h>
#include <TestFactory.h>
#include "TestBenchCommandsRunner.h"
#include "TestBenchCommandConstants.h"
#include "CanTypes.h"

TestBenchCommandsRunner::TestBenchCommandsRunner(void) {
    commands_map[TEST_BENCH_COMMAND_LIST_CHANNELS] = list_channels_command;
    commands_map[TEST_BENCH_COMMAND_RUN_TEST] = run_test_command;
}

int TestBenchCommandsRunner::run(std::unique_ptr<TestBenchOptions> opts, std::unique_ptr<CanInterface> iface) {

    const std::map<std::string, FuncType>::iterator it = commands_map.find(opts->command());
    if (it != commands_map.end()) {
        return it->second(std::move(opts), std::move(iface));
    }
    return 0;
}

int TestBenchCommandsRunner::list_channels_command(const std::unique_ptr<TestBenchOptions> opts,
                                                   const std::unique_ptr<CanInterface> iface) {
    ConsolePrinter::PrintInterfaceChannels(iface->channels());
    return 0;
}

int
TestBenchCommandsRunner::run_test_command(const std::unique_ptr<TestBenchOptions> opts,
                                          const std::unique_ptr<CanInterface> iface) {
    std::shared_ptr<CanInterfaceChannel> chan = iface->get_channel(opts->interface_channel());
    spdlog::info("Selected CAN channel [channel_name: {}, is_virtual: {}]", chan->name(),
                 chan->vChannel());
    CanChannelError err = chan->configure(opts->baudrate());
    if (err != CanChannelError::NO_ERR) {
        return -1;
    }

    err = chan->connect();
    if (err != CanChannelError::NO_ERR) {
        return -1;
    }

    std::unique_ptr<TestBenchTest> test = TestFactory::get_test(opts->test_name());
    if (test->run(chan)) {
        spdlog::info("Test passed!!");
    } else {
        spdlog::error("Test KO!!");
    }

    err = chan->disconnect();
    if (err != CanChannelError::NO_ERR) {
        return -1;
    }
    return 0;
}
