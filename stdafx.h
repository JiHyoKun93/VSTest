#ifndef __STDAFX_H__
#define __STDAFX_H__


#ifdef COCOS2D

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
#include "json/rapidjson.h"
#include "json/document.h"

using namespace cocos2d;
using namespace cocos2d::ui;

#else

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#endif

#endif // !__STDAFX_H__
