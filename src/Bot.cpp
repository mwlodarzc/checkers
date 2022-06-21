#include "Bot.hh"
int Bot::minimax(CheckerBoard &position, int depth, int alfa, int beta, bool whitePov)
{
    int minScore, maxScore, score;
    std::vector<CheckerBoard> possible_positions = position.get_all_settings();
    if (depth == 0 || position.game_over())
        return position.get_score();

    if (whitePov)
    {
        maxScore = -std::numeric_limits<int>::max();
        for (uint i = 0; i < possible_positions.size(); i++)
        {
            score = minimax(possible_positions[i], depth - 1, alfa, beta, false);
            maxScore = std::max(maxScore, score);
            alfa = std::max(alfa, score);
            if (alfa >= beta)
                break;
        }
        return maxScore;
    }

    else
    {
        minScore = std::numeric_limits<int>::max();
        for (uint i = 0; i < possible_positions.size(); i++)
        {
            score = minimax(possible_positions[i], depth - 1, alfa, beta, true);
            minScore = std::min(minScore, score);
            beta = std::min(beta, score);
            if (alfa >= beta)
                break;
        }
        return minScore;
    }
    return 0;
}

void Bot::make_best_move(CheckerBoard &position, int depth, bool whitePov)
{
    int maxScore, score, index = 0;
    std::vector<CheckerBoard> possible_positions = position.get_all_settings();
    maxScore = -std::numeric_limits<int>::max();
    if (whitePov)
        whitePov = !whitePov;
    if (!possible_positions.empty())
        for (uint i = 0; i < possible_positions.size(); i++)
        {
            score = minimax(possible_positions[i], depth - 1, -std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), whitePov);
            std::cout << score << std::endl;
            if (score < maxScore)
            {
                maxScore = score;
                index = i;
            }
        }
    position = possible_positions[index];
}