# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A 2D tower defense game written in **C++17** using **SFML 3.0.2**. Players place towers on a 26×15 grid map to stop waves of monsters from reaching the end of a path.

## Build

**Compiler:** `C:\msys64\ucrt64\bin\g++.exe` (MSYS2 GCC)  
**SFML:** installed at `C:\SFML-3.0.2`

Build command (matches `.vscode/tasks.json`):
```bash
g++.exe -fdiagnostics-color=always -g src/*.cpp -o $ood.exe \
  -I C:/SFML-3.0.2/include \
  -L C:/SFML-3.0.2/lib \
  -lsfml-graphics -lsfml-window -lsfml-system
```

In VS Code: `Ctrl+Shift+B` triggers the build task. `F5` builds and launches the debugger (gdb).

No test framework or linting tooling is configured.

## Architecture

All source lives in `src/` as a single flat directory. The game loop in `main.cpp` wires together these systems:

### Core Systems

| Class | Role                                                                                                                               |
|---|------------------------------------------------------------------------------------------------------------------------------------|
| `GameManager` | Owns every live `GameObject`; drives update ticks; tracks state (Running / GameOver / Victory)                                     |
| `Renderer` | SFML window; renders objects sorted by `RenderLayer` (Background → Entity → Projectile → UI)                                       |
| `InputManager` | Routes mouse/keyboard events to `IClickable` objects                                                                               |
| `ObjectFactory` | Singleton factory — always create objects here with singleton so they are registered in `GameManager` and `Renderer` automatically |
| `Time` | 정적 deltaTime 제공자. 매 프레임 `time.update()` 호출 → `Time::getDeltaTime()`으로 조회                                                           |
| `Timer` | 쿨다운/지연 측정 유틸리티 (`Timer.h`). `IRoutine` 상속. Wave 스포닝 등 내부 타이밍에 사용                                                                   |

### GameObject Hierarchy

`GameObject` is the base (position + `Tag`). Objects opt into behaviours via interfaces:

- **`IRoutine`** — frame update (`update()`, 파라미터 없음 — deltaTime은 `Time::getDeltaTime()` 직접 조회)
- **`IRenderable`** — frame render (`render(sf::RenderWindow&)`) + layer declaration
- **`IClickable`** — mouse interaction

Key concrete types: `Tile` (Buildable / Path), `Monster`, `Tower` / `BasicTower`, `Projectile`, `Player`, `Map`, `Path`, `Wave`.

### Naming Conventions
- Class & Struct names: `PascalCase`
- Functions & local variables: `camelCase`
- Private member variables: `m_` 접두사 사용 (예: `m_health`)
- Interface classes: `I` 접두사 사용 (예: `IRoutine`)
- Constants & Enums: `UPPER_SNAKE_CASE`

## Language
모든 답변과 코드 리뷰는 한국어로 작성. 기술 용어는 원문을 병기.
