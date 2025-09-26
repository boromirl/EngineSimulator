#pragma once
#include "Engine.h"
#include "OverheatTestStand.h"
#include "MaxPowerTestStand.h"
#include <memory>

class Simulator {
private:
	std::unique_ptr<IEngine> engine;
	double timeStep;
public:
	Simulator(double dt = 1) : timeStep(dt) {}

	void initializeEngine(double environmentTemperature) {
		engine = std::make_unique<CombustionEngine>();
	}

	TestResult runOverheatTest() {
		if (!engine) throw std::runtime_error("Engine not initialized");

		OverheatTestStand test(*engine, timeStep, 1000.0);
		return test.run();
	}

	TestResult runMaxPowerTest() {
		if (!engine) throw std::runtime_error("Engine not initialized");

		MaxPowerTestStand test(*engine, timeStep, 1000.0);
		return test.run();
	}

	void setTimeStep(double dt) { timeStep = dt; }
};