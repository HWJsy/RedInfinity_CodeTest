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

    // 1. 卡牌背景
    auto bgPath = ResourcePath::getCardPath("card_general.png");
    if (!FileUtils::getInstance()->isFileExist(bgPath)) {
        CCLOGERROR("CardView[%d]: bg file not found: %s", _cardId, bgPath.c_str());
        return;
    }
    auto cardBg = Sprite::create(bgPath);
    if (!cardBg) {
        CCLOGERROR("CardView[%d]: failed to create bg sprite", _cardId);
        return;
    }

    cardBg->setAnchorPoint(Vec2(0, 0)); // 左下角对齐
    cardBg->setPosition(Vec2(0, 0));    // 放在 CardView 原点
    addChild(cardBg);

    // 拿到背景尺寸
    Size bgSize = cardBg->getContentSize();

    setContentSize(bgSize);
    float bgW = bgSize.width, bgH = bgSize.height;

    // 2. 花色图标 43×43，放右上
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
        float x = bgW - suitSprite->getContentSize().width - 30;
        float y = bgH - suitSprite->getContentSize().height - 30;
        suitSprite->setPosition(Vec2(x, y));
        suitSprite->setAnchorPoint(Vec2(0, 0));
        cardBg->addChild(suitSprite);
    }

    // 获取数字资源
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

    // 3. 大数字
    auto bigPath = ResourcePath::getNumberPath("big_" + color + "_" + numberStr + ".png");
    auto bigSprite = Sprite::create(bigPath);
    if (bigSprite) {
        float x = (bgW - bigSprite->getContentSize().width) * 0.5f;
        float y = (bgH - bigSprite->getContentSize().height) * 0.5f;
        bigSprite->setAnchorPoint(Vec2(0, 0));
        bigSprite->setPosition(Vec2(x, y));
        cardBg->addChild(bigSprite);
    }

    // 4. 小数字
    auto smallPath = ResourcePath::getNumberPath("small_" + color + "_" + numberStr + ".png");
    auto smallSprite = Sprite::create(smallPath);
    if (smallSprite) {
        float x = 30;
        float y = bgH - smallSprite->getContentSize().height - 30;
        smallSprite->setAnchorPoint(Vec2(0, 0));
        smallSprite->setPosition(Vec2(x, y));
        cardBg->addChild(smallSprite);
    }

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


