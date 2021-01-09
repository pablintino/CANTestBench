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


#include "KvaserCanInterface.h"
#include <spdlog/spdlog.h>
#include "KvaserUtils.h"
#include "canlib.h"


const std::string KvaserCanInterface::KVASER_INTERFACE_NAME = "kvaser";

KvaserCanInterface::KvaserCanInterface() : CanInterface(KVASER_INTERFACE_NAME) {
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
                    _channels.push_back(
                            std::make_shared<KvaserCanChannel>(i, std::string(chName), tmp & canCHANNEL_CAP_VIRTUAL));
                } else {
                    spdlog::error("Cannot retrieve channel {} name. [err_code: {}, err: {}]", i, stat,
                                  KvaserUtils::from_kvaser_status(stat));
                    return actionStatus::FAILED;
                }
            } else {
                spdlog::error("Cannot retrieve channel {} capabilities. [err_code: {}, err: {}]", i, stat,
                              KvaserUtils::from_kvaser_status(stat));
                return actionStatus::FAILED;
            }
        }
    } else if (stat != canOK) {
        spdlog::error("Cannot retrieve available Kvaser channels. [err_code: {}, err: {}]", stat,
                      KvaserUtils::from_kvaser_status(stat));
        return actionStatus::FAILED;
    } else {
        spdlog::error("Kvaser channel count seems to be wrong. [nChannels={}]", nChannels);
        return actionStatus::FAILED;
    }
    return actionStatus::OK;
}

KvaserCanInterface::~KvaserCanInterface() {
    canStatus stat = canUnloadLibrary();
    if (stat < 0) {
        spdlog::error("Cannot release Kvaser SDK resources. [err_code: {}, err: {}]", stat,
                      KvaserUtils::from_kvaser_status(stat));
    }
}
