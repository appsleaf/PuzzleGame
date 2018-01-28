//
//  GameLayer.h
//  Puzzle-mobile
//
//  Created by appsleaf on 2018. 1. 14..
//

#ifndef GameLayer_h
#define GameLayer_h

#include "Common.h"

class GameObject;

class GameLayer : public Layer
{
public:
    bool init();

    void StartGame();

    bool IsStreak(int x, int y);
    int StreakHorz(int x, int y);
    int StreakVert(int x, int y);
    bool CheckType(int type, int x, int y);

    bool IsAdjacent(int x1, int y1, int x2, int y2);
    void SwapObjects(int x1, int y1, int x2, int y2, bool bRollback = false);
    void RemoveObject(int x, int y);

    void SlidingFinished(int x1, int y1, int x2, int y2);
    void ProcessFalling();

    virtual void onTouchesBegan(const std::vector<Touch *> &touches, Event *event);
    virtual void onTouchesMoved(const std::vector<Touch *> &touches, Event *event);
    virtual void onTouchesEnded(const std::vector<Touch *> &touches, Event *event);

    static Scene* scene();

    CREATE_FUNC(GameLayer);

protected:
    GameObject* m_pBoard[COLUMN_COUNT][MAX_ROW_COUNT];

    Size m_winSize;

    // 사용자가 터치를 시작했는지 판단하기 위한.
    bool m_bTouchStarted;

    // 사용자가 터치한 게임 보드상의 좌표를 저장하는데 사용.
    int m_gestureStartBoardX;
    int m_gestureStartBoardY;

    // 이동 중인 오브젝트의 수
    int m_numOfSlidingObjects;

};

#endif /* GameLayer_h */

