# img_converter

**Multithreaded Image Converter using OpenCV**

This tool converts images to a specified format using OpenCV. It supports single file input, batch processing of directories, and recursive traversal of subdirectories.

---

## Build Instructions (Cross-Platform)

### Clone the Repository

```bash
git clone https://github.com/rishlol/img_converter.git
cd img_converter
```

---

### Windows (Visual Studio 2022)

1. Open **x64 Native Tools Command Prompt for VS 2022**  
2. Run the following:

```bash
cmake -DOpenCV_DIR=<OpenCV_path> -Bbuild -S . -G "Visual Studio 17 2022"
cmake --build build --config Release
```

3. Or open the generated `build/img_converter.sln` in Visual Studio and build manually.

---

### Linux / macOS

1. Install dependencies:

Linux
```bash
sudo apt install libopencv-dev cmake g++
```

macOS
```bash
brew install opencv cmake g++
```

2. Build:

Linux/macOS (No Xcode)
```bash
cmake -Bbuild -S .
cmake --build build
```

macOS (Xcode)
```bash
cmake -Bbuild -S . -G Xcode
```

3. Run:

```bash
./build/img_converter ./images .png -r
```

---

## Usage

```bash
img_converter <input_path> <output_format> [-r]
```

- `<input_path>` — File or directory of images  
- `<output_format>` — Format to convert to (e.g. `.png`, `.jpg`)  
- `-r` — *(optional)* Recursively traverse subdirectories

---

## Example

```bash
img_converter ./photos .jpg -r
```

This converts all images inside `./photos` and its subdirectories into `.jpg`.

---

## 🛠 Supported Formats

Common formats supported by OpenCV (depending on build configuration):

- `.png`, `.jpg`, `.jpeg`, `.bmp`, `.tiff`, `.tif`  
- `.webp`, `.jp2`, `.pbm`, `.pgm`, `.ppm`, `.dib`, `.jpe`

---

## License

idk
