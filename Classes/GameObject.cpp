//
//  GameObject.cpp
//  Puzzle-mobile
//
//  Created by appsleaf on 2018. 1. 15..
//

#include "GameObject.h"
#include "GameLayer.h"
#include <stdio.h>

GameObject::GameObject()
: m_pGameLayer(NULL) // 변수의 초기화
{

}

GameObject::~GameObject()
{

}

GameObject* GameObject::create(const char* pszFileName, const Rect& rect)
{
    GameObject* pSprite = new GameObject();
    if(pSprite && pSprite->initWithFile(pszFileName, rect))
    {
        pSprite->autorelease();
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

GameObject* GameObject::Create(int type)
{
    static std::string objectNames[TYPE_COUNT] =
    {
        "Blue.png",
        "Brown.png",
        "Green.png",
        "Pink.png",
        "Purple.png",
        "Red.png",
        "Yellow.png",
    };

    if (type < 0 || type > TYPE_COUNT - 1)
        return NULL;

    GameObject* pGameObject = GameObject::create(objectNames[type].c_str(), Rect(0.0f, 0.0f, OBJECT_WIDTH, OBJECT_HEIGHT));
    pGameObject->SetType(type);

    return pGameObject;
}

int GameObject::GetType()
{
    return m_type;
}

void GameObject::SetType(int type)
{
    m_type = type;
}

int GameObject::GetTargetBoardX()
{
    return m_targetBoardX;
}
void GameObject::SetTargetBoardX(int x)
{
    m_targetBoardX = x;
}

int GameObject::GetTargetBoardY()
{
    return m_targetBoardY;
}

void GameObject::SetTargetBoardY(int y)
{
    m_targetBoardY = y;
}

void GameObject::ProcessSliding()
{
    Point position = getPosition();

    m_prevBoardX = Common::ComputeBoardX(position.x);
    m_prevBoardY = MAX_ROW_COUNT -  Common::ComputeBoardY(position.y);

    Point targetPosition = Common::ComputeXY(m_targetBoardX, m_targetBoardY);

    MoveBy* pMoveBy = MoveBy::create(0.1f, Vec2(targetPosition.x - position.x, targetPosition.y - position.y));

    //FiniteTimeAction* pAction = Sequence::create(pMoveBy, CallFunc::create (this, callfunc_selector(GameObject::SlidingCompleteHandler)), NULL);
    //CallFunc *pCallFunc = CallFunc::create( CC_CALLBACK_0(GameObject::SlidingCompleteHandler,this));

    FiniteTimeAction* pAction = Sequence::create(pMoveBy, CallFunc::create( CC_CALLBACK_0(GameObject::SlidingCompleteHandler,this)), NULL);


    runAction(pAction);

}

void GameObject::SlidingCompleteHandler()
{
    int x1 = m_prevBoardX;
    int y1 = m_prevBoardY;
    int x2 = m_targetBoardX;
    int y2 = m_targetBoardY;

    m_pGameLayer->SlidingFinished(x1, y1, x2, y2);
}


void GameObject::Rollback()
{
    Point targetPosition = Common::ComputeXY(m_prevBoardX, m_prevBoardY);
    Point position = getPosition();

    MoveBy* pMoveBy = MoveBy::create(0.1f, Vec2(targetPosition.x - position.x, targetPosition.y - position.y));

    FiniteTimeAction* pAction = Sequence::create(pMoveBy, NULL);

    runAction(pAction);
}

void GameObject::ProcessFalling()
{
    Point position = getPosition();

    m_prevBoardX = Common::ComputeX(position.x);
    m_prevBoardY = MAX_ROW_COUNT - Common::ComputeY(position.y);

    Point targetPosition = Common::ComputeXY(m_targetBoardX, m_targetBoardY);

    int fallingStepCount = m_targetBoardY - m_prevBoardY;

    MoveBy* pMoveBy = MoveBy::create(0.1f * fallingStepCount, Vec2(targetPosition.x - position.x, targetPosition.y - position.y));

    FiniteTimeAction* pAction = Sequence::create(pMoveBy, CallFunc::create(CC_CALLBACK_0(GameObject::FallingCompleteHandler,this)),NULL);

    runAction(pAction);
}

void GameObject::FallingCompleteHandler()
{

}

void GameObject::SetGameLayer(GameLayer *pGameLayer)
{
    m_pGameLayer = pGameLayer;
}