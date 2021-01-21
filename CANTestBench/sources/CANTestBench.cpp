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
#include <ConsolePrinter.h>
#include <TestBenchCommandsRunner.h>
#include <ProgramArgumentsException.h>
#include "TestBenchOptions.h"
#include "CanException.h"
#include "CanInterfaceFactory.h"
#include "CanTypes.h"
#include "KvaserCanInterface.h"


int main(int argc, char **argv) {

    std::unique_ptr<TestBenchOptions> opts = TestBenchOptions::parse(argc, argv);

    try {
        // Obtain the selected CAN interface
        std::unique_ptr<CanInterface> iface = CanIntefaceFactory::make_inteface(opts->interface_type());

        if (iface->initialize() == actionStatus::OK) {
            return TestBenchCommandsRunner().run(std::move(opts), std::move(iface));
        }
    } catch (ProgramArgumentsException &e) {
        spdlog::error("Error parsing program options: {}", e.what());
    } catch (const CanException &ex) {
        spdlog::error("An error occurred while initializing CAN interface. {}", ex.what());
    }
    // If we reach this line an error occurred
    return 1;
}
