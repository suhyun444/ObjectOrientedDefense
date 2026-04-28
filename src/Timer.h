#pragma once

#include "IRoutine.h"

class Timer : public IRoutine {
private:
    float duration;
    float elapsed;
    bool finished;

public:
    explicit Timer(float duration);

    void reset();
    bool isFinished() const;
    float getElapsed() const;

    void update() override;
};
