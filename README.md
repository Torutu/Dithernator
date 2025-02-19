# Dithernator

**Dithernator** is a C++ program designed to apply a dithering effect to images. Dithering is a technique used in digital graphics to create the illusion of color depth and smooth gradients by using patterns of contrasting pixels. This program lets you process images and apply a dithering effect, generating a new output file with the prefix "Dithered_".
![image](https://github.com/user-attachments/assets/0c7d3da7-a16b-4fa5-8427-29041ca8e188)


### Purpose

This program was created for a friend who enjoys experimenting with image processing and visual effects. It was a fun project to bring a classic image manipulation effect into action with C++ and external libraries like **stb_image** for loading and saving images.

---

## Features

- **Dithering Effect**: Applies a dithering effect to a given image, enhancing the perceived color range and visual appeal.
- **Image Output**: Saves the processed image with the prefix `Dithered_` in the same directory as the input image.
- **Cross-Platform**: It works both on Linux and Windows.

---

## How It Works

1. **Input**: The program reads an input image file (JPEG format).
2. **Dithering Process**: It applies a dithering algorithm (based on pixel error diffusion) to the image to simulate a higher color depth.
3. **Output**: The processed image is saved with the prefix `Dithered_` followed by the original image filename, resulting in a new file in the same directory.

For example, if the input image is named `image.jpg`, the output will be saved as `Dithered_image.jpg`.

---

## How to use

**Windows**
cmd or powershell
```cmd
.\dithernator.exe image.jpg
```
**Linux**
```bash
./dithernator image.jpg
```
