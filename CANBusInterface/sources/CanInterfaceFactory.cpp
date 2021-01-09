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


#include "CanInterfaceFactory.h"
#include <algorithm>

#include "CanException.h"
#include "KvaserCanInterface.h"


std::unique_ptr<CanInterface> CanIntefaceFactory::make_inteface(std::string iface_type)
{
	std::transform(iface_type.begin(), iface_type.end(), iface_type.begin(), ::tolower);
	if(KvaserCanInterface::KVASER_INTERFACE_NAME == iface_type)
	{
		return std::make_unique<KvaserCanInterface>();
	}

	throw CanException("The given interface is not supported");
}

