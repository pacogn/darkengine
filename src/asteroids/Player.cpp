#include <Player.h>

Player::Player(float x, float y, float dx = 0.0f, float dy = 0.0f, float _angle = 0.0f)
{
    pos = new CVector2(x, y);
    acc = new CVector2(dx, dy);
    angle = _angle;
}

Player::~Player()
{
    delete pos;
    delete acc;
}

void Player::Render(CRenderer *renderer)
{
    renderer->DrawWireframeModel(vecModelShip, pos->x, pos->y, angle, 5.0f, color);
}
