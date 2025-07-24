# 📘 Digital Logic Suite — Simple Circuit Simulator

---

## ✅ Features

- ✅ **Basic Logic Gates** - AND, OR, NOT
- ✅ **Power Sources** - Click to toggle on/off
- ✅ **Output Bulbs** - Visual feedback for circuit output
- ✅ **Wire Connections** - Click output → click input
- ✅ **Component Dragging** - Move components around
- ✅ **Real-time Simulation** - Logic updates instantly
- ✅ **Grid Layout** - Snap-to-grid positioning

---

## 🛠️ Build & Run

```bash
# Install SFML (Linux)
sudo apt install libsfml-dev  # Ubuntu/Debian
sudo pacman -S sfml          # Arch

# Or get SFML from https://www.sfml-dev.org/download.php

# Build and run
make run
```

---

## 🎯 Usage

1. **Select Component** - Click button in sidebar
2. **Place Component** - Click on canvas
3. **Connect Wires** - Click output → click input
4. **Toggle Power** - Click power sources
5. **Move Components** - Drag to reposition
6. **Clear All** - Reset circuit

Simple and intuitive with smooth SFML rendering!

---

## 📁 File Structure

```
main.cpp                # Main SFML application
src/
├── CircuitSimulator.h/.cpp  # Main simulation logic
├── GUI.h/.cpp          # SFML GUI elements
├── Components.h/.cpp   # Logic gate implementations
└── Wire.h/.cpp         # Wire connection system
```

Clean, modular, and maintainable code.

---

## 🖥️ SFML Advantages

- **Hardware-accelerated graphics** for smooth performance
- **Simple event handling** for user interactions
- **Cross-platform** support (Windows, Linux, macOS)
- **Built-in support** for textures, shapes, and text rendering
- **Lightweight** compared to full GUI toolkits