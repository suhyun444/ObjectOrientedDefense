#include "Timer.h"
#include "Wave.h"
#include "Time.h"

Timer::Timer(Wave* wave)
    : waveDelaySeconds(0.f),
      waveElapsedSeconds(0.f),
      currentWave(wave) {}

void Timer::setWaveDelay(float delaySeconds) {
    waveDelaySeconds = delaySeconds;
}

void Timer::update() {
    if (!currentWave) return;

    waveElapsedSeconds += Time::getDeltaTime();
    if (waveElapsedSeconds >= waveDelaySeconds) {
        currentWave->spawnMonster();
        waveElapsedSeconds = 0.f;
    }
}
