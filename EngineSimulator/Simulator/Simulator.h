#pragma once
#include <stdexcept>
#include <memory>

#include "../Engine/Engine.h"
#include "../TestStand/OverheatTestStand.h"
#include "../TestStand/MaxPowerTestStand.h"

class Simulator {
private:
	std::unique_ptr<Engine> engine;
	double timeStep;
public:
	Simulator(double dt = 1.0) : timeStep(dt) {}

	void initializeEngine(double environmentTemperature) {
		engine = std::make_unique<CombustionEngine>(environmentTemperature);
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