#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "simulation_setup.h"

SimulationSetup::SimulationSetup()
{
    // Initialize with some default values
    setLength(0.0);
    setWidth(0.0);
    setNx(1);
    setNy(1);
    setEndTime(1.0);
    setDt(0.01);
    setSigma(0.0);
    setC(0.0);
    setNu(0.00);
}

void SimulationSetup::readParameters() {
    std::ifstream file("setupDict");
    if (!file.is_open()) {
        std::cerr << "Error opening setupDict file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        double value;

        if (iss >> key >> value) {
            if (key == "length") setLength(value);
            else if (key == "width") setWidth(value);
            else if (key == "nx") setNx(static_cast<int>(value));
            else if (key == "ny") setNy(static_cast<int>(value));
            else if (key == "endTime") setEndTime(value);
            else if (key == "dt") setDt(value);
            else if (key == "sigma") setSigma(value);
            else if (key == "c") setC(value);
            else if (key == "nu") setNu(value);
            else std::cerr << "Unknown parameter: " << key << std::endl;
        }
    }

    file.close();
}

void SimulationSetup::getParameters(double &L, double &W, int &NX, int &NY, double &TF,
                                    double &DELT, double &SIG, double &CCOEFF, double &NU) {
    L = getLength();
    W = getWidth();
    NX = getNx();
    NY = getNy();
    TF = getEndTime();
    DELT = getDt();
    SIG = getSigma();
    CCOEFF = getC();
    NU = getNu();
}

void SimulationSetup::printParameters() const {
    std::cout << "Simulation Parameters: \n";
    std::cout << "Length: " << getLength() << "\n";
    std::cout << "Width: " << getWidth() << "\n";
    std::cout << "Nx: " << getNx() << "\n";
    std::cout << "Ny: " << getNy() << "\n";
    std::cout << "EndTime: " << getEndTime() << "\n";
    std::cout << "Dt: " << getDt() << "\n";
    std::cout << "Sigma: " << getSigma() << "\n";
    std::cout << "C: " << getC() << "\n";
    std::cout << "Nu: " << getNu() << "\n";
}
