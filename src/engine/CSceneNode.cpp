#include "CSceneNode.h"
//-------------------------------------
#include <algorithm>

//-------------------------------------
CSceneNode::~CSceneNode() {

    if(mpParent != nullptr) {
        mpParent->RemoveChild(this);
        mpParent = nullptr;
    }

    for(auto &node : mChildren) {
        node->SetParent(nullptr);
    }
    mChildren.clear();
}

// TODO: check long cycles
//-------------------------------------
void
CSceneNode::SetParent(CSceneNode *pParent) {

    // WTF!
    if(pParent == this)
        return;

    // If I'm already the parent, do nothing
    if(pParent == mpParent)
        return;

    // If I have a parent, remove me from it
    if(mpParent != nullptr) {
        mpParent->RemoveChild(this);
    }

    // Set parent
    mpParent = pParent;

    // Add to parent's children list
    if(pParent != nullptr) {
        if (pParent->mpParent != nullptr) {
            pParent->mpParent->RemoveChild(pParent);
        }
        pParent->mChildren.push_back(this);
    }
}

// TODO: check long cycles
//-------------------------------------
void
CSceneNode::AddChild(CSceneNode *pChild) {

    if(pChild == nullptr)
        return;

    // WTF!
    if(pChild == this)
        return;

    pChild->SetParent(this);
}

//-------------------------------------
void
CSceneNode::RemoveChild(CSceneNode *pChild) {

    auto it = std::find(mChildren.begin(), mChildren.end(), pChild);
    if(it != mChildren.end()) {
        pChild->mpParent = nullptr;
        mChildren.erase(it);
    }
}

//-------------------------------------
const mat4 &
CSceneNode::GetMatrixLocal() {

    if(mIsDirtyTransform)
        BuildLocalMatrix3D();

    return mMatrixLocal;
}

//-------------------------------------
const mat4 &
CSceneNode::GetMatrixWorld() {

    if(IsDirtyTransformWorld()) {
        if(mpParent != nullptr) {
            mMatrixWorld = mpParent->GetMatrixWorld() * GetMatrixLocal();

            return mMatrixWorld;
        }

        mMatrixWorld = GetMatrixLocal();
    }

    return mMatrixWorld;
}

//-------------------------------------
bool
CSceneNode::IsDirtyTransformWorld() const {

    if(mpParent != nullptr) {
        return (mIsDirtyTransform || mpParent->IsDirtyTransformWorld());
    }

    return mIsDirtyTransform;
}

//-------------------------------------
void
CSceneNode::BuildLocalMatrix2D() {

    mIsDirtyTransform = false;
    mMatrixLocal.MakeTransform(mPosition, vec3(mScale.x, mScale.y, 1), mRotation.z);
}

//-------------------------------------
void
CSceneNode::BuildLocalMatrix3D() {

    mIsDirtyTransform = false;
    mMatrixLocal.MakeTransform(mPosition, mScale, mRotation);
}
