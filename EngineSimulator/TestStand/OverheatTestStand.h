#pragma once
#include "TestStand.h"

// Тест перегрева двигателя
class OverheatTestStand : public TestStand {
public:
	OverheatTestStand(Engine& eng, double dt, double maxTime)
		: TestStand(eng, dt, maxTime) { }

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