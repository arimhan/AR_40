#include "FbxObj.h"

bool AFbxObj::Init() { m_fTimer = 61; return true; }
bool AFbxObj::Frame() { return true; }
bool AFbxObj::Render() 
{
	AFbxImporter* pAnimImp = nullptr;
	if (m_pAnimImp != nullptr)
	{
		pAnimImp = m_pAnimImp;
	}
	else
	{
		pAnimImp = m_pMeshImp;
	}

	m_fTimer += g_fSecPerFrame * pAnimImp->m_Scene.iFrameSpeed * m_fDir * 0.33f; //speed;
	if (m_fTimer >= pAnimImp->m_Scene.iEnd)
	{
		//재생 끝나면 다시 처음부터~
		m_fTimer = pAnimImp->m_Scene.iStart;
	}

	int iFrame = m_fTimer;
	//frame은 max-> 0, min(anm->신end -1)
	for (int iObj=0; iObj<m_pMeshImp->m_pDrawList.size(); iObj++)
	{
		AFbxModel* pFbxObj = m_pMeshImp->m_pDrawList[iObj];
		//_tcsstr
		if (_tcsstr(pFbxObj->m_csName.c_str(), L"LOD") != nullptr) //SK_Mannequin_LOD0
		{
			if (_tcsstr(pFbxObj->m_csName.c_str(), L"LOD") == nullptr) 
			{
				continue;
			}
		}
		if (pFbxObj->m_bSkinned) //스키닝 여부에 따라 렌더링 설정
		{
			for (auto data : pAnimImp->m_pFbxModelMap)
			{
				//map <wstring 이름, AFbxModel animmodel값> 
				wstring name = data.first;
				AFbxModel* pAnimModel = data.second;
				auto model = m_pMeshImp->m_pFbxModelMap.find(name);
				if (model == m_pMeshImp->m_pFbxModelMap.end())
				{
					continue; //error
				}
				AFbxModel* pTreeModel = model->second;
				if (pTreeModel == nullptr)
				{
					continue; //error
				}
				auto bindpose = pFbxObj->m_dxMatrixBindPoseMap.find(name);
				if (bindpose != pFbxObj->m_dxMatrixBindPoseMap.end() && pAnimModel)
				{
					TMatrix matInverseBindpose = bindpose->second;
					m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex] = matInverseBindpose
						* Interplate(pAnimImp, pAnimModel, m_fTimer);
				}
				T::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex], 
					&m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex]);
			}
		}
		else //m_bSkinned가 아니면
		{
			for (int iNode = 0; iNode < m_pMeshImp->m_pTreeList.size(); iNode++)
			{
				AFbxModel* pFbxModel = m_pMeshImp->m_pTreeList[iNode];
				if (pFbxModel->m_AnimTrack.size() > 0) //AnimTrack이 없을 경우
				{
					m_matBoneArray.matBoneWorld[iNode] = Interplate(pAnimImp, pFbxModel, m_fTimer);
				}
				T::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[iNode],
					&m_matBoneArray.matBoneWorld[iNode]);
			}
		}

		m_pContext->UpdateSubresource(m_pMeshImp->m_pBoneCB, 0, NULL, &m_matBoneArray, 0, 0);
		m_pContext->VSSetConstantBuffers(2, 1, &m_pMeshImp->m_pBoneCB);

		T::TVector3 vLight(cosf(g_fGameTimer) * 100.0f, 100, sinf(g_fGameTimer) * 100.0f);
		T::D3DXVec3Normalize(&vLight, &vLight);
		vLight = vLight * -1.0f;

		pFbxObj->m_LightConstantList.vLightDir.x = vLight.x;
		pFbxObj->m_LightConstantList.vLightDir.y = vLight.y;
		pFbxObj->m_LightConstantList.vLightDir.z = vLight.z;
		pFbxObj->m_LightConstantList.vLightDir.w = 1.0f;

		pFbxObj->m_LightConstantList.vCameraDir.x = m_pMainCamera->m_vLook.x;
		pFbxObj->m_LightConstantList.vCameraDir.y = m_pMainCamera->m_vLook.y;
		pFbxObj->m_LightConstantList.vCameraDir.z = m_pMainCamera->m_vLook.z;
		pFbxObj->m_LightConstantList.vCameraDir.w = 1.0f;

		pFbxObj->m_LightConstantList.vCameraPos.x = m_pMainCamera->m_vCamera.x;
		pFbxObj->m_LightConstantList.vCameraPos.y = m_pMainCamera->m_vCamera.y;
		pFbxObj->m_LightConstantList.vCameraPos.z = m_pMainCamera->m_vCamera.z;
		pFbxObj->m_LightConstantList.vCameraPos.w = 1.0f;

		pFbxObj->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
		pFbxObj->Render();
	}
	return true;
}
bool AFbxObj::Release() { return true; }

