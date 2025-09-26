#pragma once
#include "Engine.h"
#include "string"

struct TestResult {
	bool success;
	std::string message;
	double value1;
	double value2;
};

class ITestStand {
protected:
	IEngine& engine;
	double timeStep;
public:
	ITestStand(IEngine& eng, double dt) : engine(eng), timeStep(dt) {}
	virtual ~ITestStand() = default;
	ITestStand(const ITestStand&) = delete;
	ITestStand& operator=(const ITestStand&) = delete;

	virtual TestResult run() = 0;
	void setTimeStep(double dt) {
		timeStep = dt;
	}
};