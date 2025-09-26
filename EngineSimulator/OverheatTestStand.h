#pragma once
#include "TestStand.h"

class OverheatTestStand : public TestStand {
private:
	double timeLimit;
public:
	OverheatTestStand(Engine& eng, double dt, double maxTime)
		: TestStand(eng, dt), timeLimit(maxTime){ }

	TestResult run() override {
		engine.Reset(engine.GetEnvTemperature());

		while (engine.GetTime() < timeLimit) {
			if (engine.IsOverheated()) {
				return {
					true,
					"Engine overheated after " + std::to_string(engine.GetTime()) + " seconds",
					engine.GetTime(),
					0.0
				};
			}
			engine.Update(timeStep);
		}

		return {
			false,
			"Engine did not overheat within " + std::to_string(timeLimit) + " seconds",
			timeLimit,
			0.0
		};
	}
};