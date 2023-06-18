/* SceneGraph is a data structure used for managing spatial representation of scenes.
   A scene graph typically has a hierarchical, tree-like structure where the nodes represent objects, attributes, transformations, and so on.
*/

#pragma once
#include "matrix.h"
#include "vec3.h"

#include "vec4.h"
#include "Mesh.h" //Already implemented in similar projects

#include <vector>

class SceneNode
{
public:
    SceneNode(Mesh *m = NULL, Vector4 colour = Vector4(1, 1, 1, 1));
    ~SceneNode(void);

    void SetTransform(const Matrix4 &matrix) { transform = matrix; }
    const Matrix4 &GetTransform() const { return transform; }
    Matrix4 GetWorldTransform() const { return worldTransform; }
    Vector4 GetColour() const { return colour; }
    void SetColour(Vector4 c) { colour = c; }
    Vector3 GetModelScale() const { return modelScale; }
    void SetModelScale(Vector3 s) { modelScale = s; }
    Mesh *GetMesh() const { return mesh; }
    void SetMesh(Mesh *m) { mesh = m; }
    void AddChild(SceneNode *s);
    virtual void Update(float msec);
    virtual void Draw(const OGLRenderer &r);
    std ::vector<SceneNode *>::const_iterator GetChildIteratorStart()
    {
        return children.begin();
    }
    std ::vector<SceneNode *>::const_iterator GetChildIteratorEnd()
    {
        return children.end();
    }

protected:
    SceneNode *parent;
    Mesh *mesh;
    Matrix4 worldTransform;
    Matrix4 transform;
    Vector3 modelScale;
    Vector4 colour;
    std ::vector<SceneNode *> children;
};

SceneNode ::SceneNode(Mesh *mesh, Vector4 colour)
{
    this - > mesh = mesh;
    this - > colour = colour;
    parent = NULL;
    modelScale = Vector3(1, 1, 1);
}

SceneNode ::~SceneNode(void)
{
    for (unsigned int i = 0; i < children.size(); ++i)
    {
        delete children[i];
    }
}

void SceneNode ::AddChild(SceneNode *s)
{
    children.push_back(s);
    s - > parent = this;
}

void SceneNode ::Draw(const OGLRenderer &r)
{
    if (mesh)
    {
        mesh - > Draw()
    };
}

void SceneNode ::Update(float msec)
{
    if (parent)
    { // This node has a parent ...
        worldTransform = parent - > worldTransform * transform;
    }
    else
    { // Root node , world transform is local transform !
        worldTransform = transform;
    }
    for (vector<SceneNode *>::iterator i = children.begin();
         i != children.end(); ++i)
    {
        (*i) - > Update(msec);
    }
}