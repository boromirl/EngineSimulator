#pragma once

#include <vector>

// Общий класс для разных видов двигателей
class Engine {
protected:
    Engine() = default;
public:
	virtual ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

	virtual void Update(double dt) = 0;
    virtual void Reset(double environmentTemperature) = 0;

	virtual const double& GetCrankshaftSpeed() const = 0;
	virtual const double& GetEngineTemperature() const = 0;
    virtual const double& GetEnginePower() const = 0;
    virtual const double& GetTime() const = 0;
    virtual const double& GetEnvTemperature() const = 0;
    virtual const double& GetTorque() const = 0;
    virtual bool IsOverheated() const = 0;
    virtual bool IsGeneratingTorque() const = 0;
};

// Internal Combustion Engin - Двигатель Внутреннего Сгорания
class CombustionEngine : public Engine{
private:
	/*  
        -------------------
        Постоянные значения
        -------------------
    */
   
    double inertia;                      // Момент инерции двигателя
    double overheatTemp;                 // Температура перегрева
    double hmCoef;                       // Коэф. зависимости скорости нагрева от крутящего момента
    double hvCoef;                       // Коэф. зависимости скорости нагрева от скорости вращения коленвала
    double cCoef;                        // Коэф. зависимости скорости охлаждения от температуры двигателя окружающей среды
    // Значения M и V для интерполяции
    std::vector<double> torqueValues;
    std::vector<double> speedValues;

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
    double crankshaftSpeed;                 // скорость вращения коленвала (V)
    double engineTemperature;               // температура двигателя
    double time;                            // время работы двигателя
    bool isGeneratingTorque;                // раскручивается ли двигатель

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
    // Простая версия с дефолтными значениями
    CombustionEngine(
        double environmentTemperature,
        double inertiaMoment = 10,
        double overheatTemperature = 110,
        double heatTorqueCoef = 0.01, 
        double heatSpeedCoef = 0.0001,
        double coolCoef = 0.1,
        std::vector<double> torqueValuePoints = { 20, 75, 100, 105, 75, 0 },
        std::vector<double> speedValuePoints = { 0, 75, 150, 200, 250, 300 })
        : inertia(inertiaMoment),
        overheatTemp(overheatTemperature),
        hmCoef(heatTorqueCoef),
        hvCoef(heatSpeedCoef),
        cCoef(coolCoef) ,
        torqueValues(torqueValuePoints),
        speedValues(speedValuePoints)
    {
        Reset(environmentTemperature);
    }

    /*  
        -------
        Геттеры
        -------
    */

    const double& GetCrankshaftSpeed() const override {
        return crankshaftSpeed;
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

    bool IsGeneratingTorque() const override {
        return isGeneratingTorque;
    }

    const double& GetTorque() const override {
        return engineTorque;
    }

    virtual const double& GetEnvTemperature() const {
        return envTemperature;
    }

    /*
        -----------------------------------
        Методы управления работой двигателя
        -----------------------------------
    */

    // Симуляция работы за промежуток времени dt в секундах
    void Update(double dt) override;
    // Сброс двигателя к изначальному состоянию
    void Reset(double environmentTemperature) override;
};