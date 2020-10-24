#pragma once
#include "GameObject.h"
#include <vector>
#include "Mesh.h"
#include <assimp\scene.h>
#include "Joint.h"

class Model : public GameObject
{
private:
    std::vector<Mesh*> meshes;
    std::string directory;
    
    const aiScene* aiscene;
    
public:
    Joint* rootJoint;
    std::unordered_map<std::string, Joint*> joints;
    std::string currentAnimation;
    float animationTime = 0;

private:
    void processNode(aiNode* node, const aiScene* scene, unsigned int level=0);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    void applyTransformToJoint(Joint* joint, const std::unordered_map<std::string, glm::mat4>& transforms, const glm::mat4& parentTransform);

public:
    Model();
    Model(const std::string& source);
    Model(std::vector<Mesh*>& meshes);
    Model(Mesh* mesh);
    void create(const std::string& source);
    void printAnimationNames();
    void printHierarchy(aiNode* node, std::string offset="");

    Joint* loadJoints(aiNode* node, Joint* parent);

    void draw(Shader* shader=nullptr, Camera* camera=nullptr, std::vector<Light*>* lights=nullptr);
    void update(float delta);
};