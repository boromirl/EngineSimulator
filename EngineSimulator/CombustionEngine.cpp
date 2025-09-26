#include "Engine.h"

double CombustionEngine::calculateEngineTorque(double V) const {
    if (V < 0) {
        throw std::invalid_argument("Crankshaft speed (V) cannot be negative.");
        // можно вместо этого return -1;
    }

    // Кусочно-линейная зависимость
    if (V >= 0 && V < 75) return 20;
    else if (V >= 75 && V < 150) return 75;
    else if (V >= 150 && V < 200) return 100;
    else if (V >= 200 && V < 250) return 105;
    else if (V >= 250 && V < 300) return 75;
    else if (V >= 300) return 0;
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

void CombustionEngine::Start(double environmentTemperature) {
    this->envTemperature = environmentTemperature;
    // Температура двигателя до момента старта должна равняться температуре окружающей среды
    this->engineTemperature = environmentTemperature;
    this->isRunning = true;
}

void CombustionEngine::Update(double dt) {
    crankshaftVelocity += crankshaftAcceleration * dt;
    engineTorque = calculateEngineTorque(crankshaftVelocity);

    heatingSpeed = calculateHeatingSpeed();
    coolingSpeed = calculateCoolingSpeed();
    engineTemperature += (heatingSpeed - coolingSpeed) * dt;

    enginePower = calculateEnginePower();

    crankshaftAcceleration = calculateAcceleration();
    if (engineTorque <= 0) isRunning = false;
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
    isRunning = false;
    time = 0.0;
}