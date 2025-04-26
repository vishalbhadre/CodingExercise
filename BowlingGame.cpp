#include "BowlingGame.h"

bool BowlingGame::isFrameAStrike(uint16_t frameNumber)
{
    return m_frameScore[frameNumber].try1PinsKnockedDown == n_numberOfPins;
}
bool BowlingGame::isFrameASpare(uint16_t frameNumber)
{
    return ((m_frameScore[frameNumber].try2PinsKnockedDown.has_value()) && ((m_frameScore[frameNumber].try1PinsKnockedDown +
        m_frameScore[frameNumber].try2PinsKnockedDown.value()) == n_numberOfPins));
}
void BowlingGame::UpdateScoreDueToStrikeOrSpare(uint16_t frameNumber, uint16_t numberOfPinsKnockedDown)
{
    m_frameScore[frameNumber - 1].m_score += numberOfPinsKnockedDown;
    m_frameScore[frameNumber].m_score += numberOfPinsKnockedDown;
}
void BowlingGame::UpdateFrameScoreAfterATry(uint16_t frameNumber, uint16_t tryIndex, uint16_t numberOfPinsKnockedDown)
{
    if (tryIndex == 1)
    {
        m_frameScore[frameNumber].try1PinsKnockedDown = numberOfPinsKnockedDown;
        m_frameScore[frameNumber].m_score = numberOfPinsKnockedDown;
        if (frameNumber > 0)
        {
            m_frameScore[frameNumber].m_score += m_frameScore[frameNumber - 1].m_score;
            if (isFrameAStrike(frameNumber - 1))
            {
                UpdateScoreDueToStrikeOrSpare(frameNumber, numberOfPinsKnockedDown);
            }
            else if (isFrameASpare(frameNumber - 1))
            {
                UpdateScoreDueToStrikeOrSpare(frameNumber, numberOfPinsKnockedDown);
            }
        }
    }
    else if (tryIndex == 2)
    {
        m_frameScore[frameNumber].try2PinsKnockedDown = numberOfPinsKnockedDown;
        m_frameScore[frameNumber].m_score += numberOfPinsKnockedDown;

        if (frameNumber > 0)
        {
            if (isFrameAStrike(frameNumber - 1))
            {
                UpdateScoreDueToStrikeOrSpare(frameNumber, numberOfPinsKnockedDown);
            }
        }
    }
    else if (tryIndex == 3)
    {
        m_frameScore[frameNumber].try3PinsKnockedDown = numberOfPinsKnockedDown;
        m_frameScore[frameNumber].m_score += numberOfPinsKnockedDown;
    }
}
bool BowlingGame::isValidInput(uint16_t frameNumber, uint16_t tryIndex, uint16_t numberOfPinsKnockedDown)
{
    bool isValidInput = true;
    if (frameNumber <= (n_numberOfFrames - 1))
    {
        if (numberOfPinsKnockedDown > n_numberOfFrames)
            isValidInput = false;
        else if ((tryIndex == 2) && ((m_frameScore[frameNumber].try1PinsKnockedDown + numberOfPinsKnockedDown) > n_numberOfFrames))
            isValidInput = false;
    }
    return isValidInput;
}
void BowlingGame::DisplayScore()
{
    for (auto& fScore : m_frameScore)
    {
        std::cout << "Frame Score : " << fScore.m_score << std::endl;
    }
}