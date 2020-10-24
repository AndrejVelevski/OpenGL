#include "Model.h"
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <glad\glad.h>
#include <iostream>
#include <glm\gtx\string_cast.hpp>
#include <glm\gtx\compatibility.hpp>
#include <glm\gtx\quaternion.hpp>
#include "Utils.h"

unsigned int jointId;

struct JointData
{
    unsigned int jointId;
    unsigned int vertexId;
    float weight;

    JointData(unsigned int jointId, unsigned int vertexId, float weight)
    {
        this->jointId = jointId;
        this->vertexId = vertexId;
        this->weight = weight;
    }
};

bool compareTo(const JointData& jd1, const JointData& jd2)
{
    if (jd1.vertexId < jd2.vertexId)
        return true;
    else if (jd1.vertexId == jd2.vertexId)
        if (jd1.weight > jd2.weight)
            return true;
        else if (jd1.weight == jd2.weight)
            if (jd1.jointId < jd2.jointId)
                return true;
    return false;
}

glm::mat4 aiMatrix4x4_mat4(const aiMatrix4x4& m)
{
    return glm::mat4
    {
        m.a1, m.b1, m.c1, m.d1,
        m.a2, m.b2, m.c2, m.d2,
        m.a3, m.b3, m.c3, m.d3,
        m.a4, m.b4, m.c4, m.d4
    };
};

void Model::processNode(aiNode* ainode, const aiScene* aiscene, unsigned int level)
{
    /*for (int i = 0; i < level; ++i)
    {
        std::cout << "    ";
    }
    std::cout << ainode->mName.C_Str() << std::endl;*/

    for (unsigned int i = 0; i < ainode->mNumMeshes; ++i)
    {
        aiMesh* mesh = aiscene->mMeshes[ainode->mMeshes[i]];
        meshes.push_back(processMesh(mesh, aiscene));
    }

    for (unsigned int i = 0; i < ainode->mNumChildren; ++i)
    {
        processNode(ainode->mChildren[i], aiscene, level+1);
    }
}

Mesh* Model::processMesh(aiMesh* aimesh, const aiScene* aiscene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> elements;
    Material* material = nullptr;

    //joints
    std::vector<JointData> jointData;
    if (aimesh->HasBones())
    {
        for (int i = 0; i < aimesh->mNumBones; ++i)
        {
            //std::cout << aimesh->mBones[i]->mName.C_Str() << std::endl;
            for (int j = 0; j < aimesh->mBones[i]->mNumWeights; ++j)
            {
                jointData.push_back(JointData(i, aimesh->mBones[i]->mWeights[j].mVertexId, aimesh->mBones[i]->mWeights[j].mWeight));
            }
        }
    }

    std::sort(jointData.begin(), jointData.end(), compareTo);
    unsigned int jdx = 0;

    //vertices, tex coords, normals
    for (int i = 0; i < aimesh->mNumVertices; ++i)
    {
        glm::vec3 p, n;
        p.x = aimesh->mVertices[i].x;
        p.y = aimesh->mVertices[i].y;
        p.z = aimesh->mVertices[i].z;
              
        n.x = aimesh->mNormals[i].x;
        n.y = aimesh->mNormals[i].y;
        n.z = aimesh->mNormals[i].z;
        
        glm::vec2 t;
        if (aimesh->mTextureCoords[0])
        {
            t.x = aimesh->mTextureCoords[0][i].x;
            t.y = aimesh->mTextureCoords[0][i].y;
        }
        else
        {
            t.x = 0;
            t.y = 0;
        }

        if (aimesh->HasBones())
        {
            glm::ivec3 ji;
            glm::vec3 jw;
            while (jointData[jdx].vertexId != i)
            {
                ++jdx;
            }
            if (jointData[jdx].vertexId == i)
            {
                ji.x = jointData[jdx].jointId;
                jw.x = jointData[jdx].weight;
                ++jdx;
            }
            else
            {
                ji.x = 0;
                jw.x = 0;
            }
            if (jointData[jdx].vertexId == i)
            {
                ji.y = jointData[jdx].jointId;
                jw.y = jointData[jdx].weight;
                ++jdx;
            }
            else
            {
                ji.y = 0;
                jw.y = 0;
            }
            if (jointData[jdx].vertexId == i)
            {
                ji.z = jointData[jdx].jointId;
                jw.z = jointData[jdx].weight;
                ++jdx;
            }
            else
            {
                ji.z = 0;
                jw.z = 0;
            }

            float total = jw[0] + jw[1] + jw[2];
            jw /= total;

            vertices.push_back(Vertex(p, t, n, ji, jw));
        }
        else
        {
            vertices.push_back(Vertex(p, t, n));
        }
    }

    /*for (int i = 0; i < jointData.size(); ++i)
    {
        std::cout << jointData[i].vertexId << " " << jointData[i].weight << " " << jointData[i].jointId << std::endl;
    }*/

    /*for (int i = 0; i < vertices.size(); ++i)
    {
        Vertex v = vertices[i];
        std::cout << i << "\t" << glm::to_string(v.jointIds) << "\t\t" << glm::to_string(v.jointWeights) << std::endl;
    }*/

    //elements
    for (int i = 0; i < aimesh->mNumFaces; ++i)
    {
        aiFace face = aimesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; ++j)
        {
            elements.push_back(face.mIndices[j]);
        }
    }

    //material
    aiMaterial* aiMaterial = aiscene->mMaterials[aimesh->mMaterialIndex];
    glm::vec3 ambient, diffuse, specular;
    float shininess;
    aiColor3D color(1.0f, 1.0f, 1.0f);

    aiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);
    ambient = glm::vec3(color.r, color.g, color.b);
    aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    diffuse = glm::vec3(color.r, color.g, color.b);
    aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);
    specular = glm::vec3(color.r, color.g, color.b);
    aiMaterial->Get(AI_MATKEY_SHININESS, shininess);

    shininess += 1.0;
    shininess /= 128.0;

    material = new Material(ambient, diffuse, specular, shininess);

    Texture* diffuseTex = nullptr;
    Texture* specularTex = nullptr;

    if (aiMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString str;
        aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        diffuseTex = new Texture(directory + "/" + str.C_Str(), GL_SRGB_ALPHA);
    }

    if (aiMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0)
    {
        aiString str;
        aiMaterial->GetTexture(aiTextureType_SPECULAR, 0, &str);
        specularTex = new Texture(directory + "/" + str.C_Str(), GL_RGBA);
    }

    material->setDiffuseTexture(diffuseTex);
    material->setSpecularTexture(specularTex);

    return new Mesh(vertices, elements, material);
}

