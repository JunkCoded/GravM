# GravM — Gravitational Maneuvers Simulation in Unreal Engine

[![Unreal Engine](https://shields.io)](https://unrealengine.com)
[![License: MIT](https://shields.io)](https://opensource.org)

**GravM** is a 3D orbital mechanics simulation tool built with Unreal Engine. It focuses on recreating and visualizing **gravitational assists (slingshot maneuvers)**—a spaceflight technique used to accelerate, decelerate, or redirect spacecraft using the gravity of celestial bodies.

This project was originally developed as my high school graduation/thesis project. It was successfully presented and defended at multiple academic competitions, winning top honors, awards, and securing additional merit points for my university admission.

---

## 🏆 Achievements & Recognition

* **Award Winner:** Achieved top-tier placements at regional/national high school science and engineering project competitions.
* **Academic Merit:** Officially recognized by university admission boards, granting bonus entry points for exceptional technical execution.

---

## 🚀 Key Features

* **Real-time Orbital Physics:** Accurate calculation of gravitational forces exerted by celestial bodies on a spacecraft.
* **Trajectory Prediction:** Visual rendering of calculated flight paths and projected slingshot vectors.
* **Interactive Controls:** Adjustable variables for spacecraft mass, approach velocity, entry angles, and planetary orbits.

---

## 🛠️ Technical Challenge: Framerate-Independent Physics (Subticking)

### The Problem
During early development, the orbital paths of the spacecraft varied drastically depending on the hardware's performance. High-velocity gravitational maneuvers require extreme precision when the spacecraft passes close to a planet's event horizon/periapsis. 
* At **high FPS**, the physics engine updated frequently enough to calculate the curve smoothly.
* At **low FPS** (or during sudden performance spikes), delta-time gaps caused the physics engine to "teleport" the spacecraft past critical gravity points, completely breaking determinism and reproducibility across different devices.

### The Solution: Unreal Engine Subticking
To achieve universal reproducibility, the project relies on **Physics Subticking** inside Unreal Engine. 

Instead of tying gravitational calculations directly to the standard frame tick (`Tick` function), the simulation breaks down each frame's delta time into smaller, fixed-size micro-steps (subticks). 
* This ensures that whether the game runs at 30 FPS or 144 FPS, the underlying orbital math executes identical calculation intervals.
* Result: **100% deterministic and reproducible space trajectories** on all tested devices.

---

## 📂 Project Structure & Tech Stack

* **Engine:** Unreal Engine 5 (originally built/tested on UE4/5 depending on version)
* **Language:** Blueprints / C++ (Adjust based on what you actually used)
* **Physics:** Customized rigid body behaviors with sub-stepped gravitational force injection.

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 🧑‍💻 Legacy Project Note
*Please note: This is an archived archive/legacy project developed during my high school years. It is no longer actively maintained, but stands as a milestone of my early software engineering and physics simulation journey.*
