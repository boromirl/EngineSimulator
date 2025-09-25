#include <iostream>

#include "Engine.h"

void outputEngineData(MyEngine& engine) {
	std::cout << "Velocity = " << engine.GetCrankshaftVelocity() << "\n" <<
		"Temperature = " << engine.GetEngineTemperature() << "\n" <<
		"Power = " << engine.GetEnginePower() << "\n" <<
		"Is overheated = " << (engine.IsOverheated() ? "True" : "False") << std::endl;
}

int main() {
	std::cout << "Starting program!" << std::endl;

	MyEngine engine;
	outputEngineData(engine);

	engine.Start(40.0);
	outputEngineData(engine);

	//for (int i = 0; i < 1500; i++) {
	//	std::cout << "\n" <<
	//		"Iteration " << i << std::endl;
	//	engine.RunForOneSecond();
	//	outputEngineData(engine);
	//}

	int count = 1;
	while (!engine.IsOverheated()) {
		std::cout << "\n";
		std::cout << "Iteration " << count << "\n";
		engine.RunForOneSecond();
		outputEngineData(engine);
		count++;
	}

	std::cout << "Ending program!" << std::endl;

	return 0;
}