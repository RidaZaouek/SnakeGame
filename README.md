# 🐍 SnakeGame

> Classic Snake Game built with **C++** and **OpenGL (GLUT)** — real-time 2D rendering, smooth controls, and addictive gameplay.

---

## 📸 Preview

```
┌─────────────────────────────────┐
│  Score:3                        │
│                                 │
│        ██                       │
│        ██  ←  🟢 (head)        │
│        ██                       │
│        ██                       │
│             🔴 (food)           │
│                                 │
└─────────────────────────────────┘
```

---

## 🎮 Gameplay

- Use the **arrow keys** to control the snake
- **Eat the red food** to grow longer and increase your score
- **Avoid the red border walls** — hitting them ends the game
- **Avoid your own body** — self-collision also triggers Game Over
- Your **final score** is displayed in a pop-up at the end

---

## ⚙️ Features

| Feature | Details |
|---|---|
| 🟩 Grid | 40×40 cell 2D grid rendered with OpenGL |
| 🎨 Rendering | Double-buffered (`GLUT_DOUBLE`) for smooth animation |
| 🕹️ Controls | Arrow keys (↑ ↓ ← →) with direction-lock (no 180° reversal) |
| 🍎 Food | Randomly spawned using `srand(time(NULL))` |
| 💀 Collision | Wall border + self-body collision detection |
| 📈 Score | Real-time score display with GLUT bitmap font (Helvetica 18) |
| 🐍 Snake Body | Stored in integer arrays — grows up to **60 segments** |
| ⏱️ FPS | Fixed 10 FPS game loop via `glutTimerFunc()` |
| 🪟 Window | Console window hidden on launch for a clean experience |
| ☠️ Game Over | Windows `MessageBox` popup showing final score |

---

## 🛠️ Built With

- **C++**
- **OpenGL** — 2D rendering (`GL_LINE_LOOP`, `GL_POINTS`, `glRectd`)
- **GLUT / FreeGLUT** — window management, input, timer loop
- **Windows API** — `MessageBox`, `ShowWindow`

---

## 📁 Project Structure

```
SnakeGame/
│
├── SnakeGame.cpp     # Entry point — GLUT init, main loop, callbacks
├── Snake.cpp         # Game logic — grid, snake, food, collision
├── Snake.h           # Constants and function declarations
└── Game.h            # Shared headers and definitions
```

---

## 🚀 How to Run

### Requirements
- Windows OS
- Visual Studio (recommended) or MinGW with g++
- FreeGLUT library installed

### With Visual Studio
1. Clone the repository
   ```bash
   git clone https://github.com/RidaZaouek/SnakeGame.git
   ```
2. Open the `.sln` file or create a new project and add the `.cpp` files
3. Link **FreeGLUT** and **OpenGL** libraries in project settings
4. Build and run (`Ctrl + F5`)

### With g++ (MinGW)
```bash
g++ SnakeGame.cpp Snake.cpp -o SnakeGame -lfreeglut -lopengl32 -lglu32
./SnakeGame.exe
```

---

## 🎯 Controls

| Key | Action |
|---|---|
| `↑` Arrow | Move Up |
| `↓` Arrow | Move Down |
| `→` Arrow | Move Right |
| `←` Arrow | Move Left |

> ⚠️ You cannot reverse direction instantly (e.g. going RIGHT then pressing LEFT is ignored).

---

## 📐 Technical Details

- **Grid**: 40 columns × 40 rows, rendered using `GL_LINE_LOOP`
- **Projection**: Orthographic 2D via `glOrtho(0, 40, 0, 40, -1, 1)`
- **Snake position**: Two integer arrays `posX[]` and `posY[]` of max size 60
- **Movement**: Each frame, body segments shift forward and head moves based on direction
- **Food**: Placed randomly inside bounds `[1, gridSize-2]` using `rand() % range`
- **Collision detection**:
  - Wall: `posX[0] == 0 || posX[0] == gridX-1 || ...`
  - Self: loop checking if head matches any body segment position

---

## 👤 Author

**Rida Zaouek**  
[GitHub Profile](https://github.com/RidaZaouek)

---

## 📄 License

This project is open source. Feel free to fork, modify, and learn from it!