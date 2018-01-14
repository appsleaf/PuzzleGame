//
//  Common.h
//  Puzzle
//
//  Created by appsleaf on 2018. 1. 14..
//

#ifndef Common_h
#define Common_h
#include "cocos2d.h"

#define DESIGN_WIDTH    768.0f
#define DESIGN_HEIGHT   1024.0f
#define ROW_COUNT       8
#define COLUMN_COUNT    8
#define MAX_ROW_COUNT   10

#define TYPE_COUNT      7

#define OBJECT_WIDTH    96
#define OBJECT_HEIGHT   96

USING_NS_CC;

class Common
{
public:
    static float ComputeX(float x);
    static float ComputeY(float y);
    static Vec2 ComputeXY(float x, float y);

    static int ComputeBoardX(float x);
    static int ComputeBoardY(float y);
};
#endif /* Common_h */
