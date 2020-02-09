#pragma once

#include "CanInterfaceChannel.h"
#include "canlib.h"

class KvaserCanChannel : public CanInterfaceChannel
{
public:
	KvaserCanChannel(unsigned int sdkIndex, std::string name, bool vChannel);
	~KvaserCanChannel();
	void connect(unsigned int bitrate);

private:
	unsigned int _sdkIndex;
	CanHandle _hnd;
};
