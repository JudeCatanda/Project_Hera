<h1 align="center">Hera</h1>

Current State: **The fucking renderer is borken again**
<br>
Todo's:
- [ ] Save/Load the level to a bin file
- [ ] Fix The Fucking Camera Projection Matrix
- [ ] Optimize The fucking renderer

## 🛠️ Build Instructions (CMake + Ninja)

This project uses **CMake** with the **Ninja** build system.

---

## 📦 Requirements

Make sure you have these installed:

- **CMake**
- **Ninja**
- **C++ compiler** (GCC, Clang, MSVC)

### 🔧 Installation

#### Linux (Debian/Ubuntu Not Tested)

#### Windows (MSYS2)

```bash
pacman -Syu
pacman -S cmake ninja mingw-w64-gcc
```

---

## 🧱 Building the Project

From the project root, run this **exact command**:

```bash
cmake -G"Ninja" -Bbuild -S. -DCMAKE_BUILD_TYPE=Debug
```

Then compile:

```bash
cmake --build build or ninja
```


## 🚀 Release Build

For a faster, "optimized" version:
```bash
cmake -G"Ninja" -Bbuild -S. -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
