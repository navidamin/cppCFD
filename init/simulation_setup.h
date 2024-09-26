#ifndef SIMULATIONSETUP_H
#define SIMULATIONSETUP_H

class SimulationSetup {
private:
    double length;
    double width;
    int nx;
    int ny;
    double endTime;
    double dt;
    double sigma;
    double c;
    double nu;

public:
    SimulationSetup();

    // Getter methods
    double getLength() const { return length; }
    double getWidth() const { return width; }
    int getNx() const { return nx; }
    int getNy() const { return ny; }
    double getEndTime() const { return endTime; }
    double getDt() const { return dt; }
    double getSigma() const { return sigma; }
    double getC() const { return c; }
    double getNu() const { return nu; }

    // Setter methods
    void setLength(double l) { length = l; }
    void setWidth(double w) { width = w; }
    void setNx(int x) { nx = x; }
    void setNy(int y) { ny = y; }
    void setEndTime(double t) { endTime = t; }
    void setDt(double delta) { dt = delta; }
    void setSigma(double s) { sigma = s; }
    void setC(double coeff) { c = coeff; }
    void setNu(double n) { nu = n; }

    void readParameters();
    void getParameters(double &L, double &W, int &NX, int &NY, double &TF,
                       double &DELT, double &SIG, double &CCOEFF, double &NU);
    void printParameters() const;
};

#endif // SIMULATIONSETUP_H
