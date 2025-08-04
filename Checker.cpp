#include <iostream>
#include <cassert>

constexpr float MIN_TEMPERATURE = 0.0f;
constexpr float MAX_TEMPERATURE = 45.0f;
constexpr float MIN_SOC = 20.0f;
constexpr float MAX_SOC = 80.0f;
constexpr float MAX_CHARGE_RATE = 0.8f;

static bool isTemperatureValid(float temperature) {
    if (temperature < MIN_TEMPERATURE || temperature > MAX_TEMPERATURE) {
        std::cout << "Temperature out of range!\n";
        return false;
    }
    return true;
}

static bool isStateOfChargeValid(float soc) {
    if (soc < MIN_SOC || soc > MAX_SOC) {
        std::cout << "State of Charge out of range!\n";
        return false;
    }
    return true;
}

static bool isChargeRateValid(float chargeRate) {
    if (chargeRate > MAX_CHARGE_RATE) {
        std::cout << "Charge Rate out of range!\n";
        return false;
    }
    return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return isTemperatureValid(temperature) &&
           isStateOfChargeValid(soc) &&
           isChargeRateValid(chargeRate);
}

int main() {
    assert(batteryIsOk(25, 70, 0.7f) == true);
    assert(batteryIsOk(50, 85, 0) == false);
    return 0;
}
