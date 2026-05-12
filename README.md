# Lifeline GBA Text Adventure

This project contains a Butano-based Game Boy Advance text adventure inspired by Lifeline. It supports real-time RTC events and a quick-play mode for faster testing.

## 📋 Prerequisites

Before you start, make sure these tools are installed:

### 1. **devkitARM** (for GBA compilation)
   - **macOS**: `brew install devkitpro/devkitpro/devkitarm`
   - **Linux**: [devkitPro documentation](https://devkitpro.org/wiki/Getting_Started/devkitARM)
   - **Windows**: [devkitPro Installer](https://devkitpro.org/wiki/Getting_Started/devkitARM)

### 2. **Python 3** (for asset processing)
   - macOS/Linux: usually preinstalled
   - Check: `python3 --version`

### 3. **Git**
   - macOS/Linux: usually preinstalled
   - Windows: [Git for Windows](https://git-scm.com/download/win)

### 4. **Just** (optional build helper)
   - macOS: `brew install just`
   - Linux: `cargo install just` or `apt install just`
   - Windows: [Just installation](https://github.com/casey/just#installation)

## 🚀 Quick Start

### 1. Clone the repo
```bash
git clone <repo-url> my-gba-game
cd my-gba-game
```

### 2. Download required folders
```bash
./setup.sh
```
This downloads Butano into the `external/` folder.

### 3. Build
```bash
just build
```
Or build directly with Make:
```bash
make -j$(nproc)  # Linux/macOS
make -j%NUMBER_OF_PROCESSORS%  # Windows
```

### 4. Run the ROM
Open `my_gba_game.gba` in your emulator.

## 📁 Project Structure

```
lifeline_gba/
├── src/                    # C++ source code
├── include/                # Header files
├── graphics/               # Graphics assets
├── audio/                  # Audio assets
├── external/butano/        # Butano engine
├── build/                  # Build output
├── Makefile                # Build rules
├── justfile                # Just tasks
├── setup.sh                # Setup script
└── README.md               # This file
```

## 🛠️ Build Commands

### With Just (recommended)
```bash
just setup      # Verify Butano is available
just build      # Build the GBA ROM
just clean      # Remove build artifacts
just rebuild    # Clean and rebuild
just help       # Show available commands
```

### With Make
```bash
make            # Build
make clean      # Clean
```

## 📝 Customization

### 1. ROM Settings (Makefile)
```makefile
TARGET      := my_gba_game    # Output file name
ROMTITLE    := MY_GAME        # ROM title (max 12 characters)
ROMCODE     := MYGM           # ROM code (4 characters)
```

### 2. Game Code
- Modify `src/main.cpp`
- Add header files under `include/`
- Add graphics to `graphics/`
- Add audio files to `audio/`

### 3. Compiler Settings
In `Makefile`:
- `USERFLAGS` for extra compiler flags
- `USERLIBS` for linker libraries
- `AUDIO`, `DMGAUDIO` for audio assets

## 🐛 Troubleshooting

### "Could not locate Butano"
```bash
./setup.sh
```
Run the setup script.

### "command not found: just"
Install Just:
```bash
brew install just
```

### "devkitARM not found"
Install devkitARM:
```bash
brew install devkitpro/devkitpro/devkitarm
```

### "Python3 not found"
Install Python 3:
```bash
brew install python3
```

## 📚 Documentation & Resources

- [Butano GitHub](https://github.com/vittorioromeo/Batterytech-Cartridge)
- [Butano Documentation](https://viteorioromeo.info/Batterytech/)
- [devkitPro](https://devkitpro.org/)
- [GBA Development](https://www.gbadev.org/)

## 📄 License

This project uses Butano and follows the license included in `LICENSE`.

## 💡 Notes

- Modify `src/main.cpp` to change the game logic
- Useful Butano headers: `bn_core.h`, `bn_keypad.h`, `bn_sprite_text_generator.h`
- The `include/` and `graphics/` folders are included in the Butano build
- Use `-j` for faster builds on multi-core systems

---

If you need help, check the [Butano GitHub Issues](https://github.com/vittorioromeo/Batterytech-Cartridge/issues).



magick eredeti.png -resize 256x256! -alpha off -colors 256 -compress none BMP3:birthday.bmp