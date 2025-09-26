#include <iostream>
#include <limits>
#include "Simulator/Simulator.h"

// консольный ввод одного double значения с проверкой
static double getDoubleInput();
// консольный вывод результата теста
static void printResult(const TestResult& result);

int main() {
	std::cout << "--- Engine simulator ---" << std::endl;
	std::cout << std::endl;

	std::cout << "Enter the environment temperature (in Celsius): ";
	double environmentTemperature = getDoubleInput();

	Simulator simulator(0.001);

	try {
		simulator.initializeEngine(environmentTemperature);

		std::cout << "\nRunning overheating test...\n" << std::endl;
		TestResult overheatResult = simulator.runOverheatTest();
		printResult(overheatResult);

		std::cout << "\nRunning Max power test...\n" << std::endl;
		TestResult maxPowerResult = simulator.runMaxPowerTest();
		printResult(maxPowerResult);
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	std::cout << "\n--- Simulation finished ---" << std::endl;
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

void printResult(const TestResult& result) {
	std::cout << (result.success ? "SUCCESS " : "FAIL ") << result.message << std::endl;
}