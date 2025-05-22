///****************************************************************************
// Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
// 
// http://www.cocos2d-x.org
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// ****************************************************************************/
//
//#include "HelloWorldScene.h"
//#include "SimpleAudioEngine.h"
//
//USING_NS_CC;
//
//Scene* HelloWorld::createScene()
//{
//    return HelloWorld::create();
//}
//
//// Print useful error message instead of segfaulting when files are not there.
//static void problemLoading(const char* filename)
//{
//    printf("Error while loading: %s\n", filename);
//    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
//}
//
//// on "init" you need to initialize your instance
//bool HelloWorld::init()
//{
//    if (!Scene::init())
//    {
//        return false;
//    }
//
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//    // 添加关闭按钮
//    auto closeItem = MenuItemImage::create(
//        "CloseNormal.png",
//        "CloseSelected.png",
//        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
//
//    if (closeItem == nullptr ||
//        closeItem->getContentSize().width <= 0 ||
//        closeItem->getContentSize().height <= 0)
//    {
//        printf("Error while loading: 'CloseNormal.png' and 'CloseSelected.png'\n");
//    }
//    else
//    {
//        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
//        float y = origin.y + closeItem->getContentSize().height / 2;
//        closeItem->setPosition(Vec2(x, y));
//    }
//
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);
//
//    // 初始化卡牌游戏
//    initCardGame();
//    startCardGame(1); // 默认加载第1关
//
//    return true;
//}
//
//void HelloWorld::initCardGame()
//{
//    // 生成游戏模型
//    GameModelFromLevelGenerator generator;
//    auto sharedGameModel = std::shared_ptr<GameModel>(generator.generateGameModel(1));
//    if (!sharedGameModel || !sharedGameModel->init()) {
//        CCLOGERROR("Failed to create or initialize GameModel");
//        return;
//    }
//    if (!sharedGameModel->init()) {
//        CCLOGERROR("GameModel init failed");
//        return;
//    }
//
//    // 创建 GameView 智能指针
//    _gameView = GameView::createShared(sharedGameModel);
//    if (!_gameView) {
//        CCLOGERROR("GameView create failed");
//        return;
//    }
//
//    // 添加到场景（通过 get() 提取原始指针）
//    this->addChild(_gameView.get());
//
//    // 创建控制器并关联视图（传递智能指针）
//    _gameController = GameController::create(sharedGameModel);
//    if (!_gameController->init(_gameView)) {
//        CCLOGERROR("GameController init failed");
//        return;
//    }
//
//    // 设置回调函数
//    _gameView->setCardClickCallback(CC_CALLBACK_1(HelloWorld::onCardClicked, this));
//    _gameView->setUndoClickCallback(CC_CALLBACK_0(HelloWorld::onUndoClicked, this));
//}
//
//void HelloWorld::startCardGame(int levelId)
//{
//    if (_gameController) {
//        _gameController->startGame();
//    }
//}
//
//void HelloWorld::onCardClicked(int cardId)
//{
//    if (_gameController) {
//        _gameController->handleCardClick(cardId);
//    }
//}
//
//void HelloWorld::onUndoClicked()
//{
//    if (_gameController) {
//        _gameController->handleUndoClick();
//    }
//}
//
//
//void HelloWorld::menuCloseCallback(Ref* pSender)
//{
//    //Close the cocos2d-x game scene and quit the application
//    Director::getInstance()->end();
//
//    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/
//
//    //EventCustom customEndEvent("game_scene_close_event");
//    //_eventDispatcher->dispatchEvent(&customEndEvent);
//
//
//}
/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#include "controllers/GameController.h"
#include "views/GameView.h"
#include "models/GameModel.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// 打印缺资源错误提示
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 添加关闭按钮
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    if (!closeItem || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    {
        problemLoading("CloseNormal.png / CloseSelected.png");
        return false;
    }
    closeItem->setPosition(Vec2(
        origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
        origin.y + closeItem->getContentSize().height / 2));

    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // —— 以下两行是关键：先初始化 MVC，再直接启动游戏 —— 

    initCardGame();               // 创建 Model/View/Controller，并绑定回调
    _gameController->startGame(1); // 调用 startGame()，内部会调用 loadLevelConfig(...) 并生成所有卡牌

    return true;
}

void HelloWorld::initCardGame()
{
    // 1. 生成游戏模型
    auto raw = GameModelFromLevelGenerator::generateGameModel(1);
    auto sharedModel = std::shared_ptr<GameModel>(raw);

    // 2. 传给 View
    _gameView = GameView::createShared(sharedModel);
    this->addChild(_gameView.get());

    // 3. 传给 Controller
    _gameController = GameController::create(sharedModel);
    _gameController->init(_gameView);

}

// 点击卡牌
void HelloWorld::onCardClicked(int cardId)
{
    if (_gameController) {
        _gameController->handleCardClick(cardId);
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    // 如需返回 iOS 原生界面，可发自定义事件
}

