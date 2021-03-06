﻿/*	MIT License
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
#include <spdlog/spdlog.h>
#include <cxxopts.hpp>
#include <ConsolePrinter.h>
#include <ProgramArgumentsException.h>
#include "CanUtils.h"
#include "TestBenchCommandConstants.h"


const std::string option_help_key = "help";
const std::string option_debug_mode_key = "debug";
const std::string option_can_channel_key = "chan";
const std::string option_can_baudrate_key = "baudrate";
const std::string option_can_interface_key = "iface";


std::unique_ptr<TestBenchOptions> TestBenchOptions::parse(int argc, char **argv) {

    cxxopts::Options options("cantestbench", "CAN Test Bench for pablintino CANopen modules development");

    options.add_options()
            ("h," + option_help_key, "produce help message")
            ("d," + option_debug_mode_key, "debug mode")
            ("c," + option_can_channel_key, "CAN channel ID",
             cxxopts::value<unsigned int>()->default_value("0")->implicit_value("0"))
            ("b," + option_can_baudrate_key, "CAN interface baudrate",
             cxxopts::value<unsigned int>()->default_value("500000")->implicit_value("500000"))
            ("i," + option_can_interface_key, "CAN interface type",
             cxxopts::value<std::string>()->default_value("kvaser")->implicit_value("kvaser"))
            ("l," + TEST_BENCH_COMMAND_LIST_CHANNELS, "List CAN channels")
            ("t," + TEST_BENCH_COMMAND_RUN_TEST, "Test to run", cxxopts::value<std::string>());


    cxxopts::ParseResult opts = options.parse(argc, argv);

    if (opts.count(option_help_key) || opts.arguments().size() == 0) {
        ConsolePrinter::PrintProgramOptions(options.help());
        exit(0);
    }

    // Enable debug mode if requested
    spdlog::set_level(opts[option_debug_mode_key].as<bool>() ? spdlog::level::debug : spdlog::level::info);

    TestBenchOptions *tmp = new TestBenchOptions();
    if (opts.count(option_can_baudrate_key)) {
        unsigned int bitrate_opt = opts[option_can_baudrate_key].as<unsigned int>();
        if (!check_baud_rate_enum_class(bitrate_opt)) {
            throw ProgramArgumentsException("The given bitrate is not supported");
        }

        tmp->baudrate_ = static_cast<CanBitrates>(bitrate_opt);
    } else {
        tmp->baudrate_ = CanBitrates::CAN500K;
    }

    tmp->interface_type_ = opts[option_can_interface_key].as<std::string>();
    tmp->interface_channel_ = opts[option_can_channel_key].as<unsigned int>();

    /* Parse the command to exec */
    if (opts.count(TEST_BENCH_COMMAND_RUN_TEST)) {
        tmp->command_ = TEST_BENCH_COMMAND_RUN_TEST;
        tmp->test_name_ = opts[TEST_BENCH_COMMAND_RUN_TEST].as<std::string>();
    } else if (opts.count(TEST_BENCH_COMMAND_LIST_CHANNELS)) {
        tmp->command_ = TEST_BENCH_COMMAND_LIST_CHANNELS;
    } else {
        throw std::runtime_error("Command to provided");
    };

    return std::unique_ptr<TestBenchOptions>(tmp);
}

unsigned int TestBenchOptions::interface_channel() {
    return interface_channel_;
}

std::string TestBenchOptions::interface_type() {
    return interface_type_;
}

CanBitrates TestBenchOptions::baudrate() {
    return baudrate_;
}

std::string TestBenchOptions::test_name() {
    return test_name_;
}

std::string TestBenchOptions::command() {
    return command_;
}
