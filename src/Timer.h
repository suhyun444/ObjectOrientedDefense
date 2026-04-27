#pragma once
#include "IRoutine.h"

class Wave;
class Timer : public IRoutine{
private:
    float waveDelaySeconds;
    float waveElapsedSeconds;
    Wave* currentWave;
public:
    explicit Timer(Wave* wave);
    void update();

    void setWaveDelay(float delaySeconds);
};