Model::Model()
{

}

Model::Model(const std::string& source)
{
    create(source);
}

Model::Model(std::vector<Mesh*>& meshes)
{
    this->meshes = meshes;
}

Model::Model(Mesh* mesh)
{
    meshes.push_back(mesh);
}

Joint* Model::loadJoints(aiNode* node, Joint* parent)
{
    glm::mat4 pLocal;
    glm::mat4 pInverse;
    if (parent == nullptr)
    {
        pLocal = glm::mat4(1.0);
        pInverse = glm::mat4(1.0);
    }
    else
    {
        pLocal = parent->getLocalTransform();
        pInverse = parent->getInverseTransform();
    }
    glm::mat4 m = glm::inverse(pLocal * aiMatrix4x4_mat4(node->mTransformation));
    //aiMatrix4x4_mat4(aiscene->mMeshes[0]->mBones[jointId]->mOffsetMatrix)

    //std::cout << aiscene->mMeshes[0]->mNumBones << " " << node->mName.C_Str() << " " << jointId << std::endl;
    Joint* joint = new Joint(jointId, node->mName.C_Str(), aiMatrix4x4_mat4(node->mTransformation), aiMatrix4x4_mat4(aiscene->mMeshes[0]->mBones[jointId]->mOffsetMatrix), glm::mat4(1.0f), parent);
    ++jointId;
    joints[joint->getName()] = joint;

    for (int i = 0; i < node->mNumChildren; ++i)
    {
        joint->addChild(loadJoints(node->mChildren[i], joint));
    }

    return joint;
}

