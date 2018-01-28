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

    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
    listener->onTouchesEnded= CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void GameLayer::StartGame()
{
    srand((int)time(NULL));

    m_numOfSlidingObjects = 0;

    for (int x = 0; x < COLUMN_COUNT; ++x)
    {
        for (int y = 0; y < ROW_COUNT; ++y)
        {
            GameObject* pGameObject = NULL;

            do
            {
                int type = rand() % TYPE_COUNT;

                if (pGameObject != NULL)
                {
                    //CC_SAFE_DELETE(pGameObject);
                    m_pBoard[x][y] = NULL;
                }

                pGameObject = GameObject::Create(type);

                m_pBoard[x][y] = pGameObject;

            } while (IsStreak(x, y));

            pGameObject->setAnchorPoint(Vec2(0, 1));
            pGameObject->setPosition(Common::ComputeXY(x, y));
            pGameObject->SetTargetBoardX(x);
            pGameObject->SetTargetBoardY(y);
            pGameObject->SetGameLayer(this);

            this->addChild(pGameObject, zGameObject);
        }
    }

    m_bTouchStarted = false;

}

bool GameLayer::IsAdjacent(int x1, int y1, int x2, int y2)
{
    return (abs(x1 - x2) + abs(y1 - y2)) == 1;
}

void GameLayer::SwapObjects(int x1, int y1, int x2, int y2, bool bRollback)
{
    m_numOfSlidingObjects = 2;

    GameObject* pTemp = m_pBoard[x1][y1];

    m_pBoard[x1][y1] = m_pBoard[x2][y2];
    m_pBoard[x2][y2] = pTemp;

    m_pBoard[x1][y1]->SetTargetBoardX(x1);
    m_pBoard[x1][y1]->SetTargetBoardY(y1);
    m_pBoard[x2][y2]->SetTargetBoardX(x2);
    m_pBoard[x2][y2]->SetTargetBoardY(y2);

    if (bRollback)
    {
        GameObject* pGameObject = m_pBoard[x1][y1];
        pGameObject->Rollback();

        pGameObject = m_pBoard[x2][y2];
        pGameObject->Rollback();
    }
    else
    {
        m_pBoard[x1][y1]->ProcessSliding();
        m_pBoard[x2][y2]->ProcessSliding();
    }
}

bool GameLayer::IsStreak(int x, int y)
{
    return StreakHorz(x ,y) > 2 || StreakVert(x, y) > 2;
}


int GameLayer::StreakHorz(int x, int y)
{
    if (x < 0 || x >= COLUMN_COUNT)
        return 0;

    if (y < 0 || y >= ROW_COUNT)
        return 0;

    GameObject* pCurrentGameObject = m_pBoard[x][y];
    if (pCurrentGameObject == NULL)
        return 0;

    int streak = 1;
    int temp = x;

    while (CheckType(pCurrentGameObject->GetType(), temp - 1, y))
    {
        --temp;
        ++streak;
    }

    temp = x;

    while (CheckType(pCurrentGameObject->GetType(), temp + 1, y))
    {
        ++temp;
        ++streak;
    }

    return streak;
}

int GameLayer::StreakVert(int x, int y)
{
    if (x < 0 || x >= COLUMN_COUNT)
        return 0;

    if (y < 0 || y >= ROW_COUNT)
        return 0;

    GameObject* pCurrentGameObject = m_pBoard[x][y];
    if (pCurrentGameObject == NULL)
        return 0;

    int streak = 1;
    int temp = y;

    while (CheckType(pCurrentGameObject->GetType(), x, temp - 1))
    {
        --temp;
        ++streak;
    }

    temp = y;

    while (CheckType(pCurrentGameObject->GetType(), x, temp + 1))
    {
        ++temp;
        ++streak;
    }

    return streak;
}


bool GameLayer::CheckType(int type, int x, int y)
{

    if ( x < 0 || x >= COLUMN_COUNT)
        return 0;

    if ( y < 0 || y >= ROW_COUNT)
        return 0;

    if (m_pBoard[x][y] == NULL)
        return false;

    return type == m_pBoard[x][y]->GetType();
}

