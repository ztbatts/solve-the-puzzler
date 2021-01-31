#include "CurryingExamples.hpp"
#include "OnlineData.hpp"
#include <vector>
#include <iostream>

/// Most/all of this would normally be auto-coded
/// ############################################################
namespace Indices {
    enum {
        MODEL_PARAM_A = 0,
        COST_A,
        COST_B,
        CONSTRAINT_A,
        CONSTRAINT_B,
        CONSTRAINT_C,
        N_PARAMS
    };
}

struct Model {
    double a;

    void toVector(std::vector<double> &vec) const {
        vec[Indices::MODEL_PARAM_A] = a;
    }
};

struct Cost {
    double a;
    double b;

    void toVector(std::vector<double> &vec) const {
        vec[Indices::COST_A] = a;
        vec[Indices::COST_B] = b;
    }
};

struct Constraint {
    double a;
    double b;
    double c;

    void toVector(std::vector<double> &vec) const {
        vec[Indices::CONSTRAINT_A] = a;
        vec[Indices::CONSTRAINT_B] = b;
        vec[Indices::CONSTRAINT_C] = c;
    }
};
/// ############################################################


template<typename T>
void printVectorizedData(const T& vec)
{
    for (const auto value : vec) {
        std::cout << value << ", \n";
    }
}


int main() {
    using MiscOnlineData = av::OnlineData<Indices::N_PARAMS, Model, Cost, Constraint>;

    const Model params{1};
    const Cost costs{2, 3};
    const Constraint constr{4, 5, 6};

    const auto vectorizedOnlineDataDefault = MiscOnlineData(params,costs,constr).toVector();

    std::cout << "No Currying: " << "\n";
    printVectorizedData(vectorizedOnlineDataDefault);

    /// Create a MiscOnlineData factory that partially defines the constructor args
    auto partialFactoryFunction = CurriedJulian(MiscOnlineData::create)(params)(costs); // doesn't allow (params,costs)

    const auto onlineData = partialFactoryFunction(constr);
    const auto vectorizedOnlineData = onlineData.toVector();

    std::cout << "Using CurriedJulian" << "\n";
    printVectorizedData(vectorizedOnlineData);


    /// Try a different implementation of Curried class
    auto factory = CurriedCukic(MiscOnlineData::create)(params,costs); // some dangling reference issue maybe...

    auto data = factory(constr);
    auto vec = data.toVector();

    std::cout << "Using CurriedCukic" << "\n";
    printVectorizedData(vec);

}