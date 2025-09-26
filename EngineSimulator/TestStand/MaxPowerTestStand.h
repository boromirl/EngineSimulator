#pragma once
#include "TestStand.h"

class MaxPowerTestStand : public TestStand {
public:
	MaxPowerTestStand(Engine& eng, double dt, double maxTime)
		: TestStand(eng, dt, maxTime) { }

	TestResult run() override {
		engine.Reset(engine.GetEnvTemperature());
	
		double maxPower = 0.0;
		double speedAtMax = 0.0;

		while (engine.GetTime() < timeLimit && engine.IsRunning()) {
			double currentPower = engine.GetEnginePower();

			if (currentPower > maxPower) {
				maxPower = currentPower;
				speedAtMax = engine.GetCrankshaftSpeed();
			}

			engine.Update(timeStep);
		}

		return {
			true,
			"Max power: " + std::to_string(maxPower) + " kilowatts with " +
			std::to_string(speedAtMax) + " radians per second",
			maxPower,
			speedAtMax
		};
	}
};