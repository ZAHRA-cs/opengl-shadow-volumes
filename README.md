# OpenGL Shadow Volumes

<div align="center">

![OpenGL](https://img.shields.io/badge/OpenGL-3.3-blue.svg)
![C++](https://img.shields.io/badge/C++-17-00599C.svg?logo=c%2B%2B)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6.svg?logo=windows)
![License](https://img.shields.io/badge/License-MIT-green.svg)

*Real-time shadow rendering using stencil shadow volumes with the Z-FAIL algorithm*

[Features](#-features) • [Demo](#-demo) • [Technical Details](#-technical-details) • [Building](#-building--running) • [Usage](#-usage)

</div>

---

## 📋 Overview

This project implements **shadow volumes** (stencil shadows) using OpenGL to create realistic, dynamic shadows in real-time 3D scenes. The implementation uses the **Z-FAIL** algorithm (also known as **Carmack's Reverse**) with proper front and back shadow caps, making it robust even when the camera is inside the shadow volume.

**Academic Context:**
- **Course:** Computer Graphics
- **Institution:** Nanjing University of Posts and Telecommunications (NJUPT)
- **Student ID:** F23040129
- **Year:** 2024-2025

---

## ✨ Features

### Core Rendering
- ✅ **Shadow Volume Generation** - Dynamic generation of shadow volumes from geometry
- ✅ **Z-FAIL Algorithm** - Robust shadow rendering using Carmack's Reverse method
- ✅ **Stencil Buffer Rendering** - Hardware-accelerated stencil operations
- ✅ **Front & Back Caps** - Properly capped shadow volumes for correctness
- ✅ **Silhouette Edge Detection** - Efficient edge detection for shadow volume construction

### Scene Features
- 🎨 **Animated Point Light** - Light source moving in an elliptical path
- 🎲 **Tilted Cube** - Main shadow-casting object rotated at 45° on (1,0,1) axis
- 🌍 **Ground Plane** - Large surface receiving shadows
- 📷 **Interactive Camera** - First-person camera with mouse and keyboard controls
- 🔆 **Phong Lighting** - Separate ambient and diffuse+specular passes

### Visual Quality
- 🌗 **Soft Shadow Edges** - Smooth shadow transitions
- 🎭 **Proper Depth Testing** - Correct occlusion handling
- 🎨 **Multi-colored Geometry** - Each face of the cube has a distinct color
- 💡 **Visible Light Source** - Small yellow cube represents the light position

---

## 🎥 Demo

### Screenshots

<div align="center">
  <img src="docs/screenshots/demo1.png" width="45%" alt="Shadow rendering with light source" />
  <img src="docs/screenshots/demo2.png" width="45%" alt="Shadow from different angle" />
</div>

**Key Features Shown:**
- ✨ Realistic shadow casting from tilted cube onto ground plane
- 💡 Visible light source (white cube) showing current position
- 🎨 Multi-colored cube faces with proper shading
- 🌗 Sharp, well-defined shadow edges using stencil buffer
- 🔄 Dynamic shadow that changes with light movement

### Video Demo

*Optional: Add a short video showing the animated light movement and shadow dynamics*

<!-- Uncomment and add your video link when ready:
[Watch Demo Video](link-to-your-video)
-->

---

## 🔧 Technical Details

### Shadow Volume Algorithm

This implementation uses the **Z-FAIL** method with the following steps:

1. **Silhouette Detection**
   - Identify edges shared by front-facing and back-facing triangles
   - These edges form the silhouette from the light's perspective

2. **Volume Construction**
   - Create **front cap** from lit faces
   - Create **back cap** from unlit faces (extruded far away)
   - Build **side quads** by extruding silhouette edges

3. **Stencil Operations** (Z-FAIL specific)
   ```cpp
   // Front-facing shadow geometry: increment stencil on depth failure
   glStencilOp(GL_KEEP, GL_INCR, GL_KEEP);
   
   // Back-facing shadow geometry: decrement stencil on depth failure
   glStencilOp(GL_KEEP, GL_DECR, GL_KEEP);
   ```

4. **Final Rendering**
   - Render ambient pass normally
   - Render lit areas only where stencil == 0

### Architecture

```
┌─────────────────┐
│  Main Loop      │
└────────┬────────┘
         │
    ┌────▼─────┐
    │ Update   │
    │ Light    │
    │ Position │
    └────┬─────┘
         │
    ┌────▼─────────────┐
    │ Build Shadow     │
    │ Volume           │
    │ - Detect lit     │
    │   faces          │
    │ - Find silhou-   │
    │   ette edges     │
    │ - Extrude geom   │
    └────┬─────────────┘
         │
    ┌────▼─────────────┐
    │ Ambient Pass     │
    │ (stencil=keep)   │
    └────┬─────────────┘
         │
    ┌────▼─────────────┐
    │ Shadow Volume    │
    │ Pass (Z-FAIL)    │
    │ - Front faces    │
    │ - Back faces     │
    └────┬─────────────┘
         │
    ┌────▼─────────────┐
    │ Lighting Pass    │
    │ (stencil==0)     │
    └──────────────────┘
```

### Technology Stack

| Component | Technology |
|-----------|-----------|
| **Graphics API** | OpenGL 3.3 Core Profile |
| **Window Management** | GLFW 3.x |
| **Extension Loading** | GLEW |
| **Mathematics** | GLM (OpenGL Mathematics) |
| **Language** | C++17 |
| **Shading Language** | GLSL 330 |
| **Build System** | Visual Studio 2022 (v143) |

### Key Implementation Details

- **Extrusion Length:** 50 units (prevents far-plane clipping)
- **Light Animation:** Parametric ellipse with period ~10s
- **Camera Speed:** 6 units/second
- **Viewport:** 800×600 default resolution
- **Background:** Dark blue-gray (#262633)

---

## 🛠️ Building & Running

### Prerequisites

#### Required Software
- **Visual Studio 2022** (or 2019 with v142 toolset)
- **Windows SDK 10.0** or later
- **Git** (for cloning)

#### Required Libraries
The project expects external libraries in an `External/` directory:

```
External/
├── GLEW/
│   ├── include/
│   └── lib/Release/x64/
├── GLFW/
│   ├── include/
│   └── lib-vc2022/
└── glm/
    └── glm/
```

### Installation

#### 1. Clone the Repository
```bash
git clone https://github.com/ZAHRA-cs/opengl-shadow-volumes.git
cd opengl-shadow-volumes
```

#### 2. Set Up External Libraries

**Option A: Manual Setup**
1. Download [GLEW](http://glew.sourceforge.net/) (Binary version)
2. Download [GLFW](https://www.glfw.org/download.html) (Pre-compiled Windows binaries)
3. Download [GLM](https://github.com/g-truc/glm/releases)
4. Extract them into an `External/` folder following the structure above

**Option B: Using Package Managers**
```bash
# Using vcpkg
vcpkg install glew:x64-windows glfw3:x64-windows glm:x64-windows
```

#### 3. Copy Required DLLs
Copy these DLLs to your build output directory:
- `glew32.dll` (from GLEW package)
- `glfw3.dll` (from GLFW package)

### Building

#### Using Visual Studio GUI
1. Open `final-project-zahra.sln`
2. Select **Debug** or **Release** configuration
3. Set platform to **x64**
4. Build the solution (`Ctrl+Shift+B`)
5. Run (`F5` or `Ctrl+F5`)

#### Using MSBuild (Command Line)
```bash
# Debug build
msbuild final-project-zahra.sln /p:Configuration=Debug /p:Platform=x64

# Release build
msbuild final-project-zahra.sln /p:Configuration=Release /p:Platform=x64
```

### Running
```bash
# From build directory
cd x64/Debug
./final-project-zahra.exe
```

Or simply press `F5` in Visual Studio!

---

## 🎮 Usage

### Controls

| Input | Action |
|-------|--------|
| **Mouse Movement** | Look around (rotate camera) |
| **W** | Move forward |
| **S** | Move backward |
| **A** | Strafe left |
| **D** | Strafe right |
| **ESC** | Close application |

### What to Observe

1. **Shadow Movement**
   - Watch the shadow move as the light orbits around the scene
   - Notice how the shadow shape changes based on light position

2. **Shadow Quality**
   - Observe that shadows are sharp and well-defined
   - The ground plane correctly receives the cube's shadow

3. **Camera Interaction**
   - Move the camera to see shadows from different angles
   - Notice that shadows remain correct even when camera is close

---

## 📁 Project Structure

```
opengl-shadow-volumes/
│
├── final-project-zahra/
│   ├── main.cpp              # Entry point and rendering logic
│   ├── Camera.h              # First-person camera implementation
│   ├── Shader.h              # Shader compilation and management
│   │
│   └── res/
│       └── shaders/
│           ├── core.vs       # Standard vertex shader
│           ├── ambient.fs    # Ambient lighting fragment shader
│           ├── diffuse.fs    # Diffuse+specular lighting shader
│           ├── volume.vs     # Shadow volume vertex shader
│           ├── volume.fs     # Shadow volume fragment shader
│           ├── light.vs      # Light source vertex shader
│           └── light.fs      # Light source fragment shader
│
├── External/                 # Third-party libraries (not in repo)
│   ├── GLEW/
│   ├── GLFW/
│   └── glm/
│
├── docs/                     # Documentation and reports
│   ├── screenshots/          # Demo images
│   └── algorithm.md          # Algorithm explanation
│
├── final-project-zahra.sln   # Visual Studio solution
├── final-project-zahra.vcxproj
├── .gitignore
├── LICENSE
└── README.md                 # This file
```

---

## 🎓 Learning Resources

If you're interested in shadow volumes, check out these resources:

- **Graphics Gems**: [Fast, Robust Shadow Volumes](https://www.geometrictools.com/Documentation/StencilShadowVolumes.pdf)
- **GPU Gems**: [Chapter on Efficient Shadow Volume Rendering](https://developer.nvidia.com/gpugems/gpugems/part-ii-lighting-and-shadows)
- **LearnOpenGL**: [Shadow Mapping](https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping) (alternative technique)
- **OpenGL Tutorial**: [Stencil Testing](https://learnopengl.com/Advanced-OpenGL/Stencil-testing)

---

## 📝 Algorithm Explanation

### Why Z-FAIL Instead of Z-PASS?

The **Z-FAIL** algorithm (Carmack's Reverse) is more robust than the simpler Z-PASS method because:

1. ✅ **Works when camera is inside shadow volume** (Z-PASS fails here)
2. ✅ **Handles near-plane clipping correctly**
3. ✅ **More stable with various camera positions**

The trade-off is that Z-FAIL requires both front and back caps, making it slightly more complex to implement.

### Step-by-Step Process

```cpp
// 1. Identify lit and unlit faces
for each triangle {
    if (face_normal · light_direction > 0)
        face_is_lit = true;
}

// 2. Find silhouette edges
for each edge {
    if (face0_lit != face1_lit)
        add_to_silhouette(edge);
}

// 3. Build shadow volume
// Front cap (lit faces)
for each lit_face {
    emit triangle(face_vertices);
}

// Back cap (unlit faces, extruded)
for each unlit_face {
    emit triangle(face_vertices + extrusion);
}

// Side quads (from silhouette)
for each silhouette_edge {
    v0 = edge.vertex0;
    v1 = edge.vertex1;
    v0_far = v0 + normalize(v0 - light) * 50.0;
    v1_far = v1 + normalize(v1 - light) * 50.0;
    
    emit quad(v0, v0_far, v1_far, v1);
}
```

---

## 🐛 Known Issues / Limitations

- **Performance:** Shadow volume generation happens on CPU each frame. For complex meshes, this could be slow.
- **Self-shadowing:** The cube doesn't shadow itself (by design for this demo)
- **Single Light:** Only supports one light source
- **Static Geometry:** Shadow caster geometry is hardcoded (cube only)

### Potential Improvements

- [ ] Move shadow volume generation to geometry shader
- [ ] Support multiple light sources
- [ ] Add soft shadows using percentage-closer filtering
- [ ] Implement LOD for shadow volumes
- [ ] Load arbitrary mesh files (.obj, .fbx)

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2024 Zahra

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files...
```

---

## 👤 Author

**Zahra** (F23040129)  
Computer Science Student  
Nanjing University of Posts and Telecommunications

---

## 🙏 Acknowledgments

- **OpenGL Community** for excellent documentation and tutorials
- **GLM, GLFW, GLEW** developers for making graphics programming more accessible
- **John Carmack** for pioneering the Z-FAIL algorithm
- **Computer Graphics Course Staff** at NJUPT for guidance

---

## 📧 Contact & Feedback

Have questions or suggestions? Feel free to:
- Open an issue on GitHub
- Submit a pull request
- Contact via university email

---

<div align="center">

**Made with ❤️ and OpenGL**

⭐ Star this repo if you found it helpful!

</div>
