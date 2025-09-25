#include <iostream>
#include <limits>

#include "TestStands.h"

static void outputEngineData(IEngine& engine) {
	std::cout << "Velocity = " << engine.GetCrankshaftVelocity() << "\n" <<
		"Temperature = " << engine.GetEngineTemperature() << "\n" <<
		"Power = " << engine.GetEnginePower() << "\n" <<
		"Is overheated = " << (engine.IsOverheated() ? "True" : "False") << std::endl;
}

static void printMenu() {
	std::cout << "1) Heating test stand" << "\n" <<
		"2) Max power stand" << "\n" <<
		"3) Exit" << std::endl;
}

int main() {
	int choice = -1;
	bool flag = false;

	while (!flag) {
		std::cout << "What do you want to do?" << std::endl;
		printMenu();

		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice) {
		case 1: {
			double environmentTemperature;
			std::cout << "Environment temperature: ";
			std::cin >> environmentTemperature;

			MyEngine engine;
			int result = HeatTestStand::RunTest(engine, environmentTemperature);
			std::cout << "Heat test stand result:  " << result << "\n" << std::endl;
			break;
		}
		case 2: {
			double environmentTemperature;
			std::cout << "Environment temperature: ";
			std::cin >> environmentTemperature;

			MyEngine engine;
			PowerTestResult result = MaxPowerTestStand::RunTest(engine, environmentTemperature);
			std::cout << "Max power test stand result: \n" <<
				"  Max Power = " << result.maxPower << "\n" <<
				"  Velocity  = " << result.crankshaftVelocity << "\n" << std::endl;
			break;
		}
		case 3:
			flag = true;
			break;
		default:
			std::cout << choice << " is incorrect" << std::endl;
		}

	}

	return 0;
}