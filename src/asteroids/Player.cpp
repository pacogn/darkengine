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

void Player::Update(double deltaTime)
{
    // VELOCITY changes POSITION (with respect of time)
    pos->x += acc->x * deltaTime;
    pos->y += acc->y * deltaTime;
}

void Player::Thrust(double deltaTime)
{
    // ACCELERATION changes VELOCITY (with respecto of time)
    acc->x += Sin(angle) * mass * deltaTime;
    acc->y += -Cos(angle) * mass * deltaTime;
}

void Player::SteerLeft(double deltaTime)
{
    angle -= steerDegrees * deltaTime;
}

void Player::SteerRight(double deltaTime)
{
    angle += steerDegrees * deltaTime;
}

void Player::Render(CRenderer *renderer)
{
    renderer->WrapCoordinates(pos->x, pos->y, pos->x, pos->y);
    renderer->DrawWireframeModel(vecModelShip, pos->x, pos->y, angle, 5.0f, color);
}

void Player::Reset(float x, float y)
{
    pos->x = x;
    pos->y = y;
    acc->x = 0.0f;
    acc->y = 0.0f;
    angle = 0.0f;
}
