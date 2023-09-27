#pragma once


#define GET_ID_FUNCTION(name) static std::string GetID() { return #name; }

#include "CameraComponents.h"
#include "PlayerComponents.h"
#include "PhysicsComponents.h"
#include "RenderComponents.h"

#undef GET_ID_FUNCTION