void Model::create(const std::string& source)
{
    Assimp::Importer import;
    import.ReadFile(source, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
    aiscene = import.GetOrphanedScene();

    if (!aiscene || aiscene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiscene->mRootNode)
    {
        return;
    }
    directory = source.substr(0, source.find_last_of('/'));

    aiNode* aiRootNode = aiscene->mRootNode;
    //printHierarchy(aiRootNode);

    processNode(aiRootNode, aiscene);

    jointId = 0;

    if (aiscene->mMeshes[0]->mNumBones > 0)
    {
        rootJoint = loadJoints(aiRootNode->mChildren[0]->mChildren[0], nullptr);
    }
    else
    {
        rootJoint = nullptr;
    }
    
    this->currentAnimation = "";
}

void Model::printAnimationNames()
{
    for (int i = 0; i < aiscene->mNumAnimations; ++i)
    {
        std::cout << aiscene->mAnimations[i]->mName.C_Str() << std::endl;
    }
    
}

void Model::printHierarchy(aiNode* node, std::string offset)
{
    std::cout << offset << "name: " << node->mName.C_Str() << " " << node->mNumMeshes << std::endl;

    for (int i = 0; i < node->mNumChildren; ++i)
    {
        printHierarchy(node->mChildren[i], offset+"    ");
    }
    
}

void setJointUniforms(Shader* shader, Joint* joint)
{
    shader->setUniformMatrix4fv("jointTransforms[" + std::to_string(joint->getId()) + "]", joint->transform);

    for (int i = 0; i < joint->children.size(); ++i)
    {
        setJointUniforms(shader, joint->children[i]);
    }
}

void Model::draw(Shader* shader, Camera* camera, std::vector<Light*>* lights)
{
    if (shader != nullptr)
    {
        shader->bind();

        if (camera != nullptr)
        {
            shader->setUniformMatrix4fv("model", getTransform());
            shader->setUniformMatrix4fv("view", camera->getView());
            shader->setUniformMatrix4fv("projection", camera->getProjection());
            shader->setUniform3f("viewPosition", camera->position);
        }

        if (rootJoint != nullptr)
        {
            shader->setUniform1i("hasJoints", true);
            setJointUniforms(shader, rootJoint);
        }
        else
        {
            shader->setUniform1i("hasJoints", false);
        }

        if (lights != nullptr && lights->size() > 0)
        {
            shader->setUniform1i("numLights", lights->size());
            for (int i = 0; i < lights->size(); ++i)
            {
                Light* light = lights->at(i);

                if (light != nullptr)
                {
                    shader->setUniform1i("lights[" + std::to_string(i) + "].type", light->type);

                    shader->setUniform3f("lights[" + std::to_string(i) + "].ambient", light->ambient);
                    shader->setUniform3f("lights[" + std::to_string(i) + "].diffuse", light->diffuse);
                    shader->setUniform3f("lights[" + std::to_string(i) + "].specular", light->specular);

                    shader->setUniform3f("lights[" + std::to_string(i) + "].position", light->position);
                    shader->setUniform3f("lights[" + std::to_string(i) + "].direction", light->direction);
                    shader->setUniform1f("lights[" + std::to_string(i) + "].innerCutoff", cos(glm::radians(light->innerCutoff)));
                    shader->setUniform1f("lights[" + std::to_string(i) + "].outerCutoff", cos(glm::radians(light->outerCutoff)));

                    shader->setUniform1f("lights[" + std::to_string(i) + "].constant", light->constant);
                    shader->setUniform1f("lights[" + std::to_string(i) + "].linear", light->linear);
                    shader->setUniform1f("lights[" + std::to_string(i) + "].quadratic", light->quadratic);
                }
            }
        }

        for (Mesh* mesh : meshes)
        {
            if (mesh != nullptr)
                mesh->draw(shader);
        }
    }
}

glm::vec3 interpolate(const glm::vec3& start, const glm::vec3& end, float amount)
{
    return start + (end - start) * amount;
}

glm::quat interpolate(const glm::quat& start, const glm::quat& end, float amount)
{
    glm::quat quat(0.0f, 0.0f, 0.0f, 1.0f);
    float dot = glm::dot(start, end);
    float amountI = 1.0f - amount;
    if (dot < 0)
    {
        quat = amountI * start + amount * +end;
    }
    else
    {
        quat = amountI * start + amount * -end;
    }
    
    quat = glm::normalize(quat);

    return quat;
}

void Model::applyTransformToJoint(Joint* joint, const std::unordered_map<std::string, glm::mat4>& transforms, const glm::mat4& parentTransform)
{
    glm::mat4 transform;
    auto iterator = transforms.find(joint->getName());
    if (iterator != transforms.end())
        transform = iterator->second;
    else
        transform = joint->getLocalTransform();

    glm::mat4 currentTransform = parentTransform * transform;

    for (Joint* child : joint->children)
        applyTransformToJoint(child, transforms, currentTransform);

    joint->transform = currentTransform * joint->getInverseTransform();
}

void Model::update(float delta)
{
    if (aiscene == nullptr)
        return;
    if (aiscene->mNumAnimations == 0)
        return;
    if (rootJoint == nullptr)
        return;

    aiAnimation* aianimation = nullptr;
    for (int i = 0; i < aiscene->mNumAnimations; ++i)
    {
        if (aiscene->mAnimations[i]->mName.C_Str() == currentAnimation)
        {
            aianimation = aiscene->mAnimations[i];
            break;
        }
    }

    if (aianimation == nullptr)
        return;

    animationTime += delta * aianimation->mTicksPerSecond;
    while (animationTime >= aianimation->mDuration)
        animationTime -= aianimation->mDuration;

    //std::cout << animationTime << " " << aianimation->mDuration << " " << aianimation->mTicksPerSecond << std::endl;

    std::unordered_map<std::string, glm::mat4> transforms;

    for (int i = 0; i < aianimation->mNumChannels; ++i)
    {
        aiNodeAnim* ainodeanim = aianimation->mChannels[i];
        Joint* joint = joints[ainodeanim->mNodeName.C_Str()];

        int pcIdx = 0;
        int rcIdx = 0;
        int scIdx = 0;

        for (int j = 1; j < ainodeanim->mNumPositionKeys; ++j)
        {
            if (ainodeanim->mPositionKeys[j].mTime >= animationTime)
            {
                pcIdx = j-1;
                break;
            }
        }
        for (int j = 1; j < ainodeanim->mNumRotationKeys; ++j)
        {
            if (ainodeanim->mRotationKeys[j].mTime >= animationTime)
            {
                rcIdx = j-1;
                break;
            }
        }
        for (int j = 1; j < ainodeanim->mNumScalingKeys; ++j)
        {
            if (ainodeanim->mScalingKeys[j].mTime >= animationTime)
            {
                scIdx = j-1;
                break;
            }
        }

        int pnIdx = pcIdx == ainodeanim->mNumPositionKeys - 1 ? 0 : pcIdx + 1;
        int rnIdx = rcIdx == ainodeanim->mNumRotationKeys - 1 ? 0 : rcIdx + 1;
        int snIdx = scIdx == ainodeanim->mNumScalingKeys - 1 ? 0 : scIdx + 1;

        aiVectorKey cPosKey = ainodeanim->mPositionKeys[pcIdx];
        aiVectorKey nPosKey = ainodeanim->mPositionKeys[pnIdx];
        aiQuatKey cRotKey = ainodeanim->mRotationKeys[rcIdx];
        aiQuatKey nRotKey = ainodeanim->mRotationKeys[rnIdx];
        aiVectorKey cScaKey = ainodeanim->mScalingKeys[scIdx];
        aiVectorKey nScaKey = ainodeanim->mScalingKeys[snIdx];
        float dPosTime = map(float(cPosKey.mTime), float(nPosKey.mTime), 0.0f, 1.0f, animationTime);
        float dRotTime = map(float(cRotKey.mTime), float(nRotKey.mTime), 0.0f, 1.0f, animationTime);
        float dScaTime = map(float(cScaKey.mTime), float(nScaKey.mTime), 0.0f, 1.0f, animationTime);

       /* glm::vec3 cPos = { cPosKey.mValue.x, cPosKey.mValue.y, cPosKey.mValue.z };
        glm::vec3 nPos = { nPosKey.mValue.x, nPosKey.mValue.y, nPosKey.mValue.z };
        glm::quat cRot = { cRotKey.mValue.x, cRotKey.mValue.y, cRotKey.mValue.z, cRotKey.mValue.w };
        glm::quat nRot = { nRotKey.mValue.x, nRotKey.mValue.y, nRotKey.mValue.z, nRotKey.mValue.w };
        glm::vec3 cSca = { cScaKey.mValue.x, cScaKey.mValue.y, cScaKey.mValue.z };
        glm::vec3 nSca = { nScaKey.mValue.x, nScaKey.mValue.y, nScaKey.mValue.z };

        glm::vec3 pos = glm::lerp(cPos, nPos, dPosTime);
        glm::quat rot = glm::lerp(cRot, nRot, dRotTime);
        glm::vec3 sca = glm::lerp(cSca, nSca, dScaTime);

        glm::mat4 p = glm::translate(glm::mat4(1.0f), pos);
        glm::mat4 r = glm::toMat4(rot);
        glm::mat4 s = glm::scale(glm::mat4(1.0f), sca);*/

        aiVector3D pos = cPosKey.mValue + (nPosKey.mValue - cPosKey.mValue) * dPosTime;
        aiVector3D sca = cScaKey.mValue + (nScaKey.mValue - cScaKey.mValue) * dScaTime;
        aiQuaternion rot;
        aiQuaternion::Interpolate(rot, cRotKey.mValue, nRotKey.mValue, dRotTime);

        glm::mat4 p = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, pos.z));
        glm::mat4 r = aiMatrix4x4_mat4(aiMatrix4x4(rot.GetMatrix()));
        glm::mat4 s = glm::scale(glm::mat4(1.0f), glm::vec3(sca.x, sca.y, sca.z));

        transforms[ainodeanim->mNodeName.C_Str()] = p * s * r;
    }

    applyTransformToJoint(rootJoint, transforms, glm::mat4(1.0f));
}
