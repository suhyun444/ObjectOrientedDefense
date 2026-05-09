#include "WaveParser.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

MonsterType WaveParser::parseMonsterType(const std::string& str) {
    std::string s = trim(str);
    if (s == "Skeleton") return MonsterType::Skeleton;
    if (s == "Wolf")     return MonsterType::Wolf;
    return MonsterType::Goblin;
}

WaveDescription WaveParser::parseWave(const std::string& waveFile) {
    std::ifstream file(waveFile);
    WaveDescription result;
    std::string line;

    if (!file.is_open()) return result;

    // 첫 줄: rewardGold
    try {
        if (std::getline(file, line) && !trim(line).empty())
            result.rewardGold = std::stoi(trim(line));
    } catch (const std::exception& e) {
        result.hasError = true;
        result.errorMessage = "rewardGold 파싱 실패: " + std::string(e.what());
        return result;
    }

    // 이후 줄: spawnTime,monsterType
    int lineNumber = 1;
    while (std::getline(file, line)) {
        ++lineNumber;
        if (trim(line).empty()) continue;

        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, ','))
            tokens.push_back(trim(token));

        if (tokens.size() < 2) continue;

        SpawnEvent ev;
        try {
            ev.spawnTime = std::stof(tokens[0]);
        } catch (const std::exception& e) {
            result.hasError = true;
            result.errorMessage = std::to_string(lineNumber) + "번째 줄 spawnTime 파싱 실패 (\"" + tokens[0] + "\"): " + e.what();
            return result;
        }
        ev.type = parseMonsterType(tokens[1]);
        result.spawns.push_back(ev);
    }

    return result;
}


