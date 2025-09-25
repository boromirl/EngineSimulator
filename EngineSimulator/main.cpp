#include <iostream>
#include <limits>

#include "TestStands.h"

static double getDoubleInput();

int main() {
	double envTemp = 0.0;
	CombustionEngine engine;

	std::cout << "---- Engine simulation ----" << std::endl;
	std::cout << "Enter the environment temperature (in Celsius): ";
	envTemp = getDoubleInput();

	std::cout << "\nRunning overheating test..." << std::endl;
	int heatTestResult = HeatTestStand::RunTest(engine, envTemp);
	std::cout << "\nTest result:\n" <<
		"  Engine runs for " << heatTestResult << " seconds before overheating." << std::endl;

	engine.Reset();
	std::cout << "\nRunnig maximum engine power test..." << std::endl;
	PowerTestResult powerTestResult = MaxPowerTestStand::RunTest(engine, envTemp);
	std::cout << "\nTest result:\n" <<
		"  Maximum engine power achieved is " << powerTestResult.maxPower << " kilowatts with velocity " << powerTestResult.crankshaftVelocity << " radians per second" <<  std::endl;

	return 0;
}

double getDoubleInput() {
	double num;

	while (true) {
		if (std::cin >> num) {
			break;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid number.\n";
		}
	}

	return num;
}