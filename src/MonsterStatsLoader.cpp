#include "MonsterStatsLoader.h"

#include <fstream>
#include <sstream>
#include <vector>


static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

MonsterType MonsterStatsLoader::parseMonsterType(const std::string& str) {
    std::string s = trim(str);
    if (s == "Skeleton") return MonsterType::Skeleton;
    if (s == "Wolf")     return MonsterType::Wolf;
    return MonsterType::Goblin;
}

MonsterStats MonsterStatsLoader::load(const std::string& statsFile) {
    std::ifstream file(statsFile);
    std::map<MonsterType, MonsterDescription> result;
    std::string line;

    if (!file.is_open()) return MonsterStats(result);

    std::getline(file, line); // 헤더 스킵

    while (std::getline(file, line)) {
        if (trim(line).empty()) continue;

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ','))
            tokens.push_back(trim(token));

        if (tokens.size() < 4) continue;

        MonsterDescription desc;
        desc.type       = parseMonsterType(tokens[0]);
        desc.maxHealth  = std::stoi(tokens[1]);
        desc.speed      = std::stof(tokens[2]);
        desc.rewardGold = std::stoi(tokens[3]);

        if (tokens.size() >= 8) {
            auto r      = static_cast<sf::Uint8>(std::stoi(tokens[4]));
            auto g      = static_cast<sf::Uint8>(std::stoi(tokens[5]));
            auto b      = static_cast<sf::Uint8>(std::stoi(tokens[6]));
            desc.color  = sf::Color(r, g, b);
            desc.hollow = (std::stoi(tokens[7]) != 0);
        }

        result[desc.type] = desc;
    }

    return MonsterStats(std::move(result));
}
