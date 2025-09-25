// EngineSimulator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream> 

int main()
{
    std::cout << "Hello World!\n";
}

class Engine {
    // ---------------------
    //      Постоянные
    // ---------------------
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

    // Получение крутящего момента M, вырабатываемого двигателем от скорости вращения коленвала V
    int getEngineTorque(double V) {
        if (V < 0) {
            throw std::invalid_argument("Crankshaft speed (V) cannot be negative.");
            // можно вместо этого return -1;
        }

        // Кусочно-линейная зависимость
        if (V >= 0 && V < 75) return 20;
        else if (V >= 75 && V < 150) return 75;
        else if (V >= 150 && V < 200) return 100;
        else if (V >= 200 && V < 250) return 105;
        else if (V >= 250 && V < 300) return 75;
        else if (V >= 300) return 0;
    }

    // -----------------------
    //  Промежуточные данные
    // -----------------------
    double engineTorque;            // Крутящий момент двигателя (M)
    int envTemperature;             // Температура окружения
    double crankshaftAcceleration;  // Ускорение коленвала

    double getAcceleration() {
        return engineTorque / inertia;
    }

    double getHeatingSpeed() {
        return (engineTorque * hmCoef) + (crankshaftVelocity * crankshaftVelocity * hvCoef);
    }

    double getCoolingSpeed() {
        return cCoef * (envTemperature - engineTemperature);
    }

    // Вычисление мощности двигателя N на данный момент
    double getEnginePower() {
        return getEngineTorque(crankshaftVelocity) * crankshaftVelocity / 1000.0;
    }

public:
    // -----------------------
    // Симулируемые значения
    // -----------------------
    double crankshaftVelocity;              // скорость вращения коленвала (V)
    double engineTemperature;               // температура двигателя

    Engine() {
        engineTorque = 0.0;
        envTemperature = 0.0;
        crankshaftVelocity = 0.0;
        engineTemperature = 0.0;
    }

    ~Engine() = default;

    void Start(double environmentTemperature) {
        this->envTemperature = environmentTemperature;
        // Температура двигателя до момента старта должна равняться температуре окружающей среды
        this->engineTemperature = environmentTemperature;
    }

    void simulateSecond() {
        this->engineTorque = getEngineTorque(this->crankshaftVelocity);
        this->crankshaftAcceleration = getAcceleration();
        crankshaftVelocity += crankshaftAcceleration;
    }
};