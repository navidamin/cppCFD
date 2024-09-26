#ifndef OUTPUT_H
#define OUTPUT_H
#include <cstring>
#include <iostream>

#include "matrix.h"


class Output
{
public:
    Output();

    void createDirectoryIfNotExists(const std::string& resultsDir);

    void writeToCSV(const std::string& filename, const Matrix& u, double time);

    void writeTimeSteps(const Matrix& u, int timeStep, double dt, int everyTimeStepconst );

    void writeInitialState(const Matrix& u);

    void writeFinalState(const Matrix& u, double endTime);




    const std::string resultsDir = "results";


};

#endif // OUTPUT_H