void AFbxObj::GenAABB()
{
	m_BoxCollision.vMin = T::TVector3(100000, 100000, 100000);
	m_BoxCollision.vMax = T::TVector3(-100000, -100000, -100000);

	for (int i = 0; i < m_VertexList.size(); i++)
	{
		//박스 충돌값의 min, max의 x,y,z값을 비교한다. (충돌값 체크)
		if (m_BoxCollision.vMin.x > m_VertexList[i].p.x)
		{
			m_BoxCollision.vMin.x = m_VertexList[i].p.x;
		}
		if (m_BoxCollision.vMin.y > m_VertexList[i].p.y)
		{
			m_BoxCollision.vMin.y = m_VertexList[i].p.y;
		}
		if (m_BoxCollision.vMin.z > m_VertexList[i].p.z)
		{
			m_BoxCollision.vMin.z = m_VertexList[i].p.z;
		}
		//max 체크
		if (m_BoxCollision.vMax.x < m_VertexList[i].p.x)
		{
			m_BoxCollision.vMax.x = m_VertexList[i].p.x;
		}
		if (m_BoxCollision.vMax.y < m_VertexList[i].p.y)
		{
			m_BoxCollision.vMax.y = m_VertexList[i].p.y;
		}
		if (m_BoxCollision.vMax.z < m_VertexList[i].p.z)
		{
			m_BoxCollision.vMax.z = m_VertexList[i].p.z;
		}
	}

	m_BoxCollision.vList[0] = T::TVector3(//각VB의 좌표값을 위치 min,max로 표기한다. (-1,1,-1)
		m_BoxCollision.vMin.x, m_BoxCollision.vMax.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[1] = T::TVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMax.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[2] = T::TVector3(
		m_BoxCollision.vMin.x, m_BoxCollision.vMin.y, m_BoxCollision.vMin.z);
	m_BoxCollision.vList[3] = T::TVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMin.y, m_BoxCollision.vMin.z);

	m_BoxCollision.vList[4] = T::TVector3(
		m_BoxCollision.vMin.x, m_BoxCollision.vMax.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[5] = T::TVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMax.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[6] = T::TVector3(
		m_BoxCollision.vMin.x, m_BoxCollision.vMin.y, m_BoxCollision.vMax.z);
	m_BoxCollision.vList[7] = T::TVector3(
		m_BoxCollision.vMax.x, m_BoxCollision.vMin.y, m_BoxCollision.vMax.z);
}


bool AFbxObj::RenderShadoe(AShader* pShader)
{
	//Shadow Render시, Anim이 있을 경우 Anim으로, 없을 경우 Mesh로
	AFbxImporter* pAnimImp = nullptr;
	if (m_pAnimImp != nullptr)
	{
		pAnimImp = m_pAnimImp;
	}
	else
	{
		pAnimImp = m_pMeshImp;
	}

	m_fTimer += g_fSecPerFrame * pAnimImp->m_Scene.iFrameSpeed * m_fDir * 0.3f;
	if (m_fTimer >= pAnimImp->m_Scene.iEnd)
	{
		m_fTimer = pAnimImp->m_Scene.iStart;
	}

	int iFrame = m_fTimer;
	iFrame = max(0, min(pAnimImp->m_Scene.iEnd - 1, iFrame));

	for (int iObj = 0; iObj < m_pMeshImp->m_pDrawList.size(); iObj++)
	{
		AFbxModel* pFbxObj = m_pMeshImp->m_pDrawList[iObj];
		if (_tcsstr(pFbxObj->m_csName.c_str(), L"LOD") !== nullptr)
		{
			if(_tcsstr(pFbxObj->m_csName.c_str(), L"LOD0") !== nullptr)
			{	continue; }
		}

		//m_bSkinned 애니메이션일때
		if (pFbxObj->m_bSkinned)
		{
			for (auto data : pAnimImp->m_pFbxModelMap)
			{
				//전부 map으로 묶어둠. 
				wstring name = data.first;
				AFbxModel* pAnimModel = data.second;

				auto model = m_pMeshImp->m_pFbxModelMap.find(name);
				if (model == m_pMeshImp->m_pFbxModelMap.end())
				{					continue;				}
				AFbxModel* pTreeModel = model->second;
				if(pTreeModel == nullptr)
				{					continue;				}
				auto bindpose = pFbxObj->m_dxMatrixBindPoseMap.find(name);
				if (bindpose != pFbxObj->m_dxMatrixBindPoseMap.end() && pAnimModel)
				{
					TMatrix matInverseBindpose = bindpose->second;
					m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex] = matInverseBindpose * Interplate(pAnimImp, pAnimModel, m_fTimer);
				}
				T::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex], &m_matBoneArray.matBoneWorld[pTreeModel->m_iIndex]);
			}
		}
		else
		{
			for (int iNode = 0; iNode < m_pMeshImp->m_pTreeList.size(); iNode++)
			{
				AFbxModel* pFbxModel = m_pMeshImp->m_pTreeList[iNode];

				//AnimTrack이 있을경우
				if (pFbxModel->m_AnimTrack.size() > 0)
				{
					//Interplate 보간작업
					m_matBoneArray.matBoneWorld[iNode] = Interplate(pAnimImp, pFbxModel, m_fTimer);
				}
				T::D3DXMatrixTranspose(&m_matBoneArray.matBoneWorld[pFbxModel->m_iIndex], &m_matBoneArray.matBoneWorld[pFbxModel->m_iIndex]);
			}
		}
	}
}

