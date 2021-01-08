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


#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

#include <iostream>
#include <vector> 
#include <memory>
#include "CanInterfaceChannel.h"


class CanInterface
{
public:
	CanInterface(std::string name);
	std::vector<CanInterfaceChannel*> channels(void);
	std::string name(void);
	CanInterfaceChannel* get_channel(unsigned int chan_number);
	virtual ~CanInterface();
	virtual actionStatus initialize(void) = 0;
protected:
	void setName(std::string name);
	std::vector<std::unique_ptr<CanInterfaceChannel>> _channels;
private:
	std::string _name;
};


#endif