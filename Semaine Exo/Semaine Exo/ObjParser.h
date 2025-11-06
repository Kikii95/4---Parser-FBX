#pragma once
#include "ObjData.h"
#include <string>
#include <fstream>
#include <sstream>

class ObjParser {
public:
    ObjParser();

    // Parse un fichier OBJ et retourne les donnees
    // Retourne true si le parsing a reussi, false sinon
    bool parse(const std::string& filePath, ObjData& outData);

    // Parse depuis une string (utile pour tests)
    bool parseFromString(const std::string& source, ObjData& outData);

    // Derniere erreur rencontree
    const std::string& getLastError() const { return m_lastError; }

private:
    std::string m_lastError;

    // Parse une seule ligne du fichier
    void parseLine(const std::string& line, ObjData& data);

    // Parse les differents types de lignes
    void parseVertex(const std::string& line, ObjData& data);
    void parseTexCoord(const std::string& line, ObjData& data);
    void parseNormal(const std::string& line, ObjData& data);
    void parseFace(const std::string& line, ObjData& data);
    void parseObjectName(const std::string& line, ObjData& data);

    // Utilitaires
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::string trim(const std::string& str);
    bool startsWith(const std::string& str, const std::string& prefix);
};
