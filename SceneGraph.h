#pragma once

// SceneGraph is a data structure for managing the spatial representation of a
// scene. It has a hierarchical, tree-like structure where nodes represent
// objects together with their transforms, colour, and child nodes. Each node's
// world transform is the product of its parent's world transform and its own
// local transform.

#include "matrix.h"
#include "vec3.h"
#include "vec4.h"
#include "Mesh.h"

#include <vector>

// Convenience aliases mapping the generic library types to the names used here.
using Vector3 = vec3<float>;
using Vector4 = vec4<float>;
using Matrix4 = matrix<float, 4, 4>;

class SceneNode
{
public:
    explicit SceneNode(Mesh* mesh = nullptr,
                       Vector4 colour = Vector4(1, 1, 1, 1))
        : parent(nullptr),
          mesh(mesh),
          worldTransform(Matrix4::identity()),
          transform(Matrix4::identity()),
          modelScale(1, 1, 1),
          colour(colour)
    {
    }

    virtual ~SceneNode()
    {
        for (SceneNode* child : children)
            delete child;
    }

    // Non-copyable: nodes own their children via raw pointers.
    SceneNode(const SceneNode&) = delete;
    SceneNode& operator=(const SceneNode&) = delete;

    void SetTransform(const Matrix4& m) { transform = m; }
    const Matrix4& GetTransform() const { return transform; }
    const Matrix4& GetWorldTransform() const { return worldTransform; }

    Vector4 GetColour() const { return colour; }
    void SetColour(Vector4 c) { colour = c; }

    Vector3 GetModelScale() const { return modelScale; }
    void SetModelScale(Vector3 s) { modelScale = s; }

    Mesh* GetMesh() const { return mesh; }
    void SetMesh(Mesh* m) { mesh = m; }

    void AddChild(SceneNode* child)
    {
        children.push_back(child);
        child->parent = this;
    }

    std::vector<SceneNode*>::const_iterator GetChildIteratorStart() const
    {
        return children.begin();
    }
    std::vector<SceneNode*>::const_iterator GetChildIteratorEnd() const
    {
        return children.end();
    }

    virtual void Update(float msec)
    {
        if (parent)
            worldTransform = parent->worldTransform * transform;
        else
            worldTransform = transform; // root: world transform is the local transform

        for (SceneNode* child : children)
            child->Update(msec);
    }

    virtual void Draw(const OGLRenderer& r)
    {
        (void)r; // renderer unused in this stub
        if (mesh)
            mesh->Draw();
    }

protected:
    SceneNode* parent;
    Mesh* mesh;
    Matrix4 worldTransform;
    Matrix4 transform;
    Vector3 modelScale;
    Vector4 colour;
    std::vector<SceneNode*> children;
};
