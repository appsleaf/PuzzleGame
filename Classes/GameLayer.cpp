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
    Sprite* pGameObject = Sprite::create("Blue.png");
    pGameObject->setPosition(m_winSize.width / 2, m_winSize.height / 2);
    this->addChild(pGameObject);
}


Scene* GameLayer::scene()
{
    Scene* pScene = Scene::create();

    GameLayer* pLayer = GameLayer::create();
    pScene->addChild(pLayer);

    return pScene;
}
