#include "CanInterfaceChannel.h"


CanInterfaceChannel::CanInterfaceChannel(std::string name, bool vChannel) {
	_name = name;
	_vChannel = vChannel;
}
std::string CanInterfaceChannel::name(void) {
	return _name;
}
bool CanInterfaceChannel::vChannel(void) {
	return _vChannel;
}

