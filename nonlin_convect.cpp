#include "nonlin_convect.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

void createDirectoryIfNotExists(const std::string& path) {
    #ifdef _WIN32
    int result = mkdir(path.c_str());
    #else
    int result = mkdir(path.c_str(), 0777);
    #endif
    if (result != 0 && errno != EEXIST) {
        std::cerr << "Error creating directory " << path << ": " << std::strerror(errno) << std::endl;
    }
}

void writeToCSV(const std::string& filename, const Matrix& u, double time) {
    std::ofstream file(filename);
    file << "x,u,time\n";
    for (int i = 0; i < u.getCols(); ++i) {
        file << i * (2.0 / (u.getCols() - 1)) << "," << u(0, i) << "," << time << "\n";
    }
    file.close();
}

void nonLinConvect(int dimension, const SimParams& inputParameters) {
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

    // Create results directory
    const std::string resultsDir = "results";
    createDirectoryIfNotExists(resultsDir);

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
    writeToCSV(resultsDir + "/initial_state.csv", u, 0.0);

    // Time stepping
    for (int n = 0; n < nt; ++n) {
        Matrix un = u;  // Copy current u

        for (int i = 1; i < nx; ++i) {
            u(0, i) = un(0, i) - un(0, i) * dt / dx * (un(0, i) - un(0, i-1));
        }

        // Write out at certain timesteps
        if (n % 10 == 0) {
            std::ostringstream oss;
            oss << resultsDir << "/state_" << std::setfill('0') << std::setw(5) << n << ".csv";
            writeToCSV(oss.str(), u, n * dt);
        }
    }

    // Write final state
    writeToCSV(resultsDir + "/final_state.csv", u, endTime);

    std::cout << "Simulation completed. CSV files have been written to the '" << resultsDir << "' directory." << std::endl;
}
