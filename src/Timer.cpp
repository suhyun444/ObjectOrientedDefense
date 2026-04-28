#include "Timer.h"
#include "Time.h"

Timer::Timer(float duration)
    : duration(duration),
      elapsed(0.f),
      finished(false) {}

void Timer::reset() {
    elapsed  = 0.f;
    finished = false;
}

bool Timer::isFinished() const {
    return finished;
}

float Timer::getElapsed() const {
    return elapsed;
}

void Timer::update() {
    if (finished) return;
    elapsed += Time::getDeltaTime();
    if (elapsed >= duration) finished = true;
}
