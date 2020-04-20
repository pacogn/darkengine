#include "CSceneManager.h"
#include "CMesh.h"
#include "CCamera.h"
#include "CLight.h"
//-------------------------------------
#include <Common/Core/stringAux.h>
#include <algorithm>

//-------------------------------------
CSceneManager   *CSceneManager::mpInstance = nullptr;

//-------------------------------------
CSceneManager *
CSceneManager::GetInstance() {
    if (mpInstance == nullptr) {
        mpInstance = new CSceneManager;
    }

    return mpInstance;
}

//-------------------------------------
void
CSceneManager::DeleteInstance() {
    if (mpInstance != nullptr) {
        delete mpInstance;
        mpInstance = nullptr;
    }
}

//-------------------------------------
CSceneManager::~CSceneManager() {
    for(CSceneNode *node : mNodes) {
        if(node != nullptr) {
            delete node;
        }
    }

    mNodes.clear();
    mMeshes.clear();
    mCameras.clear();
    mLights.clear();
}

//-------------------------------------
CSceneNode *
CSceneManager::CreateSceneNode() {
    CSceneNode   *pSceneNode;

    pSceneNode = new CSceneNode;
    //pSceneNode->mNodeType = ENodeType::Node;

    mNodes.push_back(pSceneNode);

    return pSceneNode;
}

//-------------------------------------
CMesh *
CSceneManager::CreateMesh() {
    CMesh   *pMesh;

    pMesh = new CMesh;
    //pMesh->mNodeType = ENodeType::Mesh;

    mNodes.push_back(pMesh);
    mMeshes.push_back(pMesh);

    return pMesh;
}

//-------------------------------------
CCamera *
CSceneManager::CreateCamera() {
    CCamera *pCamera;

    pCamera = new CCamera;
    //pCamera->mNodeType = ENodeType::Camera;

    mNodes.push_back(pCamera);
    mCameras.push_back(pCamera);

    return pCamera;
}

//-------------------------------------
CLight *
CSceneManager::CreateLight() {
    CLight *pLight;

    pLight = new CLight;
    //pLight->mNodeType = ENodeType::Light;

    mNodes.push_back(pLight);
    mLights.push_back(pLight);

    return pLight;
}

//-------------------------------------
CSceneNode *
CSceneManager::GetSceneNodeByName(const string &name) const {

    for (CSceneNode *pNode : mNodes) {
        if (pNode != nullptr) {
            const std::string &objName = pNode->GetName();

            if (stricmp(objName.c_str(), name.c_str()) == 0) {
                return pNode;
            }
        }
    }

    return nullptr;
}

//-------------------------------------
CMesh *
CSceneManager::GetMeshByName(const string &name) const {

    for (CMesh *pMesh : mMeshes) {
        if (pMesh != nullptr) {
            const std::string &objName = pMesh->GetName();

            if (stricmp(objName.c_str(), name.c_str()) == 0) {
                return pMesh;
            }
        }
    }

    return nullptr;
}

//-------------------------------------
CCamera *
CSceneManager::GetCameraByName(const string &name) const {

    for (CCamera *pCamera : mCameras) {
        if (pCamera != nullptr) {
            const std::string &objName = pCamera->GetName();

            if (stricmp(objName.c_str(), name.c_str()) == 0) {
                return pCamera;
            }
        }
    }

    return nullptr;
}

//-------------------------------------
CLight *
CSceneManager::GetLightByName(const string &name) const {

    for (CLight *pLight : mLights) {
        if (pLight != nullptr) {
            const std::string &objName = pLight->GetName();

            if (stricmp(objName.c_str(), name.c_str()) == 0) {
                return pLight;
            }
        }
    }

    return nullptr;
}

//-------------------------------------
CSceneNode *
CSceneManager::GetSceneNodeByUserId(int32_t userId) const {
    for (CSceneNode *pNode : mNodes) {
        if (pNode != nullptr) {
            if (pNode->GetUserId() == userId) {
                return pNode;
            }
        }
    }

    return nullptr;
}

//-------------------------------------
CMesh *
CSceneManager::GetMeshByUserId(int32_t userId) const {
    for (CMesh *pMesh: mMeshes) {
        if (pMesh != nullptr) {
            if (pMesh->GetUserId() == userId) {
                return pMesh;
            }
        }
    }

    return nullptr;
}

//-------------------------------------
CCamera *
CSceneManager::GetCameraByUserId(int32_t userId) const {
    for (CCamera *pCamera : mCameras) {
        if (pCamera != nullptr) {
            if (pCamera->GetUserId() == userId) {
                return pCamera;
            }
        }
    }

    return nullptr;
}

//-------------------------------------
CLight *
CSceneManager::GetLightByUserId(int32_t userId) const {
    for (CLight *pLight : mLights) {
        if (pLight != nullptr) {
            if (pLight->GetUserId() == userId) {
                return pLight;
            }
        }
    }

    return nullptr;
}


//-------------------------------------
bool
CSceneManager::DeleteSceneNode(CSceneNode *node) {
    auto it = std::find(mNodes.begin(), mNodes.end(), node);
    if(it != mNodes.end()) {
        mNodes.erase(it);

        //if(node->mNodeType == ENodeType::Mesh) {
            auto it2 = std::find(mMeshes.begin(), mMeshes.end(), node);
            if (it2 != mMeshes.end()) {
                mMeshes.erase(it2);
            }
        //}

        //else if(node->mNodeType == ENodeType::Mesh) {
            auto it3 = std::find(mCameras.begin(), mCameras.end(), node);
            if (it3 != mCameras.end()) {
                mCameras.erase(it3);
            }
        //}

        //else if(node->mNodeType == ENodeType::Light) {
            auto it4 = std::find(mLights.begin(), mLights.end(), node);
            if (it4 != mLights.end()) {
                mLights.erase(it4);
            }
        //}

        delete node;

        return true;
    }

    return false;
}

