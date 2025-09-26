#pragma once
#include "Engine.h"
#include "string"

struct TestResult {
	bool success;
	std::string message;
	double value1;
	double value2;
};

class TestStand {
protected:
	Engine& engine;
	double timeStep;
public:
	TestStand(Engine& eng, double dt) : engine(eng), timeStep(dt) {}
	virtual ~TestStand() = default;
	TestStand(const TestStand&) = delete;
	TestStand& operator=(const TestStand&) = delete;

	virtual TestResult run() = 0;
	void setTimeStep(double dt) {
		timeStep = dt;
	}
};