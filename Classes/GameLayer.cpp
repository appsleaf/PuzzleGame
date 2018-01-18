//
//  GameLayer.cpp
//  Puzzle-mobile
//
//  Created by appsleaf on 2018. 1. 14..
//

#include "GameLayer.h"
#include "GameObject.h"

enum
{
    zBackground = 0,
    zGameObject = 1,
};

bool GameLayer::init()
{
    if ( Layer::init() == false)
    {
        return false;
    }

    Sprite* pBackgroundSprite = Sprite::create("Background.png");
    pBackgroundSprite->setPosition(Vec2(0,0));
    pBackgroundSprite->setAnchorPoint(Vec2(0,0));
    this->addChild(pBackgroundSprite, zBackground);

    m_winSize = Director::getInstance()->getWinSize();

    StartGame();

    // Enable touches
    EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
    listener->onTouchesMoved= CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    출처: http://gharlic.tistory.com/27 [gharlic]

    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void GameLayer::StartGame()
{
    srand((int)time(NULL));

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

    for (int x = 0; x < COLUMN_COUNT; ++x)
    {
        for (int y = 0; y < ROW_COUNT; ++y)
        {
            int type = rand() % TYPE_COUNT;

            GameObject* pGameObject = GameObject::Create(type);
            m_pBoard[x][y] = pGameObject;

            pGameObject->setAnchorPoint(Vec2(0, 1));
            pGameObject->setPosition(Common::ComputeXY(x, y));

            this->addChild(pGameObject, zGameObject);
        }
    }

    m_bTouchStarted = false;

}

bool GameLayer::IsAdjacent(int x1, int y1, int x2, int y2)
{
    return (abs(x1 - x2) + abs(y1 - y2)) == 1;
}

void GameLayer::SwapObjects(int x1, int y1, int x2, int y2)
{
    GameObject* pTemp = m_pBoard[x1][y1];

    m_pBoard[x1][y1] = m_pBoard[x2][y2];
    m_pBoard[x2][y2] = pTemp;

//    m_pBoard[x1][y1]->setPosition(Common::ComputeXY(x1, y1));
//    m_pBoard[x2][y2]->setPosition(Common::ComputeXY(x2, y2));
    m_pBoard[x1][y1]->SetTargetBoardX(x1);
    m_pBoard[x1][y1]->SetTargetBoardY(y1);
    m_pBoard[x2][y2]->SetTargetBoardX(x2);
    m_pBoard[x2][y2]->SetTargetBoardY(y2);

    m_pBoard[x1][y1]->ProcessSliding();
    m_pBoard[x2][y2]->ProcessSliding();
}


void GameLayer::onTouchesBegan(const std::vector<Touch *> &touches, Event *event)
{
    Touch* pTouch = (Touch*) touches.back();
    Point point = pTouch->getLocationInView();

    m_gestureStartBoardX = Common::ComputeBoardX(point.x);
    m_gestureStartBoardY = Common::ComputeBoardY(point.y);

    CCLOG("x1 = %d, y1= %d", m_gestureStartBoardX,m_gestureStartBoardY);

    m_bTouchStarted = true;
}

void GameLayer::onTouchesMoved(const std::vector<Touch *> &touches, Event *event)
{

}

void GameLayer::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{
    if (m_bTouchStarted)
    {
        Touch* pTouch = (Touch*) touches.back();
        Point point = pTouch->getLocationInView();

        int boardX = Common::ComputeBoardY(point.x);
        int boardY = Common::ComputeBoardY(point.y);

        if (m_gestureStartBoardX != boardX || m_gestureStartBoardY != boardY)
        {
            if (IsAdjacent(m_gestureStartBoardX, m_gestureStartBoardY, boardX, boardY))
            {
                SwapObjects(m_gestureStartBoardX, m_gestureStartBoardY, boardX, boardY);
            }

            m_bTouchStarted = false;
        }
    }
}

Scene* GameLayer::scene()
{
    Scene* pScene = Scene::create();

    GameLayer* pLayer = GameLayer::create();
    pScene->addChild(pLayer);

    return pScene;
}
