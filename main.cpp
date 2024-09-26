
#include <vector>
#include <string>
#include <iostream>

using namespace std;
#include "lin_convect.h"
#include "nonlin_convect.h"
#include "simulation_setup.h"
#include "defined_types.h"


int main() {


    // INITIALIZATION

    // read paramaters
    double length, width, endTime, dt, sigma, c, nu ;
    int nx, ny;

    SimulationSetup simSetup;
    simSetup.readParameters();
    simSetup.getParameters(length, width, nx, ny, endTime, dt, sigma, c, nu );

    const SimParams inputParameters = std::make_tuple(length, width, nx, ny, endTime, dt, sigma, c, nu);

    // SOLVING
    //linConvect(1,inputParameters);      // linConvect( int dimension, vector<double> inputParameters);
    nonLinConvect(1,inputParameters);    // nonLinConvect( int dimension, vector<double> inputParameters);



    return 0;
}

