#pragma once

#include <iostream>
#include <vector> 
#include "CanInterfaceChannel.h"
#include "CanStatus.h"
#include "ICanInterface.h"


class CanInterface : ICanInterface
{
public:
	CanInterface(std::string name);
	std::vector<std::shared_ptr<CanInterfaceChannel>>& channels(void);
	std::string name(void);
	virtual ~CanInterface() {};
	virtual actionStatus initialize(void) = 0;
protected:
	void setName(std::string name);
private:
	std::vector<std::shared_ptr<CanInterfaceChannel>> _channels;
	std::string _name;
};