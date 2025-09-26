#pragma once
#include "../Engine/Engine.h"
#include "string"

struct TestResult {
	bool success;
	std::string message;
	double value1;
	double value2;
};

// Базовый класс для тестовых стендов
class TestStand {
protected:
	Engine& engine;		// тестируемый двигатель
	double timeStep;	// шаг симуляции
	double timeLimit;	// максимальное время теста
public:
	TestStand(Engine& eng, double dt, double maxTime) : engine(eng), timeStep(dt), timeLimit(maxTime) {}
	virtual ~TestStand() = default;
	TestStand(const TestStand&) = delete;
	TestStand& operator=(const TestStand&) = delete;

	virtual TestResult run() = 0;		// запуск теста
	void setTimeStep(double dt) {
		timeStep = dt;
	}
};