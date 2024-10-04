#include "burgers.h"
#include <cmath>
#include <iostream>
#include "output.h"

void burgers(int dimension, const SimParams& inputParameters) {
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

    // Initialize arrays
    std::vector<int> ip1(nx, 0);
    std::vector<int> im1(nx, 0);
    std::vector<double> x(nx, 0.0);
    Matrix u(1, nx, 0.0);

    // Set up index arrays and x values
    for (int i = 1; i < nx - 1; ++i) {
        ip1[i] = i + 1;
        im1[i] = i - 1;
        x[i] = (i - 1) * dx;
    }
    ip1[nx - 1] = 0;
    im1[0] = nx - 1;

    // Set initial condition
    for (int i = 0; i < nx; ++i) {
        double phi = std::exp(-std::pow(x[i], 2) / (4 * nu)) + std::exp(-std::pow(x[i] - 2 * M_PI, 2) / (4 * nu));
        double dphi = -0.5 / nu * x[i] * std::exp(-std::pow(x[i], 2) / (4 * nu))
                      - 0.5 / nu * (x[i] - 2 * M_PI) * std::exp(-std::pow(x[i] - 2 * M_PI, 2) / (4 * nu));
        u(0, i) = -2 * nu * dphi + 4;
    }

    // Write initial state
    output.writeInitialState(u);

    // Time stepping
    for (int n = 0; n < nt; ++n) {
        Matrix un = u;  // Copy current u

        for (int i = 1; i < nx - 1; ++i) {
            u(0, i) = un(0, i) - un(0, i) * dt / dx * (un(0, i) - un(0, im1[i]))
                      + nu * dt / (dx * dx) * (un(0, ip1[i]) - 2 * un(0, i) + un(0, im1[i]));
        }

        // Apply periodic boundary conditions
        u(0, 0) = u(0, nx - 2);
        u(0, nx - 1) = u(0, 1);

        output.writeTimeSteps(u, n, dt, 10);
    }

    // Write final state
    output.writeFinalState(u, endTime);
}
