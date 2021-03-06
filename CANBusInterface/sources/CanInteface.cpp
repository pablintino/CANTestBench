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


#include "CanException.h"
#include "CanInterface.h"
#include "fmt/core.h"
#include "Utils.h"

CanInterface::CanInterface(std::string name) : _name(name) {}

std::vector<std::shared_ptr<CanInterfaceChannel>> CanInterface::channels(void) {
	return Utils::get_values<uint8_t, std::shared_ptr<CanInterfaceChannel>>(_channels);
}

std::string CanInterface::name() {
	return _name;
}

std::shared_ptr<CanInterfaceChannel> CanInterface::get_channel(unsigned int chan_number) {

	if(chan_number < channels().size())
	{
		return channels().at(chan_number);
	}
	throw CanException(fmt::format("Channel {} doesn't exist", chan_number));
}

CanInterface::~CanInterface() {
	_channels.clear();
}
