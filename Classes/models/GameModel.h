#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "cocos2d.h"
#include "CardModel.h"
#include <vector>
#include <memory>
#include <map>

USING_NS_CC;

/**
 * @class GameModel
 * @brief 管理游戏中的卡牌状态，包括主牌堆、剩余牌栈和托盘，并支持匹配与撤销操作。
 *
 * GameModel 负责：
 * - 存储与查询当前所有卡牌模型
 * - 提供将卡牌在不同牌区间移动的接口
 * - 检查卡牌是否可匹配移动到托盘
 * - 支持记录和恢复卡牌位置，以便实现撤销功能
 *
 * 使用场景：
 * 在 GameController 中创建后，调用 init() 清空状态，
 * 然后通过 addCardTo*() 填充初始卡牌，通过 stockToTray(), playfieldToTray() 等方法完成游戏逻辑。
 */
class GameModel {
public:
    GameModel();
    virtual ~GameModel();

    /**
     * @brief 初始化游戏模型，清空所有牌区和历史记录
     * @return 始终返回 true
     */
    bool init();

    /// @name 填充接口
    ///@{
    void addCardToPlayfield(const std::shared_ptr<CardModel>& card); ///< 将卡牌加入主牌堆
    void addCardToStock(const std::shared_ptr<CardModel>& card);     ///< 将卡牌加入剩余牌栈
    void addCardToTray(const std::shared_ptr<CardModel>& card);     ///< 将卡牌加入托盘（顶部牌栈）
    ///@}

    /// @name 访问接口
    ///@{
    const std::vector<std::shared_ptr<CardModel>>& getPlayfieldCards() const; ///< 获取主牌堆
    const std::vector<std::shared_ptr<CardModel>>& getStockCards() const;     ///< 获取剩余牌栈
    const std::vector<std::shared_ptr<CardModel>>& getTrayCards() const;      ///< 获取托盘（历史牌栈）
    std::shared_ptr<CardModel> getTopTrayCard() const;                       ///< 获取托盘顶牌
    ///@}

    /**
     * @brief 将剩余牌栈顶部一张牌移入托盘
     * @return 操作成功返回 true，否则 false
     */
    bool stockToTray();

    /**
     * @brief 将主牌堆中指定 ID 的卡牌移入托盘
     * @param cardId 卡牌 ID
     * @return 操作成功返回 true，否则 false
     */
    bool playfieldToTray(int cardId);

    /// @name 匹配相关
    ///@{
    bool canMoveToTray(int cardId) const; ///< 判断指定卡牌是否可匹配到托盘
    bool matchCardToTray(int cardId);     ///< 执行匹配操作并记录位置历史
    ///@}

    /// @name 撤销支持
    ///@{
    void recordCardPosition(int cardId, const Vec2& pos); ///< 记录卡牌移动前位置
    void restoreCardPosition(int cardId, const Vec2& pos);///< 恢复卡牌到指定位置
    void undoCardMatch(int cardId, const Vec2& targetPos);///< 撤销一次匹配操作
    void undoCardReplace(int cardId);                      ///< 撤销一次托盘到剩余栈的替换操作
    ///@}

    /**
     * @brief 检查卡牌是否在主牌堆中
     * @param cardId 卡牌 ID
     * @return 在主牌堆中返回 true
     */
    bool isCardInPlayfield(int cardId) const;

    /**
     * @brief 获取指定卡牌的当前位置
     * @param cardId 卡牌 ID
     * @return 卡牌当前位置，若未找到返回 Vec2::ZERO
     */
    Vec2 getCardPosition(int cardId) const;

    /**
     * @brief 根据 ID 获取卡牌模型
     * @param cardId 卡牌 ID
     * @return 对应的 CardModel 指针，未找到返回 nullptr
     */
    std::shared_ptr<CardModel> getCardById(int cardId) const;

private:
    std::vector<std::shared_ptr<CardModel>> _playfieldCards;     ///< 主牌堆列表
    std::vector<std::shared_ptr<CardModel>> _stockCards;         ///< 剩余牌栈列表
    std::vector<std::shared_ptr<CardModel>> _trayCards;          ///< 托盘历史牌栈列表
    std::map<int, Vec2>                                     _cardPositionHistory; ///< 卡牌位置历史
    std::map<int, std::shared_ptr<CardModel>>               _cards;                  ///< ID 到卡牌模型的映射
};

#endif // GAMEMODEL_H
