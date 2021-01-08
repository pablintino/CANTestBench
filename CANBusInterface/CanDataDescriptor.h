#pragma once
#include <string>
#include <vector>

class CanDataDescriptor
{
public:
	CanDataDescriptor(long id, int dlc, std::vector<uint8_t> data);
	virtual ~CanDataDescriptor();
	std::vector<uint8_t> get_data();
	long get_id();
private:
	std::vector<uint8_t> _data;
	int _dlc;
	long _id;
};

