#include "KvaserCanChannel.h"

KvaserCanChannel::KvaserCanChannel(unsigned int sdkIndex, std::string name, bool vChannel) : CanInterfaceChannel(name, vChannel) {
	this->_sdkIndex = sdkIndex;
}

KvaserCanChannel::~KvaserCanChannel() {

}

void KvaserCanChannel::connect(unsigned int bitrate) {
	_hnd = canOpenChannel(_sdkIndex, canOPEN_EXCLUSIVE);
	if (_hnd < 0) {
		std::cout << "ERROR!!!";
	}

}