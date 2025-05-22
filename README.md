## 引擎依赖

项目使用 Git 子模块引入 Cocos2d-x 引擎源码。  
首次克隆项目后，请执行以下命令初始化子模块：

git submodule update --init --recursive

如果不使用子模块，请手动下载 Cocos2d-x v3.17.2并将其cocos2d/文件夹放置替换项目根目录下的 cocos2d/ 文件夹。

引擎下载地址：
https://github.com/cocos2d/cocos2d-x/releases 


## 项目结构树状图：
```plaintext
RedInfinity_CodeTest
├── .gitignore
├── .gitmodules
├── README.md
├── proj.win32
│   ├── build-cfg.json
│   ├── game.aps
│   ├── game.rc
│   ├── main.cpp
│   ├── main.h
│   ├── resource.h
│   ├── test_zjr.sln
│   ├── test_zjr.vcxproj
│   ├── test_zjr.vcxproj.filters
│   └── test_zjr.vcxproj.user
├── Classes
│   ├── AppDelegate.cpp
│   ├── AppDelegate.h
│   ├── HelloWorldScene.cpp
│   ├── HelloWorldScene.h
│   ├── configs
│   │   ├── loaders
│   │   │   ├── LevelConfigLoader.cpp
│   │   │   └── LevelConfigLoader.h
│   │   └── models
│   │       ├── LevelConfig.cpp
│   │       └── LevelConfig.h
│   ├── controllers
│   │   ├── GameController.cpp
│   │   └── GameController.h
│   ├── managers
│   │   ├── UndoManager.cpp
│   │   └── UndoManager.h
│   ├── models
│   │   ├── CardModel.cpp
│   │   ├── CardModel.h
│   │   ├── GameModel.cpp
│   │   └── GameModel.h
│   ├── services
│   │   ├── GameModelFromLevelGenerator.cpp
│   │   └── GameModelFromLevelGenerator.h
│   ├── utils
│   │   ├── ResourcePath.cpp
│   │   └── ResourcePath.h
│   └── views
│       ├── CardView.cpp
│       ├── CardView.h
│       ├── GameView.cpp
│       └── GameView.h
└── Resources
    ├── CloseNormal.png
    ├── CloseSelected.png
    ├── HelloWorld.png
    ├── fonts/
    ├── levels
    │   └── level_1.json
    └── res/
```

# 程序设计文档
## 一、系统架构
### 1.1 整体架构
项目采用 MVC 架构，将游戏的业务逻辑、数据模型和用户界面分离。
- **Model（模型）**：负责管理游戏数据和业务逻辑，如 `CardModel` 和 `GameModel`。
- **View（视图）**：负责渲染游戏界面和处理用户输入，如 `CardView` 和 `GameView`。
- **Controller（控制器）**：负责协调模型和视图之间的交互。

### 1.2 模块划分
#### 1.2.1 `proj.win32` 模块
- **功能**：包含 Windows 平台的项目配置文件和入口代码。
- **主要文件**：
    - `build - cfg.json`：资源复制配置文件，指定将 `../Resources` 目录下的资源复制到当前目录。
    - `main.cpp` 和 `main.h`：Windows 平台的程序入口文件。

#### 1.2.2 `Classes` 模块
- **功能**：包含游戏的核心代码，按照 MVC 架构和功能模块进行组织。
- **主要子模块和文件**：
    - **`AppDelegate`**：Cocos2d - x 应用程序的入口类，负责初始化和管理应用程序的生命周期。
    - **`HelloWorldScene`**：游戏场景类，负责创建游戏场景、初始化游戏模型、视图和控制器，并处理用户交互事件。
    - **`models` 子目录**：包含游戏的模型类，如 `CardModel` 和 `GameModel`，负责管理游戏数据和业务逻辑。
    - **`views` 子目录**：包含游戏的视图类，如 `CardView` 和 `GameView`，负责渲染游戏界面和处理用户输入。
    - **`controllers` 子目录**：包含游戏的控制器类，负责协调模型和视图之间的交互。
    - **`configs` 子目录**：包含游戏的配置文件和加载器，如 `LevelConfig` 和 `LevelConfigLoader`，负责加载和解析游戏关卡配置。
    - **`services` 子目录**：包含游戏的服务类，如 `GameModelFromLevelGenerator`，负责根据关卡配置生成游戏模型。
    - **`utils` 子目录**：包含游戏的工具类，如 `ResourcePath`，负责管理游戏资源的路径。

#### 1.2.3 `Resources` 模块
- **功能**：包含游戏的资源文件，如图片、字体、关卡配置文件等。
- **主要子目录和文件**：
    - **`levels` 子目录**：包含游戏的关卡配置文件，如 `level_1.json`，定义了关卡中卡牌的初始位置和属性。
    - **`fonts` 子目录**：包含游戏使用的字体文件。
    - **`res` 子目录**：包含游戏的其他资源文件，如卡牌背景、花色图标、数字图标等。

