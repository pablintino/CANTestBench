

#include "CanTypes.h"

bool check_baud_rate_enum_class(int value)
{
    if (value < static_cast<int>(CanBitrates::CAN10K)) return false;
    if (value > static_cast<int>(CanBitrates::CAN1M)) return false;

    switch (static_cast<CanBitrates>(value))
    {
    case CanBitrates::CAN1M:
    case CanBitrates::CAN500K:
    case CanBitrates::CAN250K:
    case CanBitrates::CAN125K:
    case CanBitrates::CAN100K:
    case CanBitrates::CAN62K:
    case CanBitrates::CAN50K:
    case CanBitrates::CAN83K:
    case CanBitrates::CAN10K:
        return true;
    default: ;
        return false;
    }
}