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


#include <iostream>
#include "ConsolePrinter.h"
#include "fmt/core.h"

void ConsolePrinter::PrintProgramOptions(std::string help_message) {

    std::cout << help_message << std::endl;

}

void ConsolePrinter::PrintInterfaceChannels(std::vector<std::shared_ptr<CanInterfaceChannel>> chans) {
    if(!chans.empty()){
        for (std::shared_ptr<CanInterfaceChannel> &chan : chans) {
            std::cout << fmt::format("CAN Channel {}:\n\t Name: {}\n\t Virtual: {}\n", chan->chan_index(), chan->name(),
                                     chan->vChannel());
        }
    }else{
        std::cout << "No CAN channels found!" << std::endl;
    }
}
