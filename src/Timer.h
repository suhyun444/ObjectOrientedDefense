#pragma once

class Timer {
private:
    float duration;
    float elapsed;
    bool finished;

public:
    explicit Timer(float duration);

    void reset();
    void reset(float newDuration);
    bool isFinished() const;
    float getElapsed() const;

    void tick();
};
