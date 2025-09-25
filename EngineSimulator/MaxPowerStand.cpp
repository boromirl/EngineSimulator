#include "TestStands.h"

PowerTestResult MaxPowerTestStand::RunTest(IEngine& engine, double environmentTemperature) {
	engine.Start(environmentTemperature);

	double maxPower = -1.0;
	double velocity = -1.0;
	while (engine.IsRunning()) {
		engine.RunForOneSecond();
		if (engine.GetEnginePower() > maxPower) {
			maxPower = engine.GetEnginePower();
			velocity = engine.GetCrankshaftVelocity();
		}
	}

	return { maxPower, velocity };
}