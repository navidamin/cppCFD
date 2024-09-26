#include "output.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <cerrno>
#include <cstring>

#include "matrix.h"

Output::Output()
{
    createDirectoryIfNotExists(resultsDir);
}

void Output::createDirectoryIfNotExists(const std::string& resultsDir) {
    #ifdef _WIN32
    int result = mkdir(resultsDir.c_str());
    #else
    int result = mkdir(resultsDir.c_str(), 0777);
    #endif
    if (result != 0 && errno != EEXIST) {
        std::cerr << "Error creating directory " << resultsDir << ": " << std::strerror(errno) << std::endl;
    }
}

void Output::writeToCSV(const std::string& filename, const Matrix& u, double time) {
    std::ofstream file(filename);
    file << "x,u,time\n";
    for (int i = 0; i < u.getCols(); ++i) {
        file << i * (2.0 / (u.getCols() - 1)) << "," << u(0, i) << "," << time << "\n";
    }
    file.close();
}


void Output::writeTimeSteps(const Matrix& u, int timeStep, double dt, int everyTimeStep ){
    // Write out at certain timesteps
    if (timeStep % everyTimeStep == 0) {
        std::ostringstream oss;
        oss << resultsDir << "/state_" << std::setfill('0') << std::setw(5) << timeStep << ".csv";
        writeToCSV(oss.str(), u, timeStep * dt);
    }
}

void Output::writeInitialState(const Matrix& u) {
    // Write initial state
    writeToCSV(resultsDir + "/initial_state.csv", u, 0.0);
}

void Output::writeFinalState(const Matrix& u, double endTime) {
    writeToCSV(resultsDir + "/final_state.csv", u, endTime);

    std::cout << "Simulation completed. CSV files have been written to the '" << resultsDir << "' directory." << std::endl;

}
