# GBA Lifeline – Text Adventure

> A Game Boy Advance text adventure inspired by [Lifeline](https://www.3minute.games/) (3 Minute Games), built with the [Butano](https://github.com/GValiente/butano) engine.  
> Supports real-time RTC-based events, narrative progression, and a quick-play mode for testing.

---

## 📋 Prerequisites

Make sure the following tools are installed before building.

### 1. devkitARM (via devkitPro)

Required to compile GBA binaries.

- **Installation guide:** https://devkitpro.org/wiki/devkitPro_pacman  
- **Windows:** https://devkitpro.org/wiki/Getting_Started

```bash
sudo dkp-pacman -S gba-dev
# or: sudo pacman -S gba-dev
```

---

### 2. Python 3

Used for asset processing and build scripts.

```bash
python3 --version
```

Install if needed:

| Platform | Command |
|----------|---------|
| macOS    | `brew install python` |
| Linux    | `sudo apt install python3` |
| Windows  | https://www.python.org |

---

### 3. Git

https://git-scm.com/downloads

---

### 4. Just *(optional)*

A convenient command runner for the project.

| Platform | Command |
|----------|---------|
| macOS    | `brew install just` |
| Linux    | `cargo install just` |
| Windows  | https://github.com/casey/just |

---

## 🚀 Quick Start

### 1. Clone

```bash
git clone <repo-url> gba-lifeline
cd gba-lifeline
```

### 2. Setup

```bash
./setup.sh
```

### 3. Build

```bash
just build
# or
make -j
```

### 4. Run

Open `my_gba_game.gba` in an emulator — **[mGBA](https://mgba.io/)** is recommended.

---

## 📁 Project Structure

```
GBA-RTC-Text-Based-Story-Game-Engine/
├── src/                  # C++ source files (entry point: src/main.cpp)
├── include/              # Header files
├── graphics/             # Graphic assets
├── audio/                # Audio assets
├── external/
│   └── butano/           # Butano engine (submodule)
├── build/                # Compiled output
├── Makefile
├── justfile
├── setup.sh
└── README.md
```

---

## 🛠️ Build Commands

| Command | Description |
|---------|-------------|
| `just build` | Build the project |
| `just clean` | Clean build artifacts |
| `make -j` | Build using Make |
| `make clean` | Clean using Make |

---

## 🎮 Features

- **Lifeline-style narrative** — story driven by player choices
- **RTC-based events** — real-time clock triggers in-game moments
- **Branching dialogue** — decisions that shape the story
- **Quick-play mode** — fast testing without waiting for RTC events

---

## 📚 Resources

| Resource | Link |
|----------|------|
| Butano engine | https://github.com/GValiente/butano |
| devkitPro | https://devkitpro.org/ |
| GBA development | https://www.gbadev.org/ |
| mGBA emulator | https://mgba.io/ |

---

## 📄 License

The Butano engine license applies to all engine code.  
See [`external/butano/LICENSE`](external/butano/LICENSE) for details.

## 📄 TODOs / Roadmap

- **Improve in-game LOG feature:**
  - timestamp
  - left right allignment for different participators
- **use RTC:** 
  - in RTC mode wait real time for answers
- **proper save to file:**
  - not sure if it works now
- **time spent in game:**
  - new feature to note game time and reveal it on UI

