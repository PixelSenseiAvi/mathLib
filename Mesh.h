#pragma once

#include <iostream>

// Minimal placeholder types so the SceneGraph compiles and is self-consistent
// without a full rendering backend. In a real project these would be provided
// by your graphics layer (e.g. an OpenGL renderer and a GPU mesh resource).

// A drawable mesh. Replace Draw() with real GPU submission in your engine.
class Mesh
{
public:
    void Draw() const
    {
        std::cout << "[Mesh] draw\n";
    }
};

// A rendering context. Kept as an opaque stub here.
class OGLRenderer
{
public:
    OGLRenderer() = default;
};
