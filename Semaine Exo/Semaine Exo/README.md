# Parser OBJ

Parser de fichiers OBJ (Wavefront) en C++ supportant les vertices geometriques, coordonnees de texture, normales et faces.

## Structure du Projet

```
.
├── ObjData.h           # Structures de donnees (Vertex, TexCoord, Normal, Face, ObjData)
├── ObjParser.h         # Interface du parser
├── ObjParser.cpp       # Implementation du parser
├── TestObjParser.cpp   # Programme de test
├── cube.obj            # Fichier de test (cube avec textures et normales)
├── Tokenizer.h         # Tokenizer generique (existant)
├── Tokenizer.cpp       # Implementation du tokenizer
└── Jour1.cpp           # Test du tokenizer
```

## Fonctionnalites

Le parser supporte les commandes OBJ suivantes :

- **`v x y z [w]`** : Vertices geometriques (w optionnel, defaut 1.0)
- **`vt u v [w]`** : Coordonnees de texture (w optionnel, defaut 0.0)
- **`vn x y z`** : Normales
- **`f v1/vt1/vn1 v2/vt2/vn2 ...`** : Faces avec variantes :
  - `f v1 v2 v3` (vertices seulement)
  - `f v1/vt1 v2/vt2 v3/vt3` (vertices + textures)
  - `f v1//vn1 v2//vn2 v3//vn3` (vertices + normales)
  - `f v1/vt1/vn1 ...` (complet)
- **`o nom`** : Nom de l'objet
- **`#`** : Commentaires (ignores)

**Note importante** : Les indices dans les fichiers OBJ commencent a 1, mais sont automatiquement convertis en base-0 lors du parsing pour faciliter l'acces aux tableaux C++.

## Compilation

### Option 1 : Visual Studio (Recommande sur Windows)

1. Ouvrir `Semaine Exo.sln` dans Visual Studio
2. Selectionner la configuration **x64 Debug** ou **x64 Release**
3. Compiler (F7) et executer (F5)

**Note** : `Jour1.cpp` est exclu de la build par defaut. Pour tester le tokenizer, re-inclure `Jour1.cpp` et exclure `TestObjParser.cpp` dans les proprietes du projet.

### Option 2 : CMake (Multi-plateforme)

```bash
# Configuration
cmake -B build

# Compilation
cmake --build build

# Execution (depuis le repertoire build)
cd build
./TestObjParser cube.obj         # Windows: TestObjParser.exe cube.obj
./TestTokenizer                   # Test du tokenizer
```

### Option 3 : Compilation manuelle (g++/clang++)

```bash
# Parser OBJ
g++ -std=c++17 -o TestObjParser TestObjParser.cpp ObjParser.cpp

# Tokenizer
g++ -std=c++17 -o TestTokenizer Jour1.cpp Tokenizer.cpp
```

## Utilisation

### Test avec le fichier cube.obj

```bash
./TestObjParser cube.obj
```

### Test avec votre propre fichier

```bash
./TestObjParser chemin/vers/votre/fichier.obj
```

### Exemple de sortie

```
Parsing du fichier: cube.obj
[OK] Parsing reussi!

========================================
Resultats du parsing OBJ
========================================

Nom de l'objet: Cube

=== STATISTIQUES ===
Vertices geometriques (v):  8
Coordonnees texture (vt):   4
Normales (vn):              6
Faces (f):                  12

=== VERTICES GEOMETRIQUES ===
v[0]: (-1.00, -1.00, 1.00)
v[1]: (1.00, -1.00, 1.00)
...

=== FACES ===
f[0]: 1/1/1 2/2/1 3/3/1
f[1]: 1/1/1 3/3/1 4/4/1
...
```

## Integration dans votre Code

```cpp
#include "ObjParser.h"

int main() {
    ObjParser parser;
    ObjData data;

    if (!parser.parse("model.obj", data)) {
        std::cerr << "Erreur: " << parser.getLastError() << std::endl;
        return 1;
    }

    // Acceder aux donnees
    for (const auto& vertex : data.vertices) {
        std::cout << "Vertex: (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;
    }

    for (const auto& face : data.faces) {
        for (const auto& fv : face.vertices) {
            // fv.vIndex, fv.vtIndex, fv.vnIndex (indices en base-0)
            // -1 si non defini
        }
    }

    return 0;
}
```

## Points Techniques Importants

### Conversion des Indices

- **Fichier OBJ** : Indices commencent a **1**
- **Structures C++** : Indices convertis en **base-0** automatiquement
- **Indices optionnels** : Valeur `-1` si non defini

Exemple :
```
# Dans le fichier OBJ
f 1/1/1 2/2/1 3/3/1

# Dans la structure Face
fv[0].vIndex  = 0   (1-1)
fv[0].vtIndex = 0   (1-1)
fv[0].vnIndex = 0   (1-1)
```

### Gestion des Faces

- Minimum 3 vertices par face (triangles)
- Support des quads et polygones (> 3 vertices)
- Pour rendu OpenGL/DirectX, triangulation necessaire si faces > 3 vertices

### Commandes Ignorees

Le parser ignore volontairement :
- `vp` : Vertices parametriques
- `s` : Smooth shading
- `g` : Groupes
- `usemtl` / `mtllib` : Materials
- Autres commandes non essentielles

## Tests

Le fichier `cube.obj` fourni contient :
- 8 vertices (coins du cube)
- 4 coordonnees de texture
- 6 normales (une par face)
- 12 triangles (6 faces × 2 triangles)

Format complet : `f v/vt/vn`

## Auteur

Projet d'exercice pour l'apprentissage du parsing de fichiers 3D.
