#include "BowlingGame.h"

void BowlingGame::SetNumberOfPlayers(uint16_t players)
{
    m_frameScore.reserve(players);
    for (uint16_t currPlayerIndex = 0; currPlayerIndex < players; currPlayerIndex++)
    {
         m_frameScore.emplace_back(std::make_tuple("", std::array<Frame, 10>{}));
    }
}
void BowlingGame::SetPlayerName(uint16_t currPlayerIndex, std::string playerName)
{
    std::get<0>(m_frameScore[currPlayerIndex]) = playerName;
}
std::string BowlingGame::GetPlayerName(uint16_t currPlayerIndex)
{
    return std::get<0>(m_frameScore[currPlayerIndex]);
}
bool BowlingGame::isFrameAStrike(uint16_t currPlayerIndex, uint16_t frameNumber)
{
    return (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].try1PinsKnockedDown == n_numberOfPins;
}
bool BowlingGame::isFrameASpare(uint16_t currPlayerIndex, uint16_t frameNumber)
{
    return (((std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].try2PinsKnockedDown.has_value()) && (((std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].try1PinsKnockedDown +
        (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].try2PinsKnockedDown.value()) == n_numberOfPins));
}
void BowlingGame::UpdateScoreDueToStrikeOrSpare(uint16_t currPlayerIndex, uint16_t frameNumber, uint16_t numberOfPinsKnockedDown)
{
    (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber - 1].m_score += numberOfPinsKnockedDown;
    (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].m_score += numberOfPinsKnockedDown;
}
void BowlingGame::UpdateFrameScoreAfterATry(uint16_t currPlayerIndex, uint16_t frameNumber, uint16_t tryIndex, uint16_t numberOfPinsKnockedDown)
{
    if (tryIndex == 1)
    {
        (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].try1PinsKnockedDown = numberOfPinsKnockedDown;
        (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].m_score = numberOfPinsKnockedDown;
        if (frameNumber > 0)
        {
            (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].m_score += (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber - 1].m_score;
            if (isFrameAStrike(currPlayerIndex, frameNumber - 1))
            {
                UpdateScoreDueToStrikeOrSpare(currPlayerIndex, frameNumber, numberOfPinsKnockedDown);
            }
            else if (isFrameASpare(currPlayerIndex, frameNumber - 1))
            {
                UpdateScoreDueToStrikeOrSpare(currPlayerIndex, frameNumber, numberOfPinsKnockedDown);
            }
        }
    }
    else if (tryIndex == 2)
    {
        (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].try2PinsKnockedDown = numberOfPinsKnockedDown;
        (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].m_score += numberOfPinsKnockedDown;

        if (frameNumber > 0)
        {
            if (isFrameAStrike(currPlayerIndex, frameNumber - 1))
            {
                UpdateScoreDueToStrikeOrSpare(currPlayerIndex, frameNumber, numberOfPinsKnockedDown);
            }
        }
    }
    else if (tryIndex == 3)
    {
        (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].try3PinsKnockedDown = numberOfPinsKnockedDown;
        (std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].m_score += numberOfPinsKnockedDown;
    }
}
bool BowlingGame::isValidInput(uint16_t currPlayerIndex, uint16_t frameNumber, uint16_t tryIndex, uint16_t numberOfPinsKnockedDown)
{
    bool isValidInput = true;
    if (frameNumber <= (n_numberOfFrames - 1))
    {
        if (numberOfPinsKnockedDown > n_numberOfFrames)
            isValidInput = false;
        else if ((tryIndex == 2) && (((std::get<1>(m_frameScore[currPlayerIndex]))[frameNumber].try1PinsKnockedDown + numberOfPinsKnockedDown) > n_numberOfFrames))
            isValidInput = false;
    }
    return isValidInput;
}
void BowlingGame::DisplayScore()
{
    for (uint16_t currPlayerIndex = 0; currPlayerIndex < m_frameScore.size(); currPlayerIndex++)
    {
        std::cout << "Player Name : " << GetPlayerName(currPlayerIndex) << std::endl;
        for (auto& fScore : (std::get<1>(m_frameScore[currPlayerIndex])))
        {
            std::cout << "\tFrame Score : " << fScore.m_score << std::endl;
        }
    }
}
void BowlingGame::DisplayPlayers()
{
    for (auto& player : m_frameScore)
    {
        std::cout << "player name : " << std::get<0>(player) << std::endl;
    }
}