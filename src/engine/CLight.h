#pragma once

#include "CSceneNode.h"

//-------------------------------------
enum class ELightType {
    Directional,
    Point,
    Spot,    
};

//-------------------------------------
class CLight : public CSceneNode {
};