## 二、详细设计
### 2.1 类设计
#### 2.1.1 `AppDelegate` 类
- **功能**：应用程序的入口类，负责初始化和管理应用程序的生命周期。
- **主要方法**：
    - `initGLContextAttrs()`：初始化 OpenGL 上下文属性。
    - `applicationDidFinishLaunching()`：应用程序启动完成时调用，初始化游戏窗口、设置帧率、加载场景等。
    - `applicationDidEnterBackground()`：应用程序进入后台时调用，暂停游戏动画和音频。
    - `applicationWillEnterForeground()`：应用程序回到前台时调用，恢复游戏动画和音频。

#### 2.1.2 `HelloWorldScene` 类
- **功能**：游戏场景类，负责创建游戏场景、初始化游戏模型、视图和控制器，并处理用户交互事件。
- **主要方法**：
    - `createScene()`：创建游戏场景。
    - `init()`：初始化场景，添加关闭按钮，初始化卡牌游戏。
    - `initCardGame()`：初始化卡牌游戏，创建游戏模型、视图和控制器。
    - `onCardClicked(int cardId)`：处理卡牌点击事件。
    - `menuCloseCallback(Ref* pSender)`：处理关闭按钮点击事件，关闭游戏。

#### 2.1.3 `CardModel` 类
- **功能**：表示游戏中的卡牌模型，包含卡牌的 ID、面值、花色和位置等信息。
- **主要方法**：
    - `CardModel(int id, CardFaceType face, CardSuitType suit)`：构造函数，初始化卡牌信息。
    - `canMatch(const CardModel* other) const`：判断两张卡牌是否可以匹配。

#### 2.1.4 `GameModel` 类
- **功能**：表示游戏的整体模型，管理游戏中的卡牌集合、卡牌位置历史等信息，处理卡牌的移动和匹配逻辑。
- **主要方法**：
    - `init()`：初始化游戏模型。
    - `addCardToPlayfield(std::shared_ptr<CardModel> card)`：将卡牌添加到游戏场。
    - `addCardToStock(std::shared_ptr<CardModel> card)`：将卡牌添加到牌堆。
    - `addCardToTray(std::shared_ptr<CardModel> card)`：将卡牌添加到托盘。
    - `getPlayfieldCards`：获取主牌堆
    - `getStockCards() const`：获取剩余牌栈
    - `getTrayCards() const`：获取托盘（历史牌栈）
    - `getTopTrayCard() const`：获取托盘顶部的卡牌。
    - `stockToTray()`：从牌堆中抽取一张卡牌到托盘。
    - `playfieldToTray(int cardId)`：将游戏场中的一张卡牌移动到托盘。
    - `canMoveToTray(int cardId) const`：判断一张卡牌是否可以移动到托盘。
    - `matchCardToTray(int cardId)`：尝试将一张卡牌匹配到托盘。
    - `recordCardPosition(int cardId, const Vec2& pos)`：记录卡牌的位置。
    - `restoreCardPosition(int cardId, const Vec2& pos)`：恢复卡牌的位置。
    - `undoCardMatch(int cardId, const Vec2& targetPos)`：撤销卡牌匹配操作。
    - `undoCardReplace(int cardId)`：撤销卡牌替换操作。
    - `isCardInPlayfield(int cardId) const`：判断一张卡牌是否在游戏场中。
    - `getCardPosition(int cardId) const`：获取一张卡牌的位置。
    - `getCardById(int cardId) const`：根据卡牌 ID 获取卡牌模型。

#### 2.1.5 `CardView` 类
- **功能**：表示游戏中卡牌的视图，负责渲染卡牌的外观和处理卡牌的触摸事件。
- **主要方法**：
    - `create(const std::shared_ptr<CardModel>& model)`：创建卡牌视图。
    - `init(const std::shared_ptr<CardModel>& model)`：初始化卡牌视图，添加触摸监听器。
    - `updateView()`：更新卡牌视图的外观。
    - `setClickCallback(const std::function<void(int)>& callback)`：设置卡牌点击回调函数。
    - `onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)`：处理触摸开始事件。
    - `onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)`：处理触摸移动事件。(暂未实现)
    - `onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)`：处理触摸结束事件。

