//
//  GameLayer.h
//  Puzzle-mobile
//
//  Created by appsleaf on 2018. 1. 14..
//

#ifndef GameLayer_h
#define GameLayer_h

#include "Common.h"

class GameLayer : public Layer
{
public:
    bool init();
    static Scene* scene();
    void StartGame();
    CREATE_FUNC(GameLayer);
private:
    Sprite* m_pBoard[COLUMN_COUNT][MAX_ROW_COUNT];
    
    Size m_winSize;
};

#endif /* GameLayer_h */

