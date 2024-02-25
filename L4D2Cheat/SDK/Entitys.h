#pragma once

#include <Windows.h>
#include <cstdint>

#include "CVector.h"


class CPlayer
{
public:
	char pad_0000[148]; //0x0000
	CVector3 legPos; //0x0094
	char pad_00A0[84]; //0x00A0
	int32_t iHealth; //0x00F4
	char pad_00F8[3920]; //0x00F8
}; //Size: 0x1048

class CInfected
{
public:
	char pad_0000[148]; //0x0000
	CVector3 position; //0x0094
	char pad_00A0[84]; //0x00A0
	int32_t iHealth; //0x00F4
	char pad_00F8[3920]; //0x00F8
};

class CEntity
{
public:

};