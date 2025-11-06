//
// Created by kolyne on 10/28/25.
//

#ifndef MINIGL_SHADER_H
#define MINIGL_SHADER_H

#include <glm/glm.hpp>
#include <string>

namespace mngl
{
    struct Color;

    class Shader
    {
        unsigned int m_id;
        unsigned int m_vertexShader;
        unsigned int m_fragmentShader;

        std::string GetFileContent(const std::string& _path);
        unsigned int Process(const std::string& _shaderCode, bool _isVertex);

    public:
        Shader(const std::string& _vertexPath, const std::string& _fragmentPath);
        ~Shader();

        void Use() const;
        void Shutdown() const;

        void SetInt(const std::string& _name, int _value) const;
        void SetFloat(const std::string& _name, float _value) const;
        void SetColor(const std::string& _name, const Color& _value) const;
        void SetVector3(const std::string& _name, const glm::vec3& _value) const;
        void SetMatrix4(const std::string& _name, const glm::mat4& _value) const;
    };
}

#endif //MINIGL_SHADER_H