void GameLayer::RemoveObject(int x, int y) {
    int currentType = m_pBoard[x][y]->GetType();
    int temp;

    std::vector<GameObject*> removeObjects;

    GameObject* pGameObject = m_pBoard[x][y];
    removeObjects.push_back(pGameObject);

    if (StreakHorz(x, y) > 2)
    {
        temp = x;

        while(CheckType(currentType, temp - 1, y))
        {
            pGameObject = m_pBoard[temp - 1][y];
            removeObjects.push_back(pGameObject);

            --temp;
        }

        temp = x;

        while(CheckType(currentType, temp + 1, y))
        {
            pGameObject = m_pBoard[temp + 1][y];
            removeObjects.push_back(pGameObject);

            ++temp;
        }
    }

    if (StreakVert(x, y) > 2)
    {
        temp = y;

        while(CheckType(currentType, x, temp - 1))
        {
            pGameObject = m_pBoard[x][temp - 1];
            removeObjects.push_back(pGameObject);

            --temp;
        }

        temp = y;

        while(CheckType(currentType, x, temp + 1))
        {
            pGameObject = m_pBoard[x][temp + 1];
            removeObjects.push_back(pGameObject);

            ++temp;
        }

    }

    for ( int i = 0; i < removeObjects.size(); ++i)
    {
        GameObject* pGameObject = removeObjects[i];
        if (pGameObject)
        {
            int boardX = pGameObject->GetTargetBoardX();
            int boardY = pGameObject->GetTargetBoardY();
            m_pBoard[boardX][boardY] = NULL;

            removeChild(pGameObject, true);
        }
    }

    removeObjects.clear();
}

void GameLayer::SlidingFinished(int x1, int y1, int x2, int y2)
{
    --m_numOfSlidingObjects;
    if ( m_numOfSlidingObjects == 0)
    {
        if( IsStreak(x1, y1) || IsStreak(x2, y2))
        {
            bool bRemove1 = false;
            bool bRemove2 = false;

            // 매칭된 줄은 삭제한다.
            if (IsStreak(x1, y1))
            {
                bRemove1 = true;
                RemoveObject(x1, y1);
            }

            if (IsStreak(x2, y2))
            {
                bRemove2 = true;
                RemoveObject(x2, y2);
            }

            if ( bRemove1 || bRemove2)
            {
                ProcessFalling();
            }
        }
        else
        {
            // 매칭되지 않았을 경우 되돌린다.
            SwapObjects(x1, y1, x2, y2, true);
        }
    }
}

void GameLayer::ProcessFalling()
{
    for (int x = 0; x < COLUMN_COUNT; ++x)
    {
        for (int y = ROW_COUNT - 1; y >= 0; --y)
        {
            GameObject* pGameObject = m_pBoard[x][y];
            if (pGameObject == NULL)
            {
                // 비어 있는 공간을 찾았으면 위쪽으로 최초로 비어 있지 않은 공간을 찾는다.
                int k = 0;

                GameObject* pToBeFallingObject = NULL;

                for (k = y; k >= 0; --k)
                {
                    pToBeFallingObject = m_pBoard[x][k];
                    if (pToBeFallingObject != NULL)
                        break;
                }

                if (pToBeFallingObject != NULL)
                {
                    m_pBoard[x][k]->SetTargetBoardX(x);
                    m_pBoard[x][k]->SetTargetBoardY(y);

                    m_pBoard[x][k]->ProcessFalling();

                    m_pBoard[x][y] = m_pBoard[x][k];
                    m_pBoard[x][k] = NULL;
                }

            }
        }
    }
}

void GameLayer::onTouchesBegan(const std::vector<Touch *> &touches, Event *event)
{
    for (Touch* pTouch : touches)
    {
        Point point = pTouch->getLocationInView();

        m_gestureStartBoardX = Common::ComputeBoardX(point.x);
        m_gestureStartBoardY = Common::ComputeBoardY(point.y);

        if(m_pBoard[m_gestureStartBoardX][m_gestureStartBoardY] == NULL)
            return;

        m_bTouchStarted = true;
    }

    /*
    Touch* pTouch = (Touch*) touches.back();
    Point point = pTouch->getLocationInView();

    m_gestureStartBoardX = Common::ComputeBoardX(point.x);
    m_gestureStartBoardY = Common::ComputeBoardY(point.y);

    if(m_pBoard[m_gestureStartBoardX][m_gestureStartBoardY] == NULL)
        return;

    m_bTouchStarted = true;
     */
}

void GameLayer::onTouchesMoved(const std::vector<Touch *> &touches, Event *event)
{
    for (Touch* pTouch : touches)
    {
        if (m_bTouchStarted)
        {
            //Touch* pTouch = (Touch*) touches.back();
            Point point = pTouch->getLocationInView();

            int boardX = Common::ComputeBoardY(point.x);
            int boardY = Common::ComputeBoardY(point.y);

            if (m_pBoard[boardX][boardY] == NULL)
                return;

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
}

void GameLayer::onTouchesEnded(const std::vector<Touch *> &touches, Event *event)
{
    for (Touch* pTouch : touches)
    {
        if (m_bTouchStarted)
        {
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
