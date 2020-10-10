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
#include "TestBenchOptions.h"
#include "../CANBusInterface/CanTypes.h"
#include "../CANBusInterface/KvaserCanInterface.h"


int main(int argc, char** argv)
{

	// TODO: Temporal hardcoded level
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug

    std::unique_ptr<TestBenchOptions> opts = TestBenchOptions::parse(argc, argv);

	if (opts == nullptr)
	{
        return 0;
	}

	// TODO: Temporal. CAN interface should be provided by a factory based on program arguments
	KvaserCanInterface iface = KvaserCanInterface();
    actionStatus status = iface.initialize();

    if (status == actionStatus::OK) {
    	// TODO: Think about makint a try-get_channel or handle some kind of exception if channel index goes out index
        CanInterfaceChannel* chan = iface.get_channel(opts->interface_channel());
        spdlog::info("Selected CAN channel. [channel_name: {}, is_virtual: {}]", chan->name(), chan->vChannel());
        CanChannelError err = chan->connect(opts->baudrate());
    	if (err != CanChannelError::NO_ERR)
    	{
            return -1;
    	}
    }

	// TODO: Ready to go On-Bus and write raw data to the proper interface
}