#### 2.1.6 `GameView` 类
- **功能**：表示游戏的整体视图，负责渲染游戏界面、更新视图和处理撤销按钮点击事件。
- **主要方法**：
    - `create(const std::shared_ptr<GameModel>& m)`：创建游戏视图。
    - `createShared(const std::shared_ptr<GameModel>& m)`：创建共享的游戏视图。
    - `init(const std::shared_ptr<GameModel>& model)`：初始化游戏视图，创建 UI。
    - `createUI()`：创建游戏界面，包括背景、游戏场、牌堆、托盘和撤销按钮。
    - `updateView()`：更新游戏视图，包括游戏场卡牌、牌堆卡牌、托盘顶部卡牌和托盘历史卡牌。
    - `onUndoButtonClicked(Ref* sender)`：处理撤销按钮点击事件。
    - `playMoveToAnimation(int cardId)`：播放卡牌移动动画。
    - `getCardViewById(int cardId)`：根据卡牌 ID 获取卡牌视图。

#### 2.1.7 `LevelConfigLoader` 类
- **功能**：负责加载和解析游戏关卡配置文件。
- **主要方法**：
    - `loadLevelConfig(int levelId)`：加载指定关卡的配置文件，解析 JSON 数据并返回 `LevelConfig` 对象。

#### 2.1.8 `GameModelFromLevelGenerator` 类
- **功能**：根据关卡配置生成游戏模型。
- **主要方法**：
    - `generateGameModel(int levelId)`：生成指定关卡的游戏模型，包括初始化游戏模型、添加游戏场卡牌、添加牌堆卡牌和从牌堆抽取一张卡牌到托盘。

### 2.2 数据流程
1. **游戏启动**：`AppDelegate` 类的 `applicationDidFinishLaunching()` 方法被调用，初始化游戏窗口、设置帧率、加载 `HelloWorldScene` 场景。
2. **场景初始化**：`HelloWorldScene` 类的 `init()` 方法被调用，添加关闭按钮，调用 `initCardGame()` 方法初始化卡牌游戏。
3. **卡牌游戏初始化**：
    - `GameModelFromLevelGenerator` 类的 `generateGameModel(int levelId)` 方法根据关卡配置生成游戏模型。
    - `GameView` 类的 `createShared(const std::shared_ptr<GameModel>& m)` 方法创建游戏视图，并调用 `init(const std::shared_ptr<GameModel>& model)` 方法初始化视图。
    - `GameController` 类创建并初始化，协调模型和视图之间的交互。
4. **用户交互**：
    - 用户点击卡牌时，`CardView` 类的 `onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)` 方法被调用，触发点击回调函数。
    - `HelloWorldScene` 类的 `onCardClicked(int cardId)` 方法处理卡牌点击事件，调用 `GameController` 类的 `handleCardClick(cardId)` 方法。
    - `GameController` 类调用 `GameModel` 类的相关方法处理卡牌匹配和移动逻辑。
    - `GameView` 类的 `updateView()` 方法更新游戏视图。
5. **撤销操作**：
    - 用户点击撤销按钮时，`GameView` 类的 `onUndoButtonClicked(Ref* sender)` 方法被调用，触发撤销回调函数。
    - `HelloWorldScene` 类的 `onUndoClicked()` 方法处理撤销点击事件，调用 `GameController` 类的 `handleUndoClick()` 方法。
    - `GameController` 类调用 `GameModel` 类的相关方法撤销卡牌匹配或替换操作。
    - `GameView` 类的 `updateView()` 方法更新游戏视图。

## 如何新加一个卡牌类型以及实现其回退功能

#### 1. 定义新的卡牌类型枚举值
在 `CardModel.h` 文件中，需要扩展 `CardSuitType` 或者 `CardFaceType` 枚举来定义新的卡牌类型。假设我们要添加一个新的花色类型，可以在 `CardSuitType` 枚举中添加新的枚举值：

```cpp
// CardModel.h
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // 梅花
    CST_DIAMONDS,   // 方块
    CST_HEARTS,     // 红桃
    CST_SPADES,     // 黑桃
    CST_NEW_SUIT,   // 新的花色类型
    CST_NUM_CARD_SUIT_TYPES
};
```

#### 2. 修改卡牌模型
在 `CardModel` 类中，需要确保新的卡牌类型可以被正确处理。构造函数和 `canMatch` 函数可能需要相应的调整。

```cpp
// CardModel.cpp
CardModel::CardModel(int id, CardFaceType face, CardSuitType suit)
    : _id(id)
    , _face(face)
    , _suit(suit)
    , _position(cocos2d::Vec2::ZERO)
{
}

bool CardModel::canMatch(const CardModel* other) const
{
    if (!other) return false;

    // 判断牌面数值是否相差1
    int thisValue = static_cast<int>(_face);
    int otherValue = static_cast<int>(other->getFace());

    return (thisValue == otherValue + 1) || (thisValue == otherValue - 1);
    // 如果新的卡牌类型有特殊的匹配规则，可以在这里添加逻辑
}
```

#### 3. 修改卡牌视图
在 `CardView.cpp` 文件中，需要为新的卡牌类型添加相应的资源加载和绘制逻辑。

