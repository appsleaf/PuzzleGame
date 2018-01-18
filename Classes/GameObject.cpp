//
//  GameObject.cpp
//  Puzzle-mobile
//
//  Created by appsleaf on 2018. 1. 15..
//

#include "GameObject.h"

GameObject::GameObject()
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

    runAction(pMoveBy);

}