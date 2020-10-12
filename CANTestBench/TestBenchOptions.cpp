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


#include "TestBenchOptions.h"
#include <iostream>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include "../CANBusInterface/CanUtils.h"


namespace bpots = boost::program_options;


std::unique_ptr<TestBenchOptions> TestBenchOptions::parse(int argc, char** argv)
{
	try {

		bpots::options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("chan", bpots::value<unsigned int>(), "CAN interface channel")
			("baudrate", bpots::value<unsigned int>(), "CAN interface baudrate")
			("iface", bpots::value<std::string>(), "CAN interface type");

		bpots::variables_map vm;
		bpots::store(bpots::parse_command_line(argc, argv, desc), vm);
		bpots::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << "\n";
			return nullptr;
		}

		TestBenchOptions* tmp = new TestBenchOptions();

		if (vm.count("baudrate"))
		{
			unsigned int bitrate_opt = vm["baudrate"].as<unsigned int>();
			if (!check_baud_rate_enum_class(bitrate_opt))
			{
				// TODO: Consider using a custom exception
				throw std::runtime_error("The given bitrate is not supported");
			}

			tmp->baudrate_ = static_cast<CanBitrates>(bitrate_opt);
		}
		else
		{
			tmp->baudrate_ = CanBitrates::CAN500K;
		}

		tmp->interface_type_ = vm.count("iface") ? vm["iface"].as<std::string>() : "Kvaser";
		tmp->interface_channel_ = vm.count("chan") ? vm["chan"].as<unsigned int>() : 0;

		// Just log the parameters of the execution for user information
		spdlog::info("Test Bench Options \r\n\tBaudrate: {}\r\n\tInteface: {}\r\n\tChannel: {}", tmp->baudrate_, tmp->interface_type_, tmp->interface_channel_);


		return std::unique_ptr<TestBenchOptions>(tmp);

	}
	catch (std::exception& e) {
		spdlog::error("Error parsing program options: {}", e.what());
		return nullptr;
	}
	catch (...) {
		spdlog::error("Unknown error parsing program options");
		return nullptr;
	}
}

unsigned int TestBenchOptions::interface_channel()
{
	return interface_channel_;
}

std::string TestBenchOptions::interface_type()
{
	return interface_type_;
}

CanBitrates TestBenchOptions::baudrate()
{
	return baudrate_;
}
