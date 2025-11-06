#include <iostream>
#include <iomanip>
#include "ObjParser.h"

void printObjData(const ObjData& data) {
    std::cout << "\n========================================\n";
    std::cout << "Resultats du parsing OBJ\n";
    std::cout << "========================================\n\n";

    if (!data.objectName.empty()) {
        std::cout << "Nom de l'objet: " << data.objectName << "\n\n";
    }

    // Statistiques
    std::cout << "=== STATISTIQUES ===\n";
    std::cout << "Vertices geometriques (v):  " << data.getVertexCount() << "\n";
    std::cout << "Coordonnees texture (vt):   " << data.getTexCoordCount() << "\n";
    std::cout << "Normales (vn):              " << data.getNormalCount() << "\n";
    std::cout << "Faces (f):                  " << data.getFaceCount() << "\n";
    std::cout << "\n";

    // Afficher les vertices
    if (!data.vertices.empty()) {
        std::cout << "=== VERTICES GEOMETRIQUES ===\n";
        for (size_t i = 0; i < data.vertices.size(); ++i) {
            const auto& v = data.vertices[i];
            std::cout << "v[" << i << "]: ("
                << std::fixed << std::setprecision(2)
                << v.x << ", " << v.y << ", " << v.z;
            if (v.w != 1.0f) {
                std::cout << ", " << v.w;
            }
            std::cout << ")\n";
        }
        std::cout << "\n";
    }

    // Afficher les coordonnees de texture
    if (!data.texCoords.empty()) {
        std::cout << "=== COORDONNEES DE TEXTURE ===\n";
        for (size_t i = 0; i < data.texCoords.size(); ++i) {
            const auto& vt = data.texCoords[i];
            std::cout << "vt[" << i << "]: ("
                << std::fixed << std::setprecision(2)
                << vt.u << ", " << vt.v;
            if (vt.w != 0.0f) {
                std::cout << ", " << vt.w;
            }
            std::cout << ")\n";
        }
        std::cout << "\n";
    }

    // Afficher les normales
    if (!data.normals.empty()) {
        std::cout << "=== NORMALES ===\n";
        for (size_t i = 0; i < data.normals.size(); ++i) {
            const auto& vn = data.normals[i];
            std::cout << "vn[" << i << "]: ("
                << std::fixed << std::setprecision(2)
                << vn.x << ", " << vn.y << ", " << vn.z
                << ")\n";
        }
        std::cout << "\n";
    }

    // Afficher les faces
    if (!data.faces.empty()) {
        std::cout << "=== FACES ===\n";
        for (size_t i = 0; i < data.faces.size(); ++i) {
            const auto& face = data.faces[i];
            std::cout << "f[" << i << "]: ";

            for (size_t j = 0; j < face.vertices.size(); ++j) {
                const auto& fv = face.vertices[j];

                if (j > 0) std::cout << " ";

                // Afficher format OBJ (indices en base-1 pour affichage)
                std::cout << (fv.vIndex + 1);
                if (fv.vtIndex >= 0 || fv.vnIndex >= 0) {
                    std::cout << "/";
                    if (fv.vtIndex >= 0) {
                        std::cout << (fv.vtIndex + 1);
                    }
                    if (fv.vnIndex >= 0) {
                        std::cout << "/" << (fv.vnIndex + 1);
                    }
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    std::cout << "========================================\n";
}

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);

    std::string filePath;

    if (argc >= 2) {
        filePath = argv[1];
    }
    else {
        filePath = "cube.obj";
        std::cout << "Aucun fichier specifie, utilisation de 'cube.obj' par defaut.\n";
        std::cout << "Usage: " << argv[0] << " <fichier.obj>\n\n";
    }

    ObjParser parser;
    ObjData data;

    std::cout << "Parsing du fichier: " << filePath << "\n";

    if (!parser.parse(filePath, data)) {
        std::cerr << "\n[ERREUR] Echec du parsing: " << parser.getLastError() << "\n";
        return 1;
    }

    std::cout << "[OK] Parsing reussi!\n";

    printObjData(data);

    return 0;
}
