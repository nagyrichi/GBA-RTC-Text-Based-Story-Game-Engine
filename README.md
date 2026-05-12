# GBA Lifeline – Text Adventure

A Game Boy Advance text adventure inspired by Lifeline, built with the Butano engine.
The game supports real-time RTC-based events, narrative progression, and a quick-play mode for testing.

---

## 📋 Prerequisites

Before building, make sure the following tools are installed.

### 1. devkitARM (via devkitPro)
Required to compile GBA binaries.

Recommended installation:
https://devkitpro.org/wiki/devkitPro_pacman

Install GBA toolchain:
sudo (dkp-pacman or pacman) -S gba-dev

Windows:
https://devkitpro.org/wiki/Getting_Started

---

### 2. Python 3
Used for asset processing and build scripts.

Check:
python3 --version

Install if needed:
- macOS: brew install python
- Linux: sudo apt install python3
- Windows: https://www.python.org

---

### 3. Git
https://git-scm.com/downloads

---

### 4. Just (optional)
- macOS: brew install just
- Linux: cargo install just
- Windows: https://github.com/casey/just

---

## 🚀 Quick Start

### Clone
git clone <repo-url> gba-lifeline
cd gba-lifeline

### Setup
./setup.sh

### Build
just build
or
make -j

### Run
Open gba_lifeline.gba in an emulator (mGBA recommended)

---

## 📁 Structure

gba-lifeline/
├── src/
├── include/
├── graphics/
├── audio/
├── external/butano/
├── build/
├── Makefile
├── justfile
├── setup.sh
└── README.md

---

## 🛠 Build commands

just build
just clean
make clean

---

## 🎮 Features

- Lifeline-style narrative
- RTC-based events
- Branching dialogue
- Quick-play mode

---

## 🧠 Main file
src/main.cpp

---

## 📚 Resources
https://github.com/vittorioromeo/butano
https://devkitpro.org/
https://www.gbadev.org/
https://mgba.io/

---

## 📄 License
Butano engine license applies (external/butano/LICENSE)
