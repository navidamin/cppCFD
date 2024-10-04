#!/bin/bash

# Define paths
export CFDCPP_DIR="${HOME}/Documents/Developery/Cpp/cppCFD"
export SOLVER_PATH="${CFDCPP_DIR}/burgers_solver"
export VISUALIZATION_PATH="${CFDCPP_DIR}/visualization"

# Check if the defined paths exist
if [ ! -f "$SOLVER_PATH" ]; then
    echo "Error: Solver not found at $SOLVER_PATH"
    exit 1
fi

if [ ! -d "$VISUALIZATION_PATH" ]; then
    echo "Error: Visualization directory not found at $VISUALIZATION_PATH"
    exit 1
fi

# Clean the results folder
echo "Cleaning results folder..."
rm -rf results
mkdir results

# Run the linear convection solver
echo "Running linear convection solver..."
$SOLVER_PATH

# Check if the solver ran successfully
if [ $? -ne 0 ]; then
    echo "Error: The linear convection solver failed to run."
    exit 1
fi

# Plot the results
echo "Plotting results..."
python $VISUALIZATION_PATH/plot_results.py

echo "Process completed successfully."
