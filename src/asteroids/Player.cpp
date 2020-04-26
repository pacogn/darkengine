#include <Player.h>

Player::Player(float x, float y, float dx = 0.0f, float dy = 0.0f, float _angle = 0.0f)
{
    pos = new CVector2(x, y);
    vel = new CVector2(dx, dy);
    angle = _angle;
}

Player::~Player()
{
    delete pos;
    delete vel;
}

// Integrador Euleriano
void Player::Update(double deltaTime)
{
    // VELOCITY changes POSITION (with respect of time)
    pos->x += vel->x * deltaTime;
    pos->y += vel->y * deltaTime;
}

void Player::Thrust(double deltaTime)
{
    // ACCELERATION changes VELOCITY (with respecto of time)
    vel->x += Sin(angle) * acc * deltaTime;
    vel->y += -Cos(angle) * acc * deltaTime;
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

bool Player::isDead()
{
    if (dead) return true;

    if (lives < 1) {
        dead = true;
        color = 0xFF0000;
    }

    return dead;
};

void Player::Reset(float x, float y)
{
    pos->x = x;
    pos->y = y;
    vel->x = 0.0f;
    vel->y = 0.0f;
    angle = 0.0f;
    color = 0x00FF00;
    dead = false;
}
