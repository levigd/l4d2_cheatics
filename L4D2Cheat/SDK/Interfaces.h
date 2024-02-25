#pragma once

#include "../Utils/Utils.h"

#include "IClientEntityList.h"
#include "EngineClient.h"

IClientEntityList* entityList = (IClientEntityList*)GetInterface("VClientEntityList003", "client.dll");
EngineClient* engineclient = (EngineClient*)GetInterface("VEngineClient013", "engine.dll");