#pragma once
#include "Engine.h"

struct PowerTestResult {
	double maxPower;
	double crankshaftVelocity;
};

class HeatTestStand {
public:
	// Возвращает время в секундах, прошедшее с запуска двигателя до перегрева
	int RunTest(IEngine& engine, double environmentTemperature);
};

class MaxPowerTestStand {
public:
	PowerTestResult RunTest(IEngine& engine, double environmentTemperature);
};