```cpp
// CardView.cpp
void CardView::drawSuit(cocos2d::Sprite* parent)
{
    if (!_cardModel || !parent) return;

    std::string suitName;
    switch (_cardModel->getSuit()) {
    case CardSuitType::CST_CLUBS:    suitName = "club";      break;
    case CardSuitType::CST_DIAMONDS: suitName = "diamond";   break;
    case CardSuitType::CST_HEARTS:   suitName = "heart";     break;
    case CardSuitType::CST_SPADES:   suitName = "spade";     break;
    case CardSuitType::CST_NEW_SUIT: suitName = "new_suit";  break;,   // 新的花色类型
    default:                         suitName = "club";      break;
    }

    auto suitPath = ResourcePath::getSuitPath(suitName + ".png");
    auto suitSprite = Sprite::create(suitPath);
    if (suitSprite) {
        Size bgSize = parent->getContentSize();
        float x = bgSize.width - suitSprite->getContentSize().width - 30;
        float y = bgSize.height - suitSprite->getContentSize().height - 30;
        suitSprite->setPosition(Vec2(x, y));
        suitSprite->setAnchorPoint(Vec2(0, 0));
        parent->addChild(suitSprite);
    }
}
```

#### 4. 修改关卡配置加载逻辑
在 `LevelConfigLoader.cpp` 文件中，需要确保新的卡牌类型可以从 JSON 配置文件中正确加载。

```cpp
// LevelConfigLoader.cpp
namespace config {
    std::shared_ptr<LevelConfig> LevelConfigLoader::loadLevelConfig(int levelId) {
        // ... 原有代码 ...

        // 解析卡牌信息
        cfg.face = cardObj["CardFace"].GetInt();
        cfg.suit = cardObj["CardSuit"].GetInt();
        if (cfg.suit == static_cast<int>(CardSuitType::CST_NEW_SUIT)) {
            // 处理新的花色类型
        }

        // ... 原有代码 ...
    }
}
```

### 实现新卡牌类型的回退功能

#### 1. 定义新的回退动作类型
在 `UndoAction.h` 文件中，添加新的回退动作类型枚举值。

```cpp
// UndoAction.h
enum class UndoActionType
{
    NONE,
    CARD_MATCHED,    // 卡片匹配操作
    STACK_TO_TRAY,   // 从剩余栈移到托盘栈的操作
    NEW_CARD_ACTION  // 新卡牌类型的回退动作
};
```

#### 2. 修改回退管理器逻辑
在 `GameController.cpp` 文件中，处理新的回退动作类型。

```cpp
// GameController.cpp
void GameController::handleUndoClick()
{
    if (!_undoManager->canUndo())
    {
        CCLOG("=== _undoManager can't undo ===");
        return;
    }
    auto action = _undoManager->undo();
    if (!action)
    {
        CCLOG("=== _undoManager can't undo ===");
        return;
    }
    if (action->getType() == UndoActionType::CARD_MATCHED) {
        int id = action->getCardId(); 
        Vec2 pos = action->getPosition();
        _gameModel->undoCardMatch(id, pos);
    }
    else if (action->getType() == UndoActionType::STACK_TO_TRAY) {
        // 将卡片从托盘栈移回 stock
        int id = action->getCardId();
        // 移除 tray 栈顶
        _gameModel->undoCardReplace(id);
    }
    else if (action->getType() == UndoActionType::NEW_CARD_ACTION) {
        // 处理新卡牌类型的回退逻辑
        int id = action->getCardId();
        Vec2 pos = action->getPosition();
        // 调用 GameModel 中对应的回退方法
        _gameModel->undoNewCardAction(id, pos);
    }
    _gameView->updateView();

    logGameState();
}
```

#### 3. 在游戏模型中实现回退方法
在 `GameModel.h` 和 `GameModel.cpp` 文件中，添加新的回退方法。

```cpp
// GameModel.h
class GameModel {
    // ... 原有代码 ...
    void undoNewCardAction(int cardId, const Vec2& targetPos);
    // ... 原有代码 ...
};

// GameModel.cpp
void GameModel::undoNewCardAction(int cardId, const Vec2& targetPos) {
    // 实现新卡牌类型的回退逻辑
    auto card = _cards.at(cardId);
    card->setPosition(targetPos);

    // 根据新卡牌类型的具体操作，将卡片移回相应的位置
    // 例如，如果是从某个特殊区域移到托盘栈，将卡片移回特殊区域
    // 这里假设是从特殊区域移到托盘栈，需要将卡片移回特殊区域
    _trayCards.pop_back();
    // 假设特殊区域是一个新的容器 _specialAreaCards
    _specialAreaCards.push_back(card);
}
```