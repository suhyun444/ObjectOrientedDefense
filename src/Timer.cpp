#include "Timer.h"

// 공유 데이터 초기화
float Timer::deltaTime = 0.0f;

void Timer::update() {
    // 자신의 인스턴스 멤버 clock을 사용하여 static 변수를 갱신
    deltaTime = clock.restart().asSeconds();
}

float Timer::getDeltaTime() {
    return deltaTime;
}

float Timer::getDeltaTimeMs() {
    return deltaTime * 1000.0f;
}