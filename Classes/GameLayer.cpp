//
//  GameLayer.cpp
//  Puzzle-mobile
//
//  Created by appsleaf on 2018. 1. 14..
//

#include "GameLayer.h"

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

    cocos2d::Sprite* pBackgroundSprite = cocos2d::Sprite::create("Background.png");
    pBackgroundSprite->setPosition(cocos2d::Vec2(0,0));
    pBackgroundSprite->setAnchorPoint(cocos2d::Vec2(0,0));
    this->addChild(pBackgroundSprite, zBackground);

    m_winSize = Director::getInstance()->getWinSize();

    StartGame();

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

            Sprite* pGameObject = Sprite::create(objectNames[type].c_str());
            m_pBoard[x][y] = pGameObject;

            pGameObject->setAnchorPoint(Vec2(0, 1));
            pGameObject->setPosition(Common::ComputeXY(x, y));

            this->addChild(pGameObject, zGameObject);
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
