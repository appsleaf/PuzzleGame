//
//  Common.cpp
//  Puzzle-mobile
//
//  Created by appsleaf on 2018. 1. 14..
//

#include "Common.h"

float Common::ComputeX(float x)
{
    return floorf(x * OBJECT_WIDTH);
}

float Common::ComputeY(float y)
{
    return Director::getInstance()->getWinSize().height - floorf(y * OBJECT_HEIGHT);
}

Vec2 Common::ComputeXY(float x, float y)
{
    return Vec2(ComputeX(x), ComputeY(y));
}

int Common::ComputeBoardX(float x)
{
    return (int)(x / floorf(OBJECT_WIDTH));
}

int Common::ComputeBoardY(float y)
{
    return (int)(y / floorf(OBJECT_HEIGHT));
}
