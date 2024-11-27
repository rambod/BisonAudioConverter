
# Bison Audio Converter

**Bison Audio Converter** is a cross-platform audio file conversion tool written in **C++** with a user-friendly GUI built using **ImGui**. The tool allows users to convert audio files to different formats while providing features like logging and streamlined workflow.

---

## Features

- **Audio Conversion**:
  - Supports WAV, MP3, and other formats (extensible via plugins).
  - Uses high-performance libraries like **libvorbis**, **lame**, and **miniaudio**.

- **ImGui-based GUI**:
  - Lightweight and responsive interface.
  - Real-time conversion logs.

- **Cross-platform**:
  - Windows and Linux support.

- **Customizable**:
  - Default window positions and flexible layouts.
  - Easy to extend with new features.

---

## Build Instructions

### Prerequisites

Ensure the following tools are installed:

- **CMake** (3.16 or higher)
- **LLVM/Clang** (or your preferred compiler)
- **vcpkg** for managing dependencies

Install the required libraries with vcpkg:

```bash
vcpkg install imgui["opengl3-binding", "glfw-binding"] fmt glfw3 libvorbis mp3lame
```

---

### Building

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/BisonAudioConverter.git
   cd BisonAudioConverter
   ```

2. Set up the build directory and generate files:
   ```bash
   cmake -S . -B cmake-build-debug -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```

3. Build the project:
   ```bash
   cmake --build cmake-build-debug
   ```

4. Run the executable:
   ```bash
   ./cmake-build-debug/BisonAudioConverter
   ```

---

## Usage

### Log Window
- View real-time logs during conversion for debugging and feedback.
- Position is customizable in `LogWindow.cpp`.

### Supported Formats
- Default supported formats:
  - `.wav` (Input)
  - `.mp3` (Output)

---

## Screenshots

| **Main Window**                            | **Log Window**                            |
|--------------------------------------------|--------------------------------------------|
| ![Main Window](screenshots/main_window.png) | ![Log Window](screenshots/log_window.png) |

---

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a feature branch:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Description of changes"
   ```
4. Submit a pull request.

---

## License

This project is licensed under the **MIT License**.

---

## Credits

- **ImGui**: Used for the GUI.
- **libvorbis**, **lame**, **fmt**: Audio and utility libraries.
- **Rambod Ghashghai**: Developer.
