#pragma once
#include <vector>
#include <string>

// Structure de donnees pour fichier OBJ
// Note: Les indices dans le fichier OBJ commencent a 1, mais sont convertis en base-0 ici

struct Vertex {
    float x, y, z;
    float w = 1.0f;  // Coordonnee homogene (optionnelle)

    Vertex() : x(0), y(0), z(0), w(1.0f) {}
    Vertex(float x_, float y_, float z_, float w_ = 1.0f)
        : x(x_), y(y_), z(z_), w(w_) {}
};

struct TexCoord {
    float u, v;
    float w = 0.0f;  // Profondeur de texture (optionnelle)

    TexCoord() : u(0), v(0), w(0.0f) {}
    TexCoord(float u_, float v_, float w_ = 0.0f)
        : u(u_), v(v_), w(w_) {}
};

struct Normal {
    float x, y, z;

    Normal() : x(0), y(0), z(0) {}
    Normal(float x_, float y_, float z_)
        : x(x_), y(y_), z(z_) {}
};

// Un vertex de face peut referencer:
// - Un indice de vertex geometrique (obligatoire)
// - Un indice de coordonnee de texture (optionnel)
// - Un indice de normale (optionnel)
// Format dans fichier OBJ: v/vt/vn ou v//vn ou v/vt ou v
struct FaceVertex {
    int vIndex = -1;   // Indice vertex (base-0, -1 = non defini)
    int vtIndex = -1;  // Indice texture (base-0, -1 = non defini)
    int vnIndex = -1;  // Indice normale (base-0, -1 = non defini)

    FaceVertex() = default;
    FaceVertex(int v, int vt = -1, int vn = -1)
        : vIndex(v), vtIndex(vt), vnIndex(vn) {}
};

struct Face {
    std::vector<FaceVertex> vertices;  // Minimum 3 vertices (triangle)

    Face() = default;
    Face(const std::vector<FaceVertex>& verts) : vertices(verts) {}
};

// Conteneur principal pour toutes les donnees du fichier OBJ
struct ObjData {
    std::vector<Vertex> vertices;      // Liste des vertices geometriques (v)
    std::vector<TexCoord> texCoords;   // Liste des coordonnees de texture (vt)
    std::vector<Normal> normals;       // Liste des normales (vn)
    std::vector<Face> faces;           // Liste des faces (f)

    std::string objectName;            // Nom de l'objet (ligne "o")

    void clear() {
        vertices.clear();
        texCoords.clear();
        normals.clear();
        faces.clear();
        objectName.clear();
    }

    // Stats
    size_t getVertexCount() const { return vertices.size(); }
    size_t getTexCoordCount() const { return texCoords.size(); }
    size_t getNormalCount() const { return normals.size(); }
    size_t getFaceCount() const { return faces.size(); }
};
