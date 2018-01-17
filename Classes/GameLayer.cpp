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

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GameLayer::onTouchesCancelled, this);

    auto dispatcher = this->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
}

void GameLayer::onTouchesBegan(const std::vector<Touch*> &touches, cocos2d::Event *event)
{
    for (auto iter = touches.begin(); iter != touches.end(); iter++)
    {
        Point point = (*iter)->getLocationInView();

        int boardX = Common::ComputeBoardX(point.x);
        int boardY = Common::ComputeBoardY(point.y);

        Sprite* pGameObject = m_pBoard[boardX][boardY];
        pGameObject->setVisible(!pGameObject->isVisible());
    }
}

void GameLayer::onTouchesMoved(const std::vector<Touch*> &touches, cocos2d::Event *event)
{
    for (auto iter = touches.begin(); iter != touches.end(); iter++)
    {
        Point point = (*iter)->getLocationInView();
    }
}

void GameLayer::onTouchesEnded(const std::vector<Touch*> &touches, cocos2d::Event *event)
{
    for (auto iter = touches.begin(); iter != touches.end(); iter++)
    {
        Point point = (*iter)->getLocationInView();
    }
}

Scene* GameLayer::scene()
{
    Scene* pScene = Scene::create();

    GameLayer* pLayer = GameLayer::create();
    pScene->addChild(pLayer);

    return pScene;
}
