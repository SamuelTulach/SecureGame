#pragma once

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

constexpr float BALL_SPEED = 150.0f;
constexpr float PADDLE_SPEED = 300.0f;
constexpr float PADDLE_WIDTH = 15.0f;
constexpr float PADDLE_HEIGHT = 90.0f;
constexpr float BALL_SIZE = 15.0f;

typedef struct _TICK_INPUT
{
    float DeltaTime;

    bool KeyW;
    bool KeyS;
    bool KeyUp;
    bool KeyDown;

    struct
    {
        float X;
        float Y;
        float Width;
        float Height;
    } LeftPaddle, RightPaddle, Ball;

    int LeftScore;
    int RightScore;
} TICK_DATA;