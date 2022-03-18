#include "PlaneObj.h"
bool APlaneObj::SetVertexData()
{
    m_VertexList.resize(4);
    // -Z plane
    m_VertexList[0].p = AVector3(-1.0f, 1.0f, 0.5f);
    m_VertexList[0].n = AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[0].c = AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[0].t = AVector2(0.0f, 0.0f);

    m_VertexList[1].p = AVector3(1.0f, 1.0f, 0.5f);
    m_VertexList[1].n = AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[1].c = AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[1].t = AVector2(1.0f, 0.0f);


    m_VertexList[2].p = AVector3(-1.0f, -1.0f, 0.5f);
    m_VertexList[2].n = AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[2].c = AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[2].t = AVector2(0.0f, 1.0f);


    m_VertexList[3].p = AVector3(1.0f, -1.0f, 0.5f);
    m_VertexList[3].n = AVector3(0.0f, 0.0f, -1.0f);
    m_VertexList[3].c = AVector4(1.0f, 1.0f, 1.0f, 1.0f);
    m_VertexList[3].t = AVector2(1.0f, 1.0f);
    return true;
}
bool APlaneObj::SetIndexData()
{
    m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
    m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
    return true;
}

APlaneObj::APlaneObj()
{

}
APlaneObj::~APlaneObj()
{

}