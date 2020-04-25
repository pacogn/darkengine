#pragma once

#include <CRendererAsteroids.h>
#include <MindShake/Math/types/CVector2.h>
#include <MindShake/Math/types/CVector3.h>

using namespace MindShake;

class Player {
public:
    Player(float x, float y, float dx, float dy, float angle);
    ~Player();
    void Render(CRenderer *renderer);

    CVector2 *pos;
    CVector2 *acc;
    float angle = 0;
    uint32_t color = 0x00FF00;

private:
    vector<pair<float, float>> vecModelShip = {
        { 0.0f, -5.0f },
        { -2.5f, +2.5f },
        { +2.5f, +2.5f },
    };
};