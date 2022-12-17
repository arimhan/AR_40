#include "PlaneObj.h"
bool APlaneObj::SetVertexData()
{
    m_VertexList.resize(4);
    // -Z plane
    m_VertexList[0].p = A::AVector3(-1.0f, 1.0f, 0.0f);
    m_VertexList[0].n = A::AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[0].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[0].t = A::AVector2(0.0f, 0.0f);

    m_VertexList[1].p = A::AVector3(1.0f, 1.0f, 0.0f);
    m_VertexList[1].n = A::AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[1].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[1].t = A::AVector2(1.0f, 0.0f);

    m_VertexList[2].p = A::AVector3(-1.0f, -1.0f, 0.0f);
    m_VertexList[2].n = A::AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[2].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[2].t = A::AVector2(0.0f, 1.0f);

    m_VertexList[3].p = A::AVector3(1.0f, -1.0f, 0.0f);
    m_VertexList[3].n = A::AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[3].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[3].t = A::AVector2(1.0f, 1.0f);
    return true;
}
bool APlaneObj::SetIndexData()
{
    m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
    m_IndexList.push_back(3); m_IndexList.push_back(2); m_IndexList.push_back(1);
    return true;
}

APlaneObj::APlaneObj(){}
APlaneObj::~APlaneObj(){}