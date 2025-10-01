#include <iostream>
#include <cassert>
#include <string>

constexpr float MIN_TEMPERATURE = 0.0f;
constexpr float MAX_TEMPERATURE = 45.0f;
constexpr float MIN_SOC = 20.0f;
constexpr float MAX_SOC = 80.0f;
constexpr float MIN_CHARGE_RATE = 0.0f;
constexpr float MAX_CHARGE_RATE = 0.8f;

enum class BreachType {
    NORMAL,
    TOO_LOW,
    TOO_HIGH
};

// Pure function to check if a value is within range
static BreachType checkBreach(float value, float min, float max) {
    if (value < min) return BreachType::TOO_LOW;
    if (value > max) return BreachType::TOO_HIGH;
    return BreachType::NORMAL;
}

// Pure validation functions
static BreachType checkTemperature(float temperature) {
    return checkBreach(temperature, MIN_TEMPERATURE, MAX_TEMPERATURE);
}

static BreachType checkStateOfCharge(float soc) {
    return checkBreach(soc, MIN_SOC, MAX_SOC);
}

static BreachType checkChargeRate(float chargeRate) {
    return checkBreach(chargeRate, MIN_CHARGE_RATE, MAX_CHARGE_RATE);
}

// I/O functions - separate from pure logic
static void reportBreach(const std::string& parameter, BreachType breach) {
    if (breach == BreachType::TOO_LOW) {
        std::cout << parameter << " is too low!\n";
    } else if (breach == BreachType::TOO_HIGH) {
        std::cout << parameter << " is too high!\n";
    }
}

static bool validateAndReport(const std::string& parameter, BreachType breach) {
    if (breach != BreachType::NORMAL) {
        reportBreach(parameter, breach);
        return false;
    }
    return true;
}

// Example of using pure functions for different purposes (e.g., logging, alerts)
static void logBreach(const std::string& parameter, BreachType breach) {
    if (breach == BreachType::TOO_LOW) {
        // Could log to file, send alert, etc.
        std::cout << "[LOG] " << parameter << " below threshold\n";
    } else if (breach == BreachType::TOO_HIGH) {
        std::cout << "[LOG] " << parameter << " above threshold\n";
    }
}

// Example of silent validation (no I/O) - useful for automated systems
static bool isBatteryOkSilent(float temperature, float soc, float chargeRate) {
    return checkTemperature(temperature) == BreachType::NORMAL &&
           checkStateOfCharge(soc) == BreachType::NORMAL &&
           checkChargeRate(chargeRate) == BreachType::NORMAL;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    BreachType tempBreach = checkTemperature(temperature);
    BreachType socBreach = checkStateOfCharge(soc);
    BreachType chargeBreach = checkChargeRate(chargeRate);

    bool isValid = true;
    isValid &= validateAndReport("Temperature", tempBreach);
    isValid &= validateAndReport("State of Charge", socBreach);
    isValid &= validateAndReport("Charge Rate", chargeBreach);

    return isValid;
}

int main() {
    // Test normal conditions
    assert(batteryIsOk(25, 70, 0.7f) == true);
    
    // Test temperature boundaries
    assert(batteryIsOk(0, 50, 0.5f) == true);    // Min temperature
    assert(batteryIsOk(45, 50, 0.5f) == true);   // Max temperature
    assert(batteryIsOk(-1, 50, 0.5f) == false);  // Too low temperature
    assert(batteryIsOk(46, 50, 0.5f) == false);  // Too high temperature
    
    // Test state of charge boundaries
    assert(batteryIsOk(25, 20, 0.5f) == true);   // Min SOC
    assert(batteryIsOk(25, 80, 0.5f) == true);   // Max SOC
    assert(batteryIsOk(25, 19, 0.5f) == false);  // Too low SOC
    assert(batteryIsOk(25, 81, 0.5f) == false);  // Too high SOC
    
    // Test charge rate boundaries
    assert(batteryIsOk(25, 50, 0.0f) == true);   // Min charge rate
    assert(batteryIsOk(25, 50, 0.8f) == true);   // Max charge rate
    assert(batteryIsOk(25, 50, -0.1f) == false); // Too low charge rate
    assert(batteryIsOk(25, 50, 0.9f) == false);  // Too high charge rate
    
    // Test multiple parameter failures
    assert(batteryIsOk(50, 85, 0.9f) == false);  // All parameters out of range
    assert(batteryIsOk(-5, 15, 1.0f) == false);  // All parameters too low/high
    
    std::cout << "All tests passed!\n";
    return 0;
}
