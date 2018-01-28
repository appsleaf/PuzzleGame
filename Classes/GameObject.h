//
//  GameObject.h
//  Puzzle-mobile
//
//  Created by appsleaf on 2018. 1. 15..
//

#ifndef GameObject_h
#define GameObject_h

#include "Common.h"

class GameLayer;

class GameObject : public Sprite
{
public:
    GameObject();
    ~GameObject();

protected:
    static GameObject* create(const char* pszFileName, const Rect& rect);

public:
    static GameObject* Create(int type);

    int GetType();
    void SetType(int type);

    int GetTargetBoardX();
    void SetTargetBoardX(int x);

    int GetTargetBoardY();
    void SetTargetBoardY(int y);

    void ProcessSliding();
    void SlidingCompleteHandler();

    void Rollback();

    void ProcessFalling();
    void FallingCompleteHandler();

    void SetGameLayer(GameLayer* pGameLayer);

private:
    int m_type;

    // 움직이기 전의 좌표
    int m_prevBoardX;
    int m_prevBoardY;

    // 움직일 때 향해야할 좌표
    int m_targetBoardX;
    int m_targetBoardY;

    GameLayer* m_pGameLayer;

};

#endif /* GameObject_h */

