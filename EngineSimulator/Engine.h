#pragma once

#include <stdexcept>

// Интерфейс для разных видов двигателей
class IEngine {
protected:
    IEngine() = default;
public:
	virtual ~IEngine() = default;
    IEngine(const IEngine&) = delete;
    IEngine& operator=(const IEngine&) = delete;

	virtual void Start(double environmentTemperature) = 0;
	virtual void RunForOneSecond() = 0;
    virtual void Reset() = 0;

	virtual const double& GetCrankshaftVelocity() const = 0;
	virtual const double& GetEngineTemperature() const = 0;
    virtual const double& GetEnginePower() const = 0;
    virtual bool IsOverheated() const = 0;
    virtual bool IsRunning() const = 0;
};

// Internal Combustion Engin - Двигатель Внутреннего Сгорания
class CombustionEngine : public IEngine{
private:
	/*  
        -------------------
        Постоянные значения
        -------------------
    */
    // Момент инерции двигателя
    const int inertia = 10;
    // Температура перегрева
    const int overheatTemp = 110;
    // Коэф. зависимости скорости нагрева от крутящего момента
    const double hmCoef = 0.01;
    // Коэф. зависимости скорости нагрева от скорости вращения коленвала
    const double hvCoef = 0.00001;
    // Коэф. зависимости скорости охлаждения от температуры двигателя окружающей среды
    const double cCoef = 0.1;

    /*  
        ---------------------
        Внутренные переменные
        ---------------------
    */
    double engineTorque;            // Крутящий момент двигателя (M)
    double envTemperature;          // Температура окружения
    double crankshaftAcceleration;  // Ускорение коленвала
    double heatingSpeed;            // Скорость нагрева двигателя
    double coolingSpeed;            // Скорость охлаждения двигателя

    /*  
        --------------------
        Выводимые переменные
        --------------------
    */
    double enginePower;                     // Мощность двигателя
    double crankshaftVelocity;              // скорость вращения коленвала (V)
    double engineTemperature;               // температура двигателя
    bool isRunning;                         // работает ли двигатель (вырабатывается ли крутящий момент)

    /*
        ----------------------------
        Вспомогательные методы
        ----------------------------
    */
    double calculateEngineTorque(double V) const;
    double calculateAcceleration() const;
    double calculateHeatingSpeed() const;
    double calculateCoolingSpeed() const;
    double calculateEnginePower() const;

public:
    CombustionEngine() {
        Reset();
    }

    /*  
        -------
        Геттеры
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
        Методы управления работой двигателя
        -----------------------------------
    */

    void Start(double environmentTemperature) override;
    void RunForOneSecond() override;
    void Reset() override;
};