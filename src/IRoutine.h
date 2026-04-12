#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

class IRoutine {
public:
    virtual ~IRoutine() = default;
    virtual void update() = 0; 
    virtual bool isAlive() const { return true; } 
};