#include <raylib.h>
#include "movement/keysMovement.h"
void UpdatePosition(Vector2* position)
{
    if (IsKeyDown(KEY_RIGHT))
        position->x += 5;
    if (IsKeyDown(KEY_LEFT))
        position->x -= 5;
    if (IsKeyDown(KEY_DOWN))
        position->y += 5;
    if (IsKeyDown(KEY_UP))
        position->y -= 5;
}
