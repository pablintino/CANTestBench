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
#include "../CANBusInterface/CanException.h"
#include "../CANBusInterface/CanInterfaceFactory.h"
#include "../CANBusInterface/CanTypes.h"
#include "../CANBusInterface/KvaserCanInterface.h"


int main(int argc, char** argv)
{

	CanChannelError err;
	
	// TODO: Temporal hardcoded level
	spdlog::set_level(spdlog::level::debug); // Set global log level to debug

	std::unique_ptr<TestBenchOptions> opts = TestBenchOptions::parse(argc, argv);

	if (opts == nullptr)
	{
		return 0;
	}

	try
	{
		// Obtain the selected CAN interface
		std::unique_ptr<CanInterface> iface = CanIntefaceFactory::make_inteface(opts->interface_type());

		actionStatus status = iface->initialize();

		if (status == actionStatus::OK) {
			CanInterfaceChannel* chan = iface->get_channel(opts->interface_channel());
			spdlog::info("Selected CAN channel. [channel_name: {}, is_virtual: {}]", chan->name(), chan->vChannel());
			err = chan->configure(opts->baudrate());
			if (err != CanChannelError::NO_ERR)
			{
				return -1;
			}

			err = chan->connect();
			if (err != CanChannelError::NO_ERR)
			{
				return -1;
			}

			/* TODO Test infinite loop*/
			for(int i = 0; i< 4; i++)
			{
				CanChannelError err;
				CanDataDescriptor data = chan->read(err);
				if(err == CanChannelError::NO_ERR)
				{
					spdlog::info("Readed data. [data_id: {}]", data.get_id());
				}
				
			}

			err = chan->disconnect();
			if (err != CanChannelError::NO_ERR)
			{
				return -1;
			}
			
		}
	}catch (const CanException& ex)
	{
		spdlog::error("An error occurred while initializing CAN interface. {}", ex.what());
	}

	// TODO: Ready to go On-Bus and write raw data to the proper interface
}
