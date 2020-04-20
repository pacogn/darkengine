#pragma once

#include <engine/engineEnums.h>
//-------------------------------------
#include <Math/types/CMatrix4.h>
//-------------------------------------
#include <string>
#include <vector>

//-------------------------------------
using mat3   = MindShake::CMatrix3;
using mat4   = MindShake::CMatrix4;
using vec2   = MindShake::CVector2;
using vec3   = MindShake::CVector3;
using vec4   = MindShake::CVector4;
using quat   = MindShake::CQuaternion;

//-------------------------------------
class CSceneNode {
    using Nodes  = std::vector<CSceneNode *>;
    using string = std::string;

public:
                        CSceneNode()                              = default;
    virtual             ~CSceneNode();

    void                Enable()                                  { mEnable = true;                                       }
    void                Disable()                                 { mEnable = false;                                      }
    void                SetEnable(bool set)                       { mEnable = set;                                        }
    bool                IsEnabled() const                         { return mEnable;                                       }

    void                SetName(const string &name)               { mName = name;                                         }
    const string &      GetName() const                           { return mName;                                         }

    void                SetUserId(int32_t userId)                 { mUserId = userId;                                     }
    int32_t             GetUserId() const                         { return mUserId;                                       }

    void                SetPosition(float x, float y)             { SetPosition(vec2(x, y));                              }
    void                SetPosition(const vec2 &pos)              { SetDirtyTransform(); mPosition.x = pos.x, mPosition.y = pos.y;  }
    void                SetPosition(float x, float y, float z)    { SetPosition(vec3(x, y, z));                           }
    void                SetPosition(const vec3 &pos)              { SetDirtyTransform(); mPosition = pos;                 }
    void                SetPositionX(float x)                     { SetDirtyTransform(); mPosition.x = x;                 }
    void                SetPositionY(float y)                     { SetDirtyTransform(); mPosition.y = y;                 }
    void                SetPositionZ(float z)                     { SetDirtyTransform(); mPosition.z = z;                 }
    void                Translate(float x, float y, float z=0)    { Translate(vec3(x, y, z));                             }
    void                Translate(const vec3 &t)                  { SetDirtyTransform(); mPosition += t;                  }

    const vec3 &        GetPosition() const                       { return mPosition;                                     }
    float               GetPosX() const                           { return mPosition.x;                                   }
    float               GetPosY() const                           { return mPosition.y;                                   }
    float               GetPosZ() const                           { return mPosition.z;                                   }

    void                SetScale2D(float s)                       { SetScale2D(vec2(s));                                  }
    void                SetScale2D(float x, float y)              { SetScale2D(vec2(x, y));                               }
    void                SetScale2D(const vec2 &s)                 { SetDirtyTransform(); mScale.x = s.x, mScale.y = s.y;  }
    void                SetScale3D(float s)                       { SetScale3D(vec3(s));                                  }
    void                SetScale3D(float x, float y, float z)     { SetScale3D(vec3(x, y, z));                            }
    void                SetScale3D(const vec3 &s)                 { SetDirtyTransform(); mScale = s;                      }
    void                SetScaleX(float x)                        { SetDirtyTransform(); mScale.x = x;                    }
    void                SetScaleY(float y)                        { SetDirtyTransform(); mScale.y = y;                    }
    void                SetScaleZ(float z)                        { SetDirtyTransform(); mScale.z = z;                    }
    void                Scale(float x, float y, float z=0)        { Scale(vec3(x, y, z));                                 }
    void                Scale(const vec3 &scale)                  { SetDirtyTransform(); mScale += scale;                 }

    const vec3 &        GetScale() const                          { return mScale;                                        }
    float               GetScaleX() const                         { return mScale.x;                                      }
    float               GetScaleY() const                         { return mScale.y;                                      }
    float               GetScaleZ() const                         { return mScale.z;                                      }

    void                SetRotation(float x, float y, float z)    { SetRotation(vec3(x, y, z));                           }
    void                SetRotation(const vec3 &angles)           { SetDirtyTransform(); mRotation = angles;              }
    void                SetRotationX(float x)                     { SetDirtyTransform(); mRotation.x = x;                 }
    void                SetRotationY(float y)                     { SetDirtyTransform(); mRotation.y = y;                 }
    void                SetRotationZ(float z)                     { SetDirtyTransform(); mRotation.z = z;                 }
    void                Rotate(float x, float y, float z)         { Rotate(vec3(x, y, z));                                }
    void                Rotate(const vec3 &angles)                { SetDirtyTransform(); mRotation += angles;             }
    void                RotateZ(float z)                          { SetDirtyTransform(); mRotation.z += z;                }

    const vec3 &        GetRotation() const                       { return mRotation;                                     }
    float               GetRotationX() const                      { return mRotation.x;                                   }
    float               GetRotationY() const                      { return mRotation.y;                                   }
    float               GetRotationZ() const                      { return mRotation.z;                                   }

    void                SetParent(CSceneNode *pParent);
    CSceneNode *        GetParent() const                         { return mpParent;                                      }
    void                AddChild(CSceneNode *pChild);
    void                RemoveChild(CSceneNode *pChild);
    CSceneNode *        GetChild(size_t index)                    { return (index < mChildren.size()) ? mChildren[index] : nullptr; }
    size_t              GetNumChildren() const                    { return mChildren.size();                              }

    virtual const mat4 &GetMatrixLocal();
    virtual const mat4 &GetMatrixWorld();

    void                SetDirtyTransform();
    bool                IsDirtyTransform() const                  { return mIsDirtyTransform;                             }
    bool                IsDirtyTransformWorld() const;

protected:
    void                BuildLocalMatrix2D();
    void                BuildLocalMatrix3D();

private:
                        CSceneNode(const CSceneNode &) = delete;
                        CSceneNode(CSceneNode &&)      = delete;

    CSceneNode &        operator=(const CSceneNode &)  = delete;
    CSceneNode &        operator=(CSceneNode &&)       = delete;

protected:
    string          mName;
    int32_t         mUserId   { 0 };

    mat4            mMatrixLocal { mat4::kIDENTITY };
    mat4            mMatrixWorld { mat4::kIDENTITY };

    CSceneNode *    mpParent  { nullptr };
    Nodes           mChildren;

    vec3            mPosition { 0 };
    vec3            mScale    { 1 };
    vec3            mRotation { 0 };

    ENodeType       mType     { ENodeType::Node };

    bool            mEnable   { true };
    bool            mIsDirtyTransform { true };
};

//-------------------------------------
inline void
CSceneNode::SetDirtyTransform() { 
    mIsDirtyTransform = true;
    for(auto node : mChildren) {
        node->SetDirtyTransform();
    }
}