#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "sri_model.h"

void run_simulation_for_archetype(const SRI::Archetype& archetype, const SRI::SRICalculator& calculator) {
    std::cout << "============================================================" << std::endl;
    std::cout << "Simulation for Archetype: " << archetype.name << std::endl;
    std::cout << "(" << archetype.description << ")" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(8) << "Age"
              << std::setw(15) << "Libido Base"
              << std::setw(15) << "Total Rep."
              << std::setw(12) << "Final SRI" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    for (double age = 20.0; age <= 50.0; age += 2.0) {
        auto components = calculator.decomposeSRI(age, archetype.gender, archetype.params);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::left << std::setw(8) << age
                  << std::setw(15) << components.libido_base
                  << std::setw(15) << components.R_total
                  << std::setw(12) << components.SRI_final << std::endl;
    }
    std::cout << "============================================================" << std::endl << std::endl;
}

int main() {
    SRI::SRICalculator calculator;
    
    // Get all predefined archetypes from the factory
    auto archetypes = SRI::ArchetypeFactory::getAllArchetypes();
    
    // Run simulation for each archetype
    for (const auto& archetype : archetypes) {
        run_simulation_for_archetype(archetype, calculator);
    }

    return 0;
}