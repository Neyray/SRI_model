#include <iostream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include "sri_model.h"

// A helper function to check if two floating-point numbers are close
void assert_approx(double a, double b, double epsilon = 1e-4) {
    assert(std::abs(a - b) < epsilon);
}

void run_tests() {
    SRI::SRICalculator calculator;
    std::cout << "Running SRI Model Tests..." << std::endl;

    // --- Test 1: Male Libido Function ---
    std::cout << "  - Testing Male Libido...";
    assert_approx(calculator.calculateMaleLibido(14.0), 0.0);       // Start age
    assert_approx(calculator.calculateMaleLibido(22.0), 99.9997);   // Peak age
    assert(calculator.calculateMaleLibido(20.0) < calculator.calculateMaleLibido(22.0));
    assert(calculator.calculateMaleLibido(30.0) < calculator.calculateMaleLibido(22.0));
    std::cout << " PASSED" << std::endl;

    // --- Test 2: Female Libido Function ---
    std::cout << "  - Testing Female Libido...";
    assert(calculator.calculateFemaleLibido(30.0) < calculator.calculateFemaleLibido(36.0)); // Approaching peak
    assert_approx(calculator.calculateFemaleLibido(36.0), 98.4475);  // Peak age
    assert(calculator.calculateFemaleLibido(45.0) < calculator.calculateFemaleLibido(36.0));
    std::cout << " PASSED" << std::endl;

    // --- Test 3: Marriage Market Pressure (MMP) ---
    std::cout << "  - Testing Marriage Market Pressure...";
    assert(calculator.calculateMMP(30, SRI::Gender::MALE) > calculator.calculateMMP(28, SRI::Gender::MALE));
    assert(calculator.calculateMMP(30, SRI::Gender::FEMALE) > calculator.calculateMMP(25, SRI::Gender::FEMALE));
    assert(calculator.calculateMMP(30, SRI::Gender::FEMALE) > calculator.calculateMMP(30, SRI::Gender::MALE)); // Gender asymmetry
    std::cout << " PASSED" << std::endl;

    // --- Test 4: Psychological Moderation (P_mod) ---
    std::cout << "  - Testing Psychological Moderation...";
    assert_approx(calculator.calculatePmod(0), 0.7);   // Min PCI
    assert_approx(calculator.calculatePmod(10), 1.3);  // Max PCI
    assert_approx(calculator.calculatePmod(6), 1.06);  // Average PCI
    std::cout << " PASSED" << std::endl;

    // --- Test 5: Full Archetype Calculation (IT Male at 30) ---
    std::cout << "  - Testing Full Archetype (IT Male @ 30)...";
    auto it_male = SRI::ArchetypeFactory::createITMale();
    auto components = calculator.decomposeSRI(30.0, it_male.gender, it_male.params);

    // Expected values calculated manually from the model for verification
    assert_approx(components.libido_base, 89.26, 1e-2);
    assert_approx(components.R_macro, 1.63, 1e-2);
    assert_approx(components.R_meso, 0.73, 1e-2);
    assert_approx(components.R_micro, 1.41, 1e-2);
    assert_approx(components.R_total, 1.25, 1e-2);
    assert_approx(components.SRI_final, 78.47, 1e-2);
    std::cout << " PASSED" << std::endl;

    std::cout << "\nAll tests completed successfully!\n" << std::endl;
}

int main() {
    run_tests();
    return 0;
}