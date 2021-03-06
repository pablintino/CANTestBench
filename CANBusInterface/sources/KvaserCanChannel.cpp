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


#include "KvaserCanChannel.h"
#include <spdlog/spdlog.h>
#include <CanException.h>
#include "CanTypes.h"
#include "KvaserUtils.h"

KvaserCanChannel::KvaserCanChannel(const unsigned int sdkIndex, const std::string name,
                                   const bool vChannel) : sdkIndex(sdkIndex),
                                                          CanInterfaceChannel(sdkIndex, name, vChannel) {
}

KvaserCanChannel::~KvaserCanChannel() {

}


long to_kvaser_bitrate(const CanBitrates bitrate) {
    switch (bitrate) {
        case CanBitrates::CAN1M:
            return canBITRATE_1M;
        case CanBitrates::CAN500K:
            return canBITRATE_500K;
        case CanBitrates::CAN250K:
            return canBITRATE_250K;
        case CanBitrates::CAN125K:
            return canBITRATE_125K;
        case CanBitrates::CAN100K:
            return canBITRATE_100K;
        case CanBitrates::CAN62K:
            return canBITRATE_62K;
        case CanBitrates::CAN50K:
            return canBITRATE_50K;
        case CanBitrates::CAN83K:
            return canBITRATE_83K;
        case CanBitrates::CAN10K:
            return canBITRATE_10K;
        default:;
            return canBITRATE_500K;
    }
}


CanChannelError KvaserCanChannel::configure(const CanBitrates bitrate) {

    canStatus stat;
    int flags = this->vChannel() ? canOPEN_ACCEPT_VIRTUAL : 0;
    hnd = canOpenChannel(sdkIndex, canOPEN_EXCLUSIVE | flags);
    if (hnd < 0) {
        spdlog::error("Cannot open Kvaser CAN channel {}. [err_code: {}, err: {}]", this->name(), hnd,
                      KvaserUtils::from_kvaser_status((canStatus) hnd));
        return CanChannelError::INITIALIZATION_ERR;
    }

    stat = canSetBusParams(hnd, to_kvaser_bitrate(bitrate), 0, 0, 0, 0, 0);
    if (stat != canOK) {
        spdlog::error("Cannot set bitrate to Kvaser CAN channel {}. [err_code: {}, err: {}]", this->name(), hnd,
                      KvaserUtils::from_kvaser_status((canStatus) hnd));
        return CanChannelError::INITIALIZATION_ERR;
    }
    spdlog::debug("Kvaser CAN interface configured. [name: {}, bitrate: {}]", this->name(), bitrate);

    return CanChannelError::NO_ERR;

}


CanChannelError KvaserCanChannel::connect() {
    canStatus stat;
    stat = canBusOn(hnd);
    if (stat != canOK) {
        spdlog::error("Cannot connect Kvaser CAN channel. [err_code: {}, err: {}]", hnd,
                      KvaserUtils::from_kvaser_status((canStatus) hnd));
        return CanChannelError::INITIALIZATION_ERR;
    }

    spdlog::debug("Kvaser CAN channel on bus.");
    return CanChannelError::NO_ERR;

}


CanChannelError KvaserCanChannel::disconnect() {
    canStatus stat;
    stat = canBusOff(hnd);
    if (stat != canOK) {
        spdlog::error("Cannot go off-bus on Kvaser CAN channel. [err_code: {}, err: {}]", hnd,
                      KvaserUtils::from_kvaser_status((canStatus) hnd));
        return CanChannelError::INITIALIZATION_ERR;
    }

    spdlog::debug("Kvaser CAN channel off-bus.");
    return CanChannelError::NO_ERR;

}

CanDataDescriptor KvaserCanChannel::read(uint32_t timeout) {
    canStatus stat;

    long id = 0;
    uint8_t data[8];
    unsigned int dlc, flags;
    unsigned long timestamp;

    stat = canReadWait(hnd, &id, data, &dlc, &flags, &timestamp, timeout);
    if (stat != canOK) {
        throw CanException("Kvaser CAN channel failed to read data", CanChannelError::READ_ERROR);
    }
    return CanDataDescriptor(id, dlc, std::vector<uint8_t>(std::begin(data), std::end(data)));

}


void KvaserCanChannel::write(uint32_t id, std::vector<uint8_t> data) {
    canStatus stat;

    //TODO Hardcoded flags
    stat = canWrite(hnd, id, data.data(), data.size(), canMSG_STD);
    if (stat != canOK) {
        throw CanException("Kvaser CAN channel failed to write data", CanChannelError::READ_ERROR);
    }
}