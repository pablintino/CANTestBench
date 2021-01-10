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


#include <spdlog/spdlog.h>
#include <TestFactory.h>
#include "TestBenchOptions.h"
#include "CanException.h"
#include "CanInterfaceFactory.h"
#include "CanTypes.h"
#include "KvaserCanInterface.h"


int main(int argc, char **argv) {

    CanChannelError err;

    std::unique_ptr<TestBenchOptions> opts = TestBenchOptions::parse(argc, argv);

    if (opts == nullptr) {
        return 0;
    }

    try {
        // Obtain the selected CAN interface
        std::unique_ptr<CanInterface> iface = CanIntefaceFactory::make_inteface(opts->interface_type());

        actionStatus status = iface->initialize();

        if (status == actionStatus::OK) {

            if (!opts->list_channels()) {

                std::shared_ptr<CanInterfaceChannel> chan = iface->get_channel(opts->interface_channel());
                spdlog::info("Selected CAN channel. [channel_name: {}, is_virtual: {}]", chan->name(),
                             chan->vChannel());
                err = chan->configure(opts->baudrate());
                if (err != CanChannelError::NO_ERR) {
                    return -1;
                }

                err = chan->connect();
                if (err != CanChannelError::NO_ERR) {
                    return -1;
                }

                std::unique_ptr<TestBenchTest> test = TestFactory::get_test(opts->test_name());
                if (test->run(chan)) {
                    spdlog::info("Test passed correctly");
                } else {
                    spdlog::error("Test failed");
                }

                err = chan->disconnect();
                if (err != CanChannelError::NO_ERR) {
                    return -1;
                }

            } else {
                for (std::shared_ptr<CanInterfaceChannel> &chan : iface->channels()) {
                    spdlog::info("CAN Channel {} [channel_name: {}, is_virtual: {}]", chan->chan_index(), chan->name(),
                                 chan->vChannel());
                }
            }
        }
    } catch (const CanException &ex) {
        spdlog::error("An error occurred while initializing CAN interface. {}", ex.what());
    }
}
