#!/bin/bash

# Butano GBA Skeleton - Setup Script
# Ez a script az összes szükséges komponenst letöltödik és beállítja

set -e  # Kilépés első hiba esetén

echo "======================================"
echo "  Butano GBA Skeleton Setup"
echo "======================================"
echo ""

# Szinek a kimenethez
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Függvény: hiba üzenet
error() {
    echo -e "${RED}✗ HIBA: $1${NC}"
    exit 1
}

# Függvény: siker üzenet
success() {
    echo -e "${GREEN}✓ $1${NC}"
}

# Függvény: figyelmeztetés
warn() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

# Függvény: info üzenet
info() {
    echo -e "${YELLOW}ℹ $1${NC}"
}

# 1. DevkitARM ellenőrzése
echo "1️⃣  DevkitARM ellenőrzése..."
if ! command -v arm-none-eabi-gcc &> /dev/null; then
    error "devkitARM nem található! Telepítsd:"
    echo "  macOS: brew install devkitpro/devkitpro/devkitarm"
    echo "  Linux: https://devkitpro.org/wiki/Getting_Started/devkitARM"
    echo "  Windows: https://devkitpro.org/wiki/Getting_Started/devkitARM"
fi
success "devkitARM megtalálva: $(arm-none-eabi-gcc --version | head -1)"
echo ""

# 2. Python3 ellenőrzése
echo "2️⃣  Python3 ellenőrzése..."
if ! command -v python3 &> /dev/null; then
    error "Python3 nem található! Telepítsd:"
    echo "  macOS: brew install python3"
    echo "  Linux: sudo apt install python3"
    echo "  Windows: https://www.python.org/downloads/"
fi
success "Python3 megtalálva: $(python3 --version)"
echo ""

# 3. Git ellenőrzése
echo "3️⃣  Git ellenőrzése..."
if ! command -v git &> /dev/null; then
    error "Git nem található! Telepítsd: https://git-scm.com/"
fi
success "Git megtalálva: $(git --version)"
echo ""

# 4. Butano letöltése/frissítése
echo "4️⃣  Butano kezelése..."
BUTANO_DIR="external/butano"

if [ -d "$BUTANO_DIR" ]; then
    info "Butano mappa már létezik: $BUTANO_DIR"
    read -p "Frissítsd a Butano-t? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        cd "$BUTANO_DIR"
        git fetch origin
        git pull origin main || git pull origin master
        cd ../..
        success "Butano frissítve"
    else
        info "Butano nem frissítve"
    fi
else
    info "Butano nem található, letöltés..."
    mkdir -p external
    cd external
    git clone https://github.com/vittorioromeo/Butano.git butano
    cd ..
    success "Butano letöltve: $BUTANO_DIR"
fi
echo ""

# 5. Just ellenőrzése (opcionális)
echo "5️⃣  Just ellenőrzése (opcionális)..."
if command -v just &> /dev/null; then
    success "Just telepítve: $(just --version)"
else
    warn "Just nem található (opcionális)"
    echo "  Telepítsd ha szeretnéd: brew install just"
    echo "  Vagy közvetlenül make-t tudsz használni"
fi
echo ""

# Végeredmény
echo "======================================"
success "Setup befejezve!"
echo "======================================"
echo ""
echo "Következő lépések:"
echo "  1. Szerkeszd a Makefile-t (TARGET, ROMTITLE, ROMCODE)"
echo "  2. Módosítsd a src/main.cpp fájlt"
echo "  3. Fordíts: just build   (vagy: make -j\$(nproc))"
echo ""
