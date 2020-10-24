#pragma once
#include "Texture.h"

#include <glm\ext\vector_float3.hpp>

struct Material
{
    enum Type {
        Ambient =      1,
        Diffuse =      2,
        Specular =     4,
        DiffuseTex =   8,
        SpecularTex = 16
    };

    int type;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    Texture* diffuseTex;
    Texture* specularTex;

    float shininess;

    inline Material()
    {

    }

    inline Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess = 0.5f)
    {
        type = Ambient + Diffuse + Specular;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->shininess = shininess;
        diffuseTex = nullptr;
        specularTex = nullptr;
    }

    inline Material(Texture* diffuseTex = nullptr, Texture* specularTex = nullptr, float shininess = 0.5f)
    {
        this->ambient = { 1.0f, 1.0f, 1.0f };
        this->diffuse = { 1.0f, 1.0f, 1.0f };
        this->specular = { 1.0f, 1.0f, 1.0f };
        this->shininess = 1.0f;
        type = Ambient + Diffuse + Specular;
        if (diffuseTex != nullptr)
            type += DiffuseTex;
        if (specularTex != nullptr)
            type += SpecularTex;
        this->diffuseTex = diffuseTex;
        this->specularTex = specularTex;
    }

    inline void setDiffuseTexture(Texture* texture)
    {
        if (diffuseTex != nullptr)
        {
            type -= DiffuseTex;
        }
        if (texture != nullptr)
        {
            type += DiffuseTex;
        }
        diffuseTex = texture;
    }

    inline void setSpecularTexture(Texture* texture)
    {
        if (specularTex != nullptr)
        {
            type -= SpecularTex;
        }
        if (texture != nullptr)
        {
            type += SpecularTex;
        }
        specularTex = texture;
    }

    inline static Material* Default() { return new Material({ 0, 0, 0 }, { 0.75, 0.75, 0.75 }, { 0.5, 0.5, 0.5 }, 0.5); }

    inline static Material* Emerald() { return new Material({ 0.0215,0.1745,	0.0215 }, { 0.07568,	0.61424,0.07568 }, { 0.633,0.727811,0.633 }, 0.6); }
    inline static Material* Jade() { return new Material({ 0.135,0.2225,0.1575 }, { 0.54,0.89,0.63 }, { 0.316228,0.316228,	0.316228 }, 0.1); }
    inline static Material* Obsidian() { return new Material({ 0.05375,0.05,0.06625 }, { 0.18275,0.17,0.22525 }, { 0.332741,0.328634,0.346435 }, 0.3); }
    inline static Material* Pearl() { return new Material({ 0.25, 0.20725, 0.20725 }, { 1, 0.829, 0.829 }, { 0.296648, 0.296648, 0.296648 }, 0.088); }
    inline static Material* Ruby() { return new Material({ 0.1745, 0.01175, 0.01175 }, { 0.61424, 0.04136, 0.04136 }, { 0.727811, 0.626959, 0.626959 }, 0.6); }
                          
    inline static Material* Turquoise() { return new Material({ 0.1, 0.18725, 0.1745 }, { 0.396, 0.74151, 0.69102 }, { 0.297254, 0.30829, 0.306678 }, 0.1); }
    inline static Material* Brass() { return new Material({ 0.329412, 0.223529, 0.027451 }, { 0.780392, 0.568627, 0.113725 }, { 0.992157, 0.941176, 0.807843 }, 0.21794872); }
    inline static Material* Bronze() { return new Material({ 0.2125, 0.1275, 0.054 }, { 0.714, 0.4284, 0.18144 }, { 0.393548, 0.271906, 0.166721 }, 0.2); }
    inline static Material* Chrome() { return new Material({ 0.25, 0.25, 0.25 }, { 0.4, 0.4, 0.4 }, { 0.774597, 0.774597, 0.774597 }, 0.6); }
    inline static Material* Copper() { return new Material({ 0.19125, 0.0735, 0.0225 }, { 0.7038, 0.27048, 0.0828 }, { 0.256777, 0.137622, 0.086014 }, 0.1); }
    inline static Material* Gold() { return new Material({ 0.24725, 0.1995, 0.0745 }, { 0.75164, 0.60648, 0.22648 }, { 0.628281, 0.555802, 0.366065 }, 0.4); }
    inline static Material* Silver() { return new Material({ 0.19225, 0.19225, 0.19225 }, { 0.50754, 0.50754, 0.50754 }, { 0.508273, 0.508273, 0.508273 }, 0.4); }
                          
    inline static Material* Black_plastic() { return new Material({ 0.0, 0.0, 0.0 }, { 0.01, 0.01, 0.01 }, { 0.50, 0.50, 0.50 }, 0.25); }
    inline static Material* Cyan_plastic() { return new Material({ 0.0, 0.1, 0.06 }, { 0.0, 0.50980392, 0.50980392 }, { 0.50196078, 0.50196078, 0.50196078 }, 0.25); }
    inline static Material* Green_plastic() { return new Material({ 0.0, 0.0, 0.0 }, { 0.1, 0.35, 0.1 }, { 0.45, 0.55, 0.45 }, 0.25); }
    inline static Material* Red_plastic() { return new Material({ 0.0, 0.0, 0.0 }, { 0.5, 0.0, 0.0 }, { 0.7, 0.6, 0.6 }, 0.25); }
    inline static Material* White_plastic() { return new Material({ 0.0, 0.0, 0.0 }, { 0.55, 0.55, 0.55 }, { 0.70, 0.70, 0.70 }, 0.25); }
    inline static Material* Yellow_plastic() { return new Material({ 0.0, 0.0, 0.0 }, { 0.5, 0.5, 0.0 }, { 0.60, 0.60, 0.50 }, 0.25); }
                          
    inline static Material* Black_rubber() { return new Material({ 0.02, 0.02, 0.02 }, { 0.01, 0.01, 0.01 }, { 0.4, 0.4, 0.4 }, 0.078125); }
    inline static Material* Cyan_rubber() { return new Material({ 0.0, 0.05, 0.05 }, { 0.4, 0.5, 0.5 }, { 0.04, 0.7, 0.7 }, 0.078125); }
    inline static Material* Green_rubber() { return new Material({ 0.0, 0.05, 0.0 }, { 0.4, 0.5, 0.4 }, { 0.04, 0.7, 0.04 }, 0.078125); }
    inline static Material* Red_rubber() { return new Material({ 0.05, 0.0, 0.0 }, { 0.5, 0.4, 0.4 }, { 0.7, 0.04, 0.04 }, 0.078125); }
    inline static Material* White_rubber() { return new Material({ 0.05, 0.05, 0.05 }, { 0.5, 0.5, 0.5 }, { 0.7, 0.7, 0.7 }, 0.078125); }
    inline static Material* Yellow_rubber() { return new Material({ 0.05, 0.05, 0.0 }, { 0.5, 0.5, 0.4 }, { 0.7, 0.7, 0.04 }, 0.078125); }

};