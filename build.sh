#!/bin/bash
set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}Building anashell...${NC}"

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo -e "${YELLOW}Configuring with CMake...${NC}"
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Build
echo -e "${YELLOW}Building...${NC}"
make -j$(nproc)

# Run tests if available
if [ -f "tests" ]; then
    echo -e "${YELLOW}Running tests...${NC}"
    ./tests
    echo -e "${GREEN}Tests passed!${NC}"
else
    echo -e "${YELLOW}No tests found${NC}"
fi

echo -e "${GREEN}Build complete! Executable: ./anashell${NC}"
