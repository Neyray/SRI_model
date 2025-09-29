#pragma once
#include <string>
#include <vector>

namespace SRI {

enum class Gender {
    MALE,
    FEMALE
};

struct ArchetypeParams {
    double PCI = 0.0;            // Psychological/Contextual Index used by P_mod
    double macro_bias = 0.0;     // optional bias to R_macro
    double meso_bias = 0.0;      // optional bias to R_meso
    double micro_bias = 0.0;     // optional bias to R_micro
};

struct Archetype {
    std::string name;
    std::string description;
    Gender gender;
    ArchetypeParams params;
};

struct SRIComponents {
    double libido_base = 0.0;
    double R_macro = 1.0;
    double R_meso = 1.0;
    double R_micro = 1.0;
    double R_total = 1.0;
    double SRI_final = 0.0;
};

class SRICalculator {
public:
    // Libido functions
    double calculateMaleLibido(double age) const;
    double calculateFemaleLibido(double age) const;

    // Marriage Market Pressure (monotonic-ish functions; gender asymmetry)
    double calculateMMP(int age, Gender gender) const;

    // Psychological moderation: maps PCI in [0,10] to [0.7,1.3] linearly
    double calculatePmod(double PCI) const;

    // Decompose the full SRI at a given age and archetype params
    SRIComponents decomposeSRI(double age, Gender gender, const ArchetypeParams& params) const;
};

class ArchetypeFactory {
public:
    static Archetype createITMale();
    static std::vector<Archetype> getAllArchetypes();
};

} // namespace SRI
