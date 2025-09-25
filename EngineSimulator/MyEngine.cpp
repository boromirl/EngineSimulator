#include "Engine.h"

double MyEngine::calculateEngineTorque(double V) const {
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

double MyEngine::calculateAcceleration() const {
    return engineTorque / inertia;
}

double MyEngine::calculateHeatingSpeed() const {
    return (engineTorque * hmCoef) + (crankshaftVelocity * crankshaftVelocity * hvCoef);
}

double MyEngine::calculateCoolingSpeed() const {
    return cCoef * (envTemperature - engineTemperature);
}

double MyEngine::calculateEnginePower() const {
    return engineTorque * crankshaftVelocity / 1000.0;
}

void MyEngine::Start(double environmentTemperature) {
    this->envTemperature = environmentTemperature;
    // Температура двигателя до момента старта должна равняться температуре окружающей среды
    this->engineTemperature = environmentTemperature;
    this->isRunning = true;
}

void MyEngine::RunForOneSecond() {
    this->crankshaftVelocity += this->crankshaftAcceleration;
    this->engineTorque = calculateEngineTorque(this->crankshaftVelocity);

    this->heatingSpeed = calculateHeatingSpeed();
    this->coolingSpeed = calculateCoolingSpeed();
    this->engineTemperature += this->heatingSpeed - this->coolingSpeed;

    this->enginePower = calculateEnginePower();

    this->crankshaftAcceleration = calculateAcceleration();
    if (engineTorque <= 0) isRunning = false;
}