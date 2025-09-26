#pragma once
#include "TestStand.h"

class MaxPowerTestStand : public ITestStand {
private:
	double timeLimit;		// ??? to parent class ???

public:
	MaxPowerTestStand(IEngine& eng, double dt, double maxTime)
		: ITestStand(eng, dt), timeLimit(maxTime) { }

	TestResult run() override {
		engine.Reset(20.0);		/// !!!!!!!!!!!!!! FIX to actual temprerature
	
		double maxPower = 0.0;
		double velocityAtMax = 0.0;

		while (engine.GetTime() < timeLimit && engine.IsRunning()) {
			double currentPower = engine.GetEnginePower();

			if (currentPower > maxPower) {
				maxPower = currentPower;
				velocityAtMax = engine.GetCrankshaftVelocity();
			}
		}

		return {
			true,
			"Max power: " + std::to_string(maxPower) + " kilowatts with " +
			std::to_string(velocityAtMax) + " radians per second",
			maxPower,
			velocityAtMax
		};
	}
};