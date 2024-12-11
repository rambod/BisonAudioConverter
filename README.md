# Bison Audio Converter

**Bison Audio Converter** is a cross-platform audio file conversion tool written in **C++** with a user-friendly GUI built using **ImGui** and **SFML**. The tool is designed for **batch and bulk audio conversion**, making it ideal for large-scale tasks where preserving directory structures is crucial.

---

## Features

- **Batch and Bulk Audio Conversion**:
  - Convert entire directories and subdirectories containing thousands (even millions) of audio files.
  - Automatically **mimics the input directory structure** in the output directory, preserving the original file organization.
  - Handles large-scale conversions efficiently.

- **Audio Format Support**:
  - Supports conversion between **WAV** and **MP3** formats.
  - Uses high-performance libraries like **miniaudio** and **LAME** for encoding.

- **ImGui-based GUI**:
  - Lightweight and responsive interface built with **ImGui** and **SFML**.
  - Real-time conversion logs for easy feedback and debugging.

- **Cross-platform**:
  - Supports **Windows** and **Linux**.

- **Customizable**:
  - Default window positions and flexible layouts.
  - Easy to extend with new features and formats.

---

## Build Instructions

### Prerequisites

Ensure the following tools and libraries are installed:

- **CMake** (3.16 or higher)
- **LLVM/Clang** (or your preferred compiler)
- **vcpkg** for managing dependencies

Install the required libraries with **vcpkg**:

```bash
vcpkg install imgui[sfml-binding] sfml fmt libmp3lame miniaudio
```

---

### Building

1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/BisonAudioConverter.git
   cd BisonAudioConverter
   ```

2. Set up the build directory and generate the build files:
   ```bash
   cmake -S . -B cmake-build-release -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```

3. Build the project:
   ```bash
   cmake --build cmake-build-release
   ```

4. Run the executable:
   ```bash
   ./cmake-build-release/BisonAudioConverter
   ```

---

## Usage

### Batch Conversion

- **Convert Entire Directories**: Select an input directory containing audio files, and Bison Audio Converter will convert all supported files within that directory and its subdirectories.
- **Preserve Directory Structure**: The output directory will mimic the structure of the input directory, maintaining the original file organization.
- **Scalability**: Efficiently handles large-scale conversions, even with millions of files.

### Log Window

- View real-time logs during conversion for debugging and feedback.
- Log position is customizable in `MainWindow.cpp`.

### Supported Formats

- **Input Format**: `.wav`
- **Output Formats**: `.wav`, `.mp3`

---

## Screenshots

| **Main Window**                            | **Log Window**                            |
|--------------------------------------------|-------------------------------------------|
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
- **SFML**: For windowing and graphics.
- **miniaudio**: For audio decoding.
- **LAME**: For MP3 encoding.
- **fmt**: For formatted output.
- **Rambod Ghashghai**: Developer.
