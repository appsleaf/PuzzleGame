//
//  GameLayer.cpp
//  Puzzle-mobile
//
//  Created by appsleaf on 2018. 1. 14..
//

#include "GameLayer.h"

bool GameLayer::init()
{
    if ( Layer::init() == false)
    {
        return false;
    }

    cocos2d::Sprite* pBackgroundSprite = cocos2d::Sprite::create("Background.png");
    pBackgroundSprite->setPosition(cocos2d::Vec2(0,0));
    pBackgroundSprite->setAnchorPoint(cocos2d::Vec2(0,0));
    this->addChild(pBackgroundSprite);

    m_winSize = Director::getInstance()->getWinSize();

    StartGame();

    return true;
}

void GameLayer::StartGame()
{
    for (int x = 0; x < COLUMN_COUNT; ++x)
    {
        for (int y = 0; y < ROW_COUNT; ++y)
        {
            Sprite* pGameObject = Sprite::create("Blue.png");
            m_pBoard[x][y] = pGameObject;

            float xPos = floorf(x * OBJECT_WIDTH);
            float yPos = m_winSize.height - floorf(y * OBJECT_HEIGHT);

            pGameObject->setAnchorPoint(Vec2(0, 1));
            pGameObject->setPosition(Vec2(xPos,yPos));

            this->addChild(pGameObject, 1);
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
