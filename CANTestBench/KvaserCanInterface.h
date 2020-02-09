#pragma once

#include "canlib.h"
#include <iostream>
#include "CanInterface.h"
#include "KvaserCanChannel.h"


class KvaserCanInterface : public CanInterface
{
public:
	static const std::string KVASER_INTERFACE_NAME;
	KvaserCanInterface();
	~KvaserCanInterface();
	actionStatus initialize(void);
};
