#pragma once
#include <array>
#include <iostream>
#include <optional>
#include <stdint.h>
#include <vector>

namespace
{
    constexpr auto n_numberOfFrames = 10;
    constexpr auto n_numberOfPins = 10;
};

class BowlingGame
{
    struct Frame
    {
        uint16_t m_score{ 0 };
        uint16_t try1PinsKnockedDown{ 0 };
        std::optional<uint16_t> try2PinsKnockedDown;
        std::optional<uint16_t> try3PinsKnockedDown;
    };
    std::vector<std::tuple<std::string, std::array<Frame, 10>>> m_frameScore;

public:
    void SetNumberOfPlayers(uint16_t players);
    void SetPlayerName(uint16_t currPlayerIndex, std::string playerName);
    std::string GetPlayerName(uint16_t currPlayerIndex);
    bool isFrameAStrike(uint16_t currPlayerIndex, uint16_t frameNumber);
    bool isFrameASpare(uint16_t currPlayerIndex, uint16_t frameNumber);
    void UpdateScoreDueToStrikeOrSpare(uint16_t currPlayerIndex, uint16_t frameNumber, uint16_t numberOfPinsKnockedDown);
    void UpdateFrameScoreAfterATry(uint16_t currPlayerIndex, uint16_t frameNumber, uint16_t tryIndex, uint16_t numberOfPinsKnockedDown);
    bool isValidInput(uint16_t currPlayerIndex, uint16_t frameNumber, uint16_t tryIndex, uint16_t numberOfPinsKnockedDown);
    void DisplayPlayers();
    void DisplayScore();
};

