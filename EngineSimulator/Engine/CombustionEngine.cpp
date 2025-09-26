#include "Engine.h"

double CombustionEngine::calculateEngineTorque(double speed) const {
    if (speed <= speedValues.front()) return torqueValues.front();
    if (speed >= speedValues.back()) return torqueValues.back();

    // Линейная интерполяция
    for (size_t i = 0; i < speedValues.size() - 1; i++) {
        if (speed >= speedValues[i] && speed <= speedValues[i + 1]) {
            double diff = (speed - speedValues[i]) / (speedValues[i + 1] - speedValues[i]);
            return torqueValues[i] + diff * (torqueValues[i + 1] - torqueValues[i]);
        }
    }
    return torqueValues.back();
}

double CombustionEngine::calculateAcceleration() const {
    return engineTorque / inertia;
}

double CombustionEngine::calculateHeatingSpeed() const {
    return (engineTorque * hmCoef) + (crankshaftSpeed * crankshaftSpeed * hvCoef);
}

double CombustionEngine::calculateCoolingSpeed() const {
    return cCoef * (envTemperature - engineTemperature);
}

double CombustionEngine::calculateEnginePower() const {
    return engineTorque * crankshaftSpeed / 1000.0;
}

void CombustionEngine::Update(double dt) {
    crankshaftSpeed += crankshaftAcceleration * dt;
    engineTorque = calculateEngineTorque(crankshaftSpeed);

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
    crankshaftSpeed = 0.0;
    engineTemperature = environmentTemperature;
    isRunning = true;
    time = 0.0;
}