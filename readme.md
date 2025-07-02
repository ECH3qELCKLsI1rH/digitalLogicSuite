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
# Install GTKmm
sudo pacman -S gtkmm3  # Arch
# or
sudo apt install libgtkmm-3.0-dev  # Ubuntu

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

Simple and intuitive!

---

## 📁 File Structure

```
main.cpp                # Main file
src/
└── MainWindow.h/.cpp   # Main window
```

Clean, modular, and maintainable code.
