#pragma once
#include "TestStand.h"

class OverheatTestStand : public ITestStand {
private:
	double timeLimit;
public:
	OverheatTestStand(IEngine& eng, double dt, double maxTime)
		: ITestStand(eng, dt), timeLimit(maxTime){ }

	// !!! TODO: reset to actual temperature
	TestResult run() override {
		engine.Reset(20.0);

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