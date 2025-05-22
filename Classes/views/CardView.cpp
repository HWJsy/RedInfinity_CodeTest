// Classes/views/CardView.cpp
#include "CardView.h"
#include "utils/ResourcePath.h"
#include "cocos2d.h"

USING_NS_CC;

// 常量定义
const float CardView::cardW = 182.0f;
const float CardView::cardH = 282.0f;
const float CardView::suitW = 43.0f;
const float CardView::suitH = 43.0f;
const float CardView::smallW = 26.0f;
const float CardView::smallH = 46.0f;
const float CardView::bigW = 80.0f;
const float CardView::bigH = 139.0f;

CardView::CardView()
    : _cardId(-1), _cardModel(nullptr)
{}

CardView::~CardView() {}

CardView* CardView::create(const std::shared_ptr<CardModel>& model)
{
    CardView* view = new (std::nothrow) CardView();
    if (view && view->init(model)) {
        view->autorelease();
        return view;
    }
    delete view;
    return nullptr;
}

bool CardView::init(const std::shared_ptr<CardModel>& model)
{
    if (!Node::init()) return false;

    _cardModel = model;
    _cardId = model->getId();
    _originalPosition = model->getPosition();

    updateView();
    setPosition(_originalPosition);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(CardView::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(CardView::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CardView::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

void CardView::updateView()
{
    if (!_cardModel) return;
    removeAllChildren();

    auto cardBg = drawBackground();
    if (!cardBg) return;

    Size bgSize = cardBg->getContentSize();
    setContentSize(bgSize);

    drawSuit(cardBg);

    // 获取数字颜色及字符串
    std::string color = (_cardModel->getSuit() == CardSuitType::CST_CLUBS || _cardModel->getSuit() == CardSuitType::CST_SPADES)
        ? "black" : "red";

    std::string numberStr;
    switch (_cardModel->getFace()) {
    case CardFaceType::CFT_ACE:   numberStr = "A";  break;
    case CardFaceType::CFT_TWO:   numberStr = "2";  break;
    case CardFaceType::CFT_THREE: numberStr = "3";  break;
    case CardFaceType::CFT_FOUR:  numberStr = "4";  break;
    case CardFaceType::CFT_FIVE:  numberStr = "5";  break;
    case CardFaceType::CFT_SIX:   numberStr = "6";  break;
    case CardFaceType::CFT_SEVEN: numberStr = "7";  break;
    case CardFaceType::CFT_EIGHT: numberStr = "8";  break;
    case CardFaceType::CFT_NINE:  numberStr = "9";  break;
    case CardFaceType::CFT_TEN:   numberStr = "10"; break;
    case CardFaceType::CFT_JACK:  numberStr = "J";  break;
    case CardFaceType::CFT_QUEEN: numberStr = "Q";  break;
    case CardFaceType::CFT_KING:  numberStr = "K";  break;
    default:                      numberStr = "A";  break;
    }

    drawNumber(cardBg, color, numberStr, true);  // 大数字
    drawNumber(cardBg, color, numberStr, false); // 小数字
}

cocos2d::Sprite* CardView::drawBackground()
{
    auto bgPath = ResourcePath::getCardPath("card_general.png");
    if (!FileUtils::getInstance()->isFileExist(bgPath)) {
        CCLOGERROR("CardView[%d]: bg file not found: %s", _cardId, bgPath.c_str());
        return nullptr;
    }
    auto cardBg = Sprite::create(bgPath);
    if (!cardBg) {
        CCLOGERROR("CardView[%d]: failed to create bg sprite", _cardId);
        return nullptr;
    }
    cardBg->setAnchorPoint(Vec2(0, 0)); // 左下角对齐
    cardBg->setPosition(Vec2(0, 0));    // 放在 CardView 原点
    addChild(cardBg);
    return cardBg;
}

void CardView::drawSuit(cocos2d::Sprite* parent)
{
    if (!_cardModel || !parent) return;

    std::string suitName;
    switch (_cardModel->getSuit()) {
    case CardSuitType::CST_CLUBS:    suitName = "club";    break;
    case CardSuitType::CST_DIAMONDS: suitName = "diamond"; break;
    case CardSuitType::CST_HEARTS:   suitName = "heart";   break;
    case CardSuitType::CST_SPADES:   suitName = "spade";   break;
    default:                         suitName = "club";    break;
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

void CardView::drawNumber(cocos2d::Sprite* parent, const std::string& color, const std::string& numberStr, bool isBig)
{
    if (!parent) return;

    std::string prefix = isBig ? "big_" : "small_";
    auto numberPath = ResourcePath::getNumberPath(prefix + color + "_" + numberStr + ".png");
    auto numberSprite = Sprite::create(numberPath);
    if (!numberSprite) return;

    Size bgSize = parent->getContentSize();

    if (isBig) {
        float x = (bgSize.width - numberSprite->getContentSize().width) * 0.5f;
        float y = (bgSize.height - numberSprite->getContentSize().height) * 0.5f;
        numberSprite->setAnchorPoint(Vec2(0, 0));
        numberSprite->setPosition(Vec2(x, y));
    }
    else {
        float x = 30;
        float y = bgSize.height - numberSprite->getContentSize().height - 30;
        numberSprite->setAnchorPoint(Vec2(0, 0));
        numberSprite->setPosition(Vec2(x, y));
    }

    parent->addChild(numberSprite);
}

void CardView::setClickCallback(const std::function<void(int)>& callback)
{
    _clickCallback = callback;
}

bool CardView::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    // 检查触摸是否在卡牌范围内
    Vec2 touchLocation = convertToNodeSpace(touch->getLocation());
    Rect rect = getBoundingBox();
    rect.origin = Vec2::ZERO;

    if (rect.containsPoint(touchLocation)) {
        // 添加选中效果
        setScale(1.1f);
        return true;
    }

    return false;
}

void CardView::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    // 可以实现拖拽功能
}

void CardView::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    // 恢复缩放
    setScale(1.0f);

    // 检查触摸是否在卡牌范围内
    Vec2 touchLocation = convertToNodeSpace(touch->getLocation());
    Rect rect = getBoundingBox();
    rect.origin = Vec2::ZERO;

    if (rect.containsPoint(touchLocation) && _clickCallback) {
        // 触发点击回调
        _clickCallback(_cardId);
    }
}


