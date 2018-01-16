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

    void StartGame();

    void onTouchesBegan(const std::vector<Touch *> &touches, Event *event);
    void onTouchesMoved(const std::vector<Touch *> &touches, Event *event);
    void onTouchesEnded(const std::vector<Touch *> &touches, Event *event);

    static Scene* scene();

    CREATE_FUNC(GameLayer);
private:
    Sprite* m_pBoard[COLUMN_COUNT][MAX_ROW_COUNT];
    
    Size m_winSize;
};

#endif /* GameLayer_h */

