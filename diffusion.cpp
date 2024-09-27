#include "diffusion.h"
#include <cmath>
#include <iostream>
#include "output.h"

void diffusion(int dimension, const SimParams& inputParameters) {
    // Extract parameters from the tuple
    const double length = std::get<0>(inputParameters);
    const double width = std::get<1>(inputParameters);
    const int nx = std::get<2>(inputParameters);
    const int ny = std::get<3>(inputParameters);
    const double endTime = std::get<4>(inputParameters);
    const double dt = std::get<5>(inputParameters);
    const double sigma = std::get<6>(inputParameters);
    const double c = std::get<7>(inputParameters);
    const double nu = std::get<8>(inputParameters);

    // Create output instance for writing results
    Output output;

    // Calculate dx
    double dx = length / (nx - 1);

    // Calculate number of time steps
    int nt = static_cast<int>(endTime / dt);

    // Initialize u
    Matrix u(1, nx, 1.0);  // Initialize with ones

    // Set initial condition: u = 2 between 0.5 and 1
    int start = static_cast<int>(0.5 / dx);
    int end = static_cast<int>(1.0 / dx) + 1;
    for (int i = start; i < end; ++i) {
        u(0, i) = 2.0;
    }

    // Write initial state
    output.writeInitialState(u);

    // Time stepping
    for (int n = 0; n < nt; ++n) {
        Matrix un = u;  // Copy current u

        for (int i = 1; i < nx - 1; ++i) {
            u(0, i) = un(0, i) + nu * (dt / (dx * dx)) * (un(0, i+1) - 2 * un(0, i) + un(0, i-1));
        }

        output.writeTimeSteps(u, n, dt, 10);
    }

    // Write final state
    output.writeFinalState(u, endTime);
}
