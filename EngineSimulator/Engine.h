#pragma once

#include <stdexcept>

// ��������� ��� ������ ����� ����������
class IEngine {
protected:
    IEngine() = default;
public:
	virtual ~IEngine() = default;
    IEngine(const IEngine&) = delete;
    IEngine& operator=(const IEngine&) = delete;

	virtual void Start(double environmentTemperature) = 0;
	virtual void RunForOneSecond() = 0;

	virtual const double& GetCrankshaftVelocity() const = 0;
	virtual const double& GetEngineTemperature() const = 0;
    virtual const double& GetEnginePower() const = 0;
    virtual bool IsOverheated() const = 0;
    virtual bool IsRunning() const = 0;
};

// 
class MyEngine : public IEngine{
private:
	/*  
        -------------------
        ���������� ��������
        -------------------
    */
    // ������ ������� ���������
    const int inertia = 10;
    // ����������� ���������
    const int overheatTemp = 110;
    // ����. ����������� �������� ������� �� ��������� �������
    const double hmCoef = 0.01;
    // ����. ����������� �������� ������� �� �������� �������� ���������
    const double hvCoef = 0.00001;
    // ����. ����������� �������� ���������� �� ����������� ��������� ���������� �����
    const double cCoef = 0.1;

    /*  
        ---------------------
        ���������� ����������
        ---------------------
    */
    double engineTorque;            // �������� ������ ��������� (M)
    double envTemperature;          // ����������� ���������
    double crankshaftAcceleration;  // ��������� ���������
    double heatingSpeed;            // �������� ������� ���������
    double coolingSpeed;            // �������� ���������� ���������

    /*  
        --------------------
        ��������� ����������
        --------------------
    */
    double enginePower;                     // �������� ���������
    double crankshaftVelocity;              // �������� �������� ��������� (V)
    double engineTemperature;               // ����������� ���������
    bool isRunning;                         // �������� �� ��������� (�������������� �� �������� ������)

    /*
        ----------------------------
        ������ ���������� ����������
        ----------------------------
    */
    double calculateEngineTorque(double V) const;
    double calculateAcceleration() const;
    double calculateHeatingSpeed() const;
    double calculateCoolingSpeed() const;
    double calculateEnginePower() const;

public:
    MyEngine() {
        engineTorque = 0.0;
        envTemperature = 0.0;
        crankshaftAcceleration = 0.0;
        heatingSpeed = 0.0;
        coolingSpeed = 0.0;

        enginePower = 0.0;
        crankshaftVelocity = 0.0;
        engineTemperature = 0.0;
        isRunning = false;
    }

    /*  
        -------
        �������
        -------
    */

    const double& GetCrankshaftVelocity() const override {
        return crankshaftVelocity;
    };
    const double& GetEngineTemperature() const override {
        return engineTemperature;
    }
    const double& GetEnginePower() const override {
        return enginePower;
    }

    bool IsOverheated() const override {
        return engineTemperature > overheatTemp;
    }

    bool IsRunning() const override {
        return isRunning;
    }

    /*
        -----------------------------------
        ������ ���������� ������� ���������
        -----------------------------------
    */

    void Start(double environmentTemperature) override;
    void RunForOneSecond() override;

};