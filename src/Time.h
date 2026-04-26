#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Time {
private:
    sf::Clock clock;           // 인스턴스가 소유 (static 아님)
    static float deltaTime;    // 누구나 접근 가능한 공유 데이터 (static)

public:
    Time() = default;

    // 메인 루프에서 인스턴스를 통해 호출됨
    void update();

    // 전역에서 파라미터 없이 호출 가능
    static float getDeltaTime();
    static float getDeltaTimeMs();
};