T::TMatrix	AFbxObj::Interplate(AFbxImporter* pAnimImp, AFbxModel* pModel, float fTime) 
{ 
	T::TMatrix matAnim;
	AScene aScene = pAnimImp->m_Scene;
	int iStart = max(aScene.iStart, fTime);
	int iEnd = min(aScene.iEnd, fTime + 1);

	//보간 = A ~7.5f ~ 8 , 9.5f <= 10 ~ 20 => 20.1
	ATrack A = pModel->m_AnimTrack[iStart];
	ATrack B = pModel->m_AnimTrack[iEnd];
	float s = fTime - (float)iStart;

	T::TVector3 Pos;
	T::D3DXVec3Lerp(&Pos, &A.t, &B.t, s);
	T::TVector3 Scale;
	T::D3DXVec3Lerp(&Scale, &A.s, &B.s, s);

	T::TQuaternion Rotation;
	T::D3DXQuaternionSlerp(&Rotation, &A.r, &B.r, s);
	T::TMatrix matScale;
	T::D3DXMatrixScaling(&matScale, Scale.x, Scale.y, Scale.z);
	T::TMatrix matRotation;
	T::D3DXMatrixRotationQuaternion(&matRotation, &Rotation);

	matAnim = matScale * matRotation;
	matAnim._41 = Pos.x;
	matAnim._42 = Pos.y;
	matAnim._43 = Pos.z;

	return matAnim;
}