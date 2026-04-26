#pragma once
#include "IRoutine.h"

class Wave;
class Timer : public IRoutine{
private:
    float waveDelaySeconds;
    float waveElapsedSeconds;
    Wave* currentWave;
public:
    Timer();
    void update();

    void setWaveDelay(float delaySeconds);
};