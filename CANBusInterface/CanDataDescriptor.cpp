﻿#include "CanDataDescriptor.h"


CanDataDescriptor::CanDataDescriptor(long id, int dlc, std::vector<uint8_t> data) : _data(data), _dlc(dlc), _id(id)
{
}


std::vector<uint8_t> CanDataDescriptor::get_data()
{
	return _data;
}

long CanDataDescriptor::get_id()
{
	return _id;
}

CanDataDescriptor::~CanDataDescriptor()
{
	std::vector<uint8_t>().swap(_data);
}