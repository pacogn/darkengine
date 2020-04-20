#pragma once

#include <vector>
#include <string>

//-------------------------------------
using std::string;
using std::vector;

class CSceneNode;
class CCamera;
class CMesh;
class CLight;

//-------------------------------------
class CSceneManager {
public:
    static CSceneManager *  GetInstance();
    static void             DeleteInstance();

public:
    CSceneNode *        CreateSceneNode();
    CMesh *             CreateMesh();
    CCamera *           CreateCamera();
    CLight *            CreateLight();

    CSceneNode *        GetSceneNodeByIndex(size_t index)    { return (index < mNodes.size())   ? mNodes[index]   : nullptr; }
    CMesh *             GetMeshByIndex(size_t index)         { return (index < mMeshes.size())  ? mMeshes[index]  : nullptr; }
    CCamera *           GetCameraByIndex(size_t index)       { return (index < mCameras.size()) ? mCameras[index] : nullptr; }
    CLight *            GetLightByIndex(size_t index)        { return (index < mLights.size())  ? mLights[index]  : nullptr; }

    CSceneNode *        GetSceneNodeByName(const string &name) const;
    CMesh *             GetMeshByName(const string &name) const;
    CCamera *           GetCameraByName(const string &name) const;
    CLight *            GetLightByName(const string &name) const;

    CSceneNode *        GetSceneNodeByUserId(int32_t UserId) const;
    CMesh *             GetMeshByUserId(int32_t UserId) const;
    CCamera *           GetCameraByUserId(int32_t UserId) const;
    CLight *            GetLightByUserId(int32_t UserId) const;

    size_t              GetNumSceneNodes() const             { return mNodes.size();   }
    size_t              GetNumMeshes() const                 { return mMeshes.size();  }
    size_t              GetNumCameras() const                { return mCameras.size(); }
    size_t              GetNumLights() const                 { return mLights.size();  }
    
    bool                DeleteSceneNode(CSceneNode *node);
    bool                DeleteMesh(CMesh *mesh)              { return DeleteSceneNode(reinterpret_cast<CSceneNode *>(mesh));   }
    bool                DeleteCamera(CCamera *camera)        { return DeleteSceneNode(reinterpret_cast<CSceneNode *>(camera)); }
    bool                DeleteLight(CLight *light)           { return DeleteSceneNode(reinterpret_cast<CSceneNode *>(light));  }

protected:
                        CSceneManager()                      = default;
                        CSceneManager(const CSceneManager &) = delete;
                        CSceneManager(CSceneManager &&)      = delete;
    virtual             ~CSceneManager();

    CSceneManager &     operator=(const CSceneManager &)     = delete;
    CSceneManager &     operator=(CSceneManager &&)          = delete;

protected:
    static CSceneManager *  mpInstance;

protected:
    vector<CSceneNode *>    mNodes;
    vector<CMesh *>         mMeshes;
    vector<CCamera *>       mCameras;
    vector<CLight *>        mLights;
};
