#include "CanInterface.h"

CanInterface::CanInterface(std::string name) {
	this->_name = name;
}
std::vector<std::shared_ptr<CanInterfaceChannel>>& CanInterface::channels(void) {
	return this->_channels;
}
std::string CanInterface::name(void) {
	return this->_name;
}
