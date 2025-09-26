#include "Engine.h"

double CombustionEngine::calculateEngineTorque(double velocity) const {
    if (velocity <= velocityValues.front()) return torqueValues.front();
    if (velocity >= velocityValues.back()) return torqueValues.back();

    // Линейная интерполяция
    for (size_t i = 0; i < velocityValues.size() - 1; i++) {
        if (velocity >= velocityValues[i] && velocity <= velocityValues[i + 1]) {
            double diff = (velocity - velocityValues[i]) / (velocityValues[i + 1] - velocityValues[i]);
            return torqueValues[i] + diff * (torqueValues[i + 1] - torqueValues[i]);
        }
    }
    return torqueValues.back();
}

double CombustionEngine::calculateAcceleration() const {
    return engineTorque / inertia;
}

double CombustionEngine::calculateHeatingSpeed() const {
    return (engineTorque * hmCoef) + (crankshaftVelocity * crankshaftVelocity * hvCoef);
}

double CombustionEngine::calculateCoolingSpeed() const {
    return cCoef * (envTemperature - engineTemperature);
}

double CombustionEngine::calculateEnginePower() const {
    return engineTorque * crankshaftVelocity / 1000.0;
}

void CombustionEngine::Update(double dt) {
    crankshaftVelocity += crankshaftAcceleration * dt;
    engineTorque = calculateEngineTorque(crankshaftVelocity);

    heatingSpeed = calculateHeatingSpeed();
    coolingSpeed = calculateCoolingSpeed();
    engineTemperature += (heatingSpeed - coolingSpeed) * dt;

    enginePower = calculateEnginePower();

    crankshaftAcceleration = calculateAcceleration();
    if (crankshaftAcceleration <= 0) isRunning = false;

    time += dt;
}

void CombustionEngine::Reset(double environmentTemperature) {
    engineTorque = 0.0;
    envTemperature = environmentTemperature;
    crankshaftAcceleration = 0.0;
    heatingSpeed = 0.0;
    coolingSpeed = 0.0;

    enginePower = 0.0;
    crankshaftVelocity = 0.0;
    engineTemperature = environmentTemperature;
    isRunning = true;
    time = 0.0;
}