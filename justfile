set shell := ["/bin/bash", "-c"]

_jobs := "$(command -v nproc >/dev/null 2>&1 && nproc || sysctl -n hw.logicalcpu)"

# Setup: Downloads and verifies Butano
setup:
    @./setup.sh

# Build: Compiles the GBA ROM
build:
    make -j{{_jobs}}

# Clean: Removes build artifacts
clean:
    make clean

# Full rebuild: Clean and build
rebuild: clean build

# Help: Shows available commands
help:
    @echo "Available commands:"
    @echo "  just setup    - Download and setup Butano"
    @echo "  just build    - Build the GBA ROM"
    @echo "  just clean    - Clean build artifacts"
    @echo "  just rebuild  - Clean and build"
