#include <funcs.hpp>

void computeScore(std::vector<Player*> players) {
    float total_scores=0, c_score=0;
    for (size_t i=0; i<players.size(); i++) {
        c_score = players[i]->getp_score();
        total_scores+=c_score;
    }
    std::cout << "Scores: " << std::endl;
    float percentage_score = 0.0;
    for (size_t i=0; i<players.size(); i++) {
        c_score = players[i]->getp_score(); 
        percentage_score = (c_score/total_scores)*100;
        std::cout << players[i]->getp_name() << ": " << percentage_score << "%" << std::endl;
    }
}