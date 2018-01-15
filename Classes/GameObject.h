//
//  GameObject.h
//  Puzzle-mobile
//
//  Created by appsleaf on 2018. 1. 15..
//

#ifndef GameObject_h
#define GameObject_h

#include "Common.h"

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

private:
    int m_type;
};

#endif /* GameObject_h */

