# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic

# Include directories
INCLUDES = -I. -I./common -I./init -I./output

# Directories
COMMON_DIR = common
INIT_DIR = init
OUTPUT_DIR = output

# Source files
SOURCES = main.cpp lin_convect.cpp nonlin_convect.cpp diffusion.cpp $(COMMON_DIR)/matrix.cpp $(INIT_DIR)/simulation_setup.cpp $(OUTPUT_DIR)/output.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = $(COMMON_DIR)/defined_types.h $(COMMON_DIR)/matrix.h $(INIT_DIR)/simulation_setup.h $(OUTPUT_DIR)/output.h lin_convect.h nonlin_convect.h diffusion.h

# Executables
EXECUTABLE1 = linear_convection
EXECUTABLE2 = nonlinear_convection
EXECUTABLE3 = diffusion_solver

# Default target
all: $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

# Rule to link the programs
$(EXECUTABLE1): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE1)

$(EXECUTABLE2): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE2)

$(EXECUTABLE3): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE3)

# Rule to compile source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJECTS) $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3) results/*.csv
	rmdir results 2>/dev/null || true

# Phony targets
.PHONY: all clean
