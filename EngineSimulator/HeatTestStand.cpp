#include "TestStands.h"

int HeatTestStand::RunTest(IEngine& engine, double environmentTemperature) {
	engine.Start(environmentTemperature);

	int seconds = 0;
	while (!engine.IsOverheated()) {
		seconds++;
		engine.RunForOneSecond();
	}

	return seconds;
}