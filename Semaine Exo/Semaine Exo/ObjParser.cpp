#include "ObjParser.h"
#include <algorithm>
#include <cctype>

ObjParser::ObjParser() : m_lastError("") {}

bool ObjParser::parse(const std::string& filePath, ObjData& outData) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        m_lastError = "Impossible d'ouvrir le fichier: " + filePath;
        return false;
    }

    outData.clear();
    m_lastError.clear();

    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        lineNum++;
        try {
            parseLine(line, outData);
        }
        catch (const std::exception& e) {
            m_lastError = "Erreur ligne " + std::to_string(lineNum) + ": " + e.what();
            return false;
        }
    }

    return true;
}

bool ObjParser::parseFromString(const std::string& source, ObjData& outData) {
    outData.clear();
    m_lastError.clear();

    std::istringstream stream(source);
    std::string line;
    int lineNum = 0;

    while (std::getline(stream, line)) {
        lineNum++;
        try {
            parseLine(line, outData);
        }
        catch (const std::exception& e) {
            m_lastError = "Erreur ligne " + std::to_string(lineNum) + ": " + e.what();
            return false;
        }
    }

    return true;
}

void ObjParser::parseLine(const std::string& line, ObjData& data) {
    std::string trimmed = trim(line);

    // Ignorer lignes vides et commentaires
    if (trimmed.empty() || trimmed[0] == '#') {
        return;
    }

    // Detecter le type de ligne
    if (startsWith(trimmed, "vn ")) {
        parseNormal(trimmed, data);
    }
    else if (startsWith(trimmed, "vt ")) {
        parseTexCoord(trimmed, data);
    }
    else if (startsWith(trimmed, "v ")) {
        parseVertex(trimmed, data);
    }
    else if (startsWith(trimmed, "f ")) {
        parseFace(trimmed, data);
    }
    else if (startsWith(trimmed, "o ")) {
        parseObjectName(trimmed, data);
    }
    // Ignorer les autres commandes (vp, s, g, usemtl, mtllib, etc.)
}

void ObjParser::parseVertex(const std::string& line, ObjData& data) {
    // Format: v x y z [w]
    std::istringstream iss(line.substr(2)); // Skip "v "

    float x, y, z, w = 1.0f;
    iss >> x >> y >> z;

    // w est optionnel
    if (iss >> w) {
        data.vertices.push_back(Vertex(x, y, z, w));
    }
    else {
        data.vertices.push_back(Vertex(x, y, z));
    }
}

void ObjParser::parseTexCoord(const std::string& line, ObjData& data) {
    // Format: vt u v [w]
    std::istringstream iss(line.substr(3)); // Skip "vt "

    float u, v, w = 0.0f;
    iss >> u >> v;

    // w est optionnel
    if (iss >> w) {
        data.texCoords.push_back(TexCoord(u, v, w));
    }
    else {
        data.texCoords.push_back(TexCoord(u, v));
    }
}

void ObjParser::parseNormal(const std::string& line, ObjData& data) {
    // Format: vn x y z
    std::istringstream iss(line.substr(3)); // Skip "vn "

    float x, y, z;
    iss >> x >> y >> z;

    data.normals.push_back(Normal(x, y, z));
}

void ObjParser::parseFace(const std::string& line, ObjData& data) {
    // Format: f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...
    // Variantes possibles:
    // - f v1 v2 v3                (vertices seulement)
    // - f v1/vt1 v2/vt2 v3/vt3    (vertices + texcoords)
    // - f v1//vn1 v2//vn2 v3//vn3 (vertices + normales)
    // - f v1/vt1/vn1 ...          (tout)

    std::string content = trim(line.substr(2)); // Skip "f "
    std::vector<std::string> tokens = split(content, ' ');

    Face face;

    for (const auto& token : tokens) {
        if (token.empty()) continue;

        FaceVertex fv;

        // Chercher les slashes
        size_t slash1 = token.find('/');
        if (slash1 == std::string::npos) {
            // Format: v (vertex seulement)
            int v = std::stoi(token);
            fv.vIndex = v - 1; // Convertir de base-1 a base-0
        }
        else {
            // Il y a au moins un slash
            size_t slash2 = token.find('/', slash1 + 1);

            // Extraire v
            std::string vStr = token.substr(0, slash1);
            fv.vIndex = std::stoi(vStr) - 1; // Base-1 -> base-0

            if (slash2 == std::string::npos) {
                // Format: v/vt (pas de slash2)
                std::string vtStr = token.substr(slash1 + 1);
                if (!vtStr.empty()) {
                    fv.vtIndex = std::stoi(vtStr) - 1;
                }
            }
            else {
                // Format: v/vt/vn ou v//vn
                std::string vtStr = token.substr(slash1 + 1, slash2 - slash1 - 1);
                std::string vnStr = token.substr(slash2 + 1);

                if (!vtStr.empty()) {
                    fv.vtIndex = std::stoi(vtStr) - 1;
                }
                if (!vnStr.empty()) {
                    fv.vnIndex = std::stoi(vnStr) - 1;
                }
            }
        }

        face.vertices.push_back(fv);
    }

    if (face.vertices.size() >= 3) {
        data.faces.push_back(face);
    }
}

void ObjParser::parseObjectName(const std::string& line, ObjData& data) {
    // Format: o name
    std::string name = trim(line.substr(2)); // Skip "o "
    data.objectName = name;
}

std::vector<std::string> ObjParser::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        std::string trimmed = trim(token);
        if (!trimmed.empty()) {
            tokens.push_back(trimmed);
        }
    }

    return tokens;
}

std::string ObjParser::trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length();

    // Trouver le debut (premier caractere non-whitespace)
    while (start < end && std::isspace(static_cast<unsigned char>(str[start]))) {
        start++;
    }

    // Trouver la fin (dernier caractere non-whitespace)
    while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1]))) {
        end--;
    }

    return str.substr(start, end - start);
}

bool ObjParser::startsWith(const std::string& str, const std::string& prefix) {
    if (str.length() < prefix.length()) {
        return false;
    }
    return str.compare(0, prefix.length(), prefix) == 0;
}
