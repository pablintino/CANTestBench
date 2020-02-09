#pragma once

#include <iostream>


class CanInterfaceChannel
{
public:
	CanInterfaceChannel(std::string name, bool vChannel);
	std::string name(void);
	bool vChannel(void);
	virtual ~CanInterfaceChannel() {};
	virtual void connect(unsigned int bitrate) = 0;

private:
	std::string _name;
	bool _vChannel;
};
