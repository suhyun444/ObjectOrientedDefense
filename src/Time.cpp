#include "Time.h"

// 공유 데이터 초기화
float Time::deltaTime = 0.0f;

void Time::update() {
    // 자신의 인스턴스 멤버 clock을 사용하여 static 변수를 갱신
    deltaTime = clock.restart().asSeconds();
}

float Time::getDeltaTime() {
    return deltaTime;
}

float Time::getDeltaTimeMs() {
    return deltaTime * 1000.0f;
}