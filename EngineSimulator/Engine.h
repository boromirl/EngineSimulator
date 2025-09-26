#pragma once

#include <vector>

// Интерфейс для разных видов двигателей
class Engine {
protected:
    Engine() = default;
public:
	virtual ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

	virtual void Update(double dt) = 0;
    virtual void Reset(double environmentTemperature) = 0;

	virtual const double& GetCrankshaftVelocity() const = 0;
	virtual const double& GetEngineTemperature() const = 0;
    virtual const double& GetEnginePower() const = 0;
    virtual const double& GetTime() const = 0;
    virtual const double& GetEnvTemperature() const = 0;
    virtual bool IsOverheated() const = 0;
    virtual bool IsRunning() const = 0;
};

// Internal Combustion Engin - Двигатель Внутреннего Сгорания
class CombustionEngine : public Engine{
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
    // Значения M и V для интерполяции
    std::vector<double> torqueValues = { 20, 75, 100, 105, 75, 0 };
    std::vector<double> velocityValues = { 0, 75, 150, 200, 250, 300 };

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
    double time;                            // время работы двигателя

    /*
        ----------------------------
        Вспомогательные методы
        ----------------------------
    */
    double calculateEngineTorque(double velocity) const;
    double calculateAcceleration() const;
    double calculateHeatingSpeed() const;
    double calculateCoolingSpeed() const;
    double calculateEnginePower() const;

public:
    CombustionEngine(double environmentTemperature) {
        Reset(environmentTemperature);
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
    const double& GetTime() const override {
        return time;
    }

    bool IsOverheated() const override {
        return engineTemperature > overheatTemp;
    }

    bool IsRunning() const override {
        return isRunning;
    }

    virtual const double& GetEnvTemperature() const {
        return envTemperature;
    }

    /*
        -----------------------------------
        Методы управления работой двигателя
        -----------------------------------
    */

    void Update(double dt) override;
    void Reset(double environmentTemperature) override;
};