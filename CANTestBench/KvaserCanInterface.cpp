#include "KvaserCanInterface.h"


const std::string KvaserCanInterface::KVASER_INTERFACE_NAME = "Kvaser SDK";

KvaserCanInterface::KvaserCanInterface(): CanInterface(KVASER_INTERFACE_NAME) {
	canInitializeLibrary();
}


actionStatus KvaserCanInterface::initialize(void) {
	
	unsigned long tmp;
	char chName[254];
	int nChannels;
	canStatus stat = canGetNumberOfChannels(&nChannels);
	if (stat == canOK && nChannels > 0 && nChannels < 300) {
		for (unsigned int i = 0; i < nChannels; i++) {
			
			stat = canGetChannelData(i, canCHANNELDATA_CHANNEL_CAP, &tmp, sizeof(tmp));
			if (stat == canOK) {
				stat = canGetChannelData(i, canCHANNELDATA_DEVDESCR_ASCII, &chName, sizeof(chName));
				if (stat == canOK) {
					this->channels().push_back(std::make_shared<KvaserCanChannel>(i, std::string(chName), tmp & canCHANNEL_CAP_VIRTUAL));
				}
				else {
					std::cout << "Error: Cannot retreive channel " << i << " name" << std::endl;
					return actionStatus::FAILED;
				}
			}
			else {
				std::cout << "Error: Cannot retreive channel " << i << " capabilities" << std::endl;
				return actionStatus::FAILED;
			}
		}
	}
	else {
		return actionStatus::FAILED;
	}
	return actionStatus::OK;
}

KvaserCanInterface::~KvaserCanInterface() {
	canStatus stat = canUnloadLibrary();
	if (stat < 0) {
		std::cout << "Unitialize failed!";
	}
}
