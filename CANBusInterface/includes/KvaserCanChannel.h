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


#ifndef KVASER_CAN_CHANNEL_H
#define KVASER_CAN_CHANNEL_H


#include "CanInterfaceChannel.h"
#include "canlib.h"
#include "CanTypes.h"


class KvaserCanChannel : public CanInterfaceChannel
{
public:
	KvaserCanChannel(unsigned int sdkIndex, std::string name, bool vChannel);
	~KvaserCanChannel();
	CanChannelError configure(CanBitrates bitrate) override;
	CanChannelError connect() override;
	CanChannelError disconnect() override;
    CanDataDescriptor read(uint32_t timeout) override;
    void KvaserCanChannel::write(uint32_t id, std::vector<uint8_t> data) override;

private:
	unsigned int sdkIndex;
	CanHandle hnd;
};

#endif