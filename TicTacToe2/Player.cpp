#include "Player.h"


// Return string yang sudah ditata biar bisa langsung dimasukkan ke fungsi display ke console
std::string Player::DisplayMatchHistory()
{
    std::string out, temp;
    for (auto& obj : history) {
        if (obj == MatchState::draw) {
            temp = "DRAW";
        }
        else if (obj == MatchState::lose) {
            temp = "LOSE";
        }
        else if (obj == MatchState::win) {
            temp = "WIN";
        }
        out.append(temp + "; ");
    }
    return out;
}


std::string Player::GetName()
{
    return name;
}


void Player::AddMatchHistory(MatchState state)
{
    history.push_back(state);
}


CellType Player::GetType()
{
    // TODO: Add your implementation code here.
    return cell_type;
}
