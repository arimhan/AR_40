#include "FbxLoader.h"


bool AFbxObj::SetIndexData()
{
	return true;
}


bool AFbxLoader::Load(string filename)
{
	bool bRet = m_pFbxImporter->Initialize(filename.c_str());
	bRet = m_pFbxImporter->Import(m_pFbxScene);
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode, nullptr);

	for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
	{
		ParseMesh(m_ObjList[iObj]);
	}
	return true;
}

void AFbxLoader::PreProcess(FbxNode* pNode, FbxNode* pParent)
{
	//Camera, Light, Mesh, Shape, Animation �۾� �� Mesh�� ������ �۾��� �Ѵ�.
	FbxMesh* pMesh = pNode->GetMesh();
	if (pMesh)
	{
		//FbxParent�� FbxNode�� ���� �������ش�.
		AFbxObj* pFbx = new AFbxObj;
		pFbx->m_pFbxParent = pParent;
		pFbx->m_pFbxNode = pNode;
		m_ObjList.push_back(pFbx);
	}
	int iNumChild = pNode->GetChildCount();
	for (int iNode = 0; iNode < iNumChild; iNode++)
	{
		FbxNode* pChild = pNode->GetChild(iNode);
		PreProcess(pChild, pNode);
	}
}

void AFbxLoader::ParseMesh(AFbxObj* pObj)
{
	FbxMesh* pFbxMesh = pObj->m_pFbxNode->GetMesh();
	if (pFbxMesh)
	{
		//Layer ����. (�������� ���� ������)
		vector<FbxLayerElementUV*> pVertexUvSet;
		vector<FbxLayerElementMaterial*> pMaterialSet;
		int iLayerCount = pFbxMesh->GetLayerCount();
		for (int iLayer = 0; iLayer < iLayerCount; iLayer++)
		{
			FbxLayer* pFbxLayer = pFbxMesh->GetLayer(iLayer);
			if (pFbxLayer->GetUVs() != nullptr)
			{
				pVertexUvSet.push_back(pFbxLayer->GetUVs());
			}
			/*if (pFbxLayer->GetMaterials() != nullptr)
			{
				pMaterialSet.push_back(pFbxLayer->GetMaterials());
			}*/
		}
		int iNumMtrl = pObj->m_pFbxNode->GetMaterialCount();
		for (int iMtrl = 0; iMtrl < iNumMtrl; iMtrl++)
		{
			FbxSurfaceMaterial* pSurface = pObj->m_pFbxNode->GetMaterial(iMtrl);
			if (pSurface)
			{
				string TextureName = ParseMaterial(pSurface);
				pObj->m_szTexFileNmae = L"../../data/fbx/";
				pObj->m_szTexFileNmae += to_mw(TextureName);
			}
		}

		//�ﰢ��, �簢��
		int iNumPolyCount = pFbxMesh->GetPolygonCount();
		FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
		int iNumFace = 0;
		for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
		{
			int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
//���̽� ������ ����������� -2 (����-2) �������� �簢���� ��쵵 ������ ������ ���� �����Ͽ� ����ϱ� ������ ��������2���� ����� ��(?)
			iNumFace = iPolySize - 2;
			for (int iFace = 0; iFace < iNumFace; iFace++)
			{
				// 1 2
				// 0 3
				// max 021, 032 -> 012, 023
				int iVertexIndex[3] = { 0, iFace + 2, iFace + 1 };
				int iCornerIndex[3];
				iCornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, iVertexIndex[0]);
				iCornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, iVertexIndex[1]);
				iCornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, iVertexIndex[2]);

				for (int iIndex = 0; iIndex < 3; iIndex++)
				{
					AVertex tVertex;
					//max (x,z,y) -> dx (x,y,z)
					FbxVector4 v = pVertexPositions[iCornerIndex[iIndex]];
					tVertex.p.x = v.mData[0];
					tVertex.p.y = v.mData[2]; //y,z�� �ٲܰ�
					tVertex.p.z = v.mData[1];

					//UV
					int u[3];
					u[0] = pFbxMesh->GetTextureUVIndex(iPoly, iVertexIndex[0]);
					u[1] = pFbxMesh->GetTextureUVIndex(iPoly, iVertexIndex[1]);
					u[2] = pFbxMesh->GetTextureUVIndex(iPoly, iVertexIndex[2]);
					if (pVertexUvSet.size() > 0)
					{
						FbxLayerElementUV* pUVset = pVertexUvSet[0];
						FbxVector2 uv;
						ReadTextureCoord(pFbxMesh, pUVset, iCornerIndex[iIndex], u[iIndex], uv);
						tVertex.t.x = uv.mData[0];
						tVertex.t.y = 1.0f - uv.mData[1];
					}
					pObj->m_VertexList.push_back(tVertex);
				}
			}
		}
	}
}

void AFbxLoader::ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVset, int iVIndex, int iUVIndex, FbxVector2& uv)
{
	FbxLayerElementUV* pFbxLayerElementUV = pUVset;
	if (pFbxLayerElementUV == nullptr) { return; }

	switch (pFbxLayerElementUV->GetMappingMode())
	{
		case FbxLayerElementUV::eByControlPoint:
		{
			switch (pFbxLayerElementUV->GetReferenceMode())
			{
				case FbxLayerElementUV::eDirect:
				{
					FbxVector2 fbxUV = pFbxLayerElementUV->GetDirectArray().GetAt(iVIndex);
					uv.mData[0] = fbxUV.mData[0];
					uv.mData[1] = fbxUV.mData[1];
					break;
				}
				case FbxLayerElementUV::eIndexToDirect:
				{
					int id = pFbxLayerElementUV->GetIndexArray().GetAt(iVIndex);
					FbxVector2 fbxUV = pFbxLayerElementUV->GetDirectArray().GetAt(id);
					uv.mData[0] = fbxUV.mData[0];
					uv.mData[1] = fbxUV.mData[1];
					break;
				}
			}
			break;
		}
		case FbxLayerElementUV::eByPolygonVertex:
		{
			switch (pFbxLayerElementUV->GetReferenceMode())
			{
				case FbxLayerElementUV::eDirect:
				case FbxLayerElementUV::eIndexToDirect:
				{
					uv.mData[0] = pFbxLayerElementUV->GetDirectArray().GetAt(iUVIndex).mData[0];
					uv.mData[1] = pFbxLayerElementUV->GetDirectArray().GetAt(iUVIndex).mData[1];
					break;
				}
			}
			break;
		}
	}
}

string AFbxLoader::ParseMaterial(FbxSurfaceMaterial* pMtrl)
{
	string name = pMtrl->GetName();
	auto Property = pMtrl->FindProperty(FbxSurfaceMaterial::sDiffuse);
	//fbxsdk::FbxProperty
	if (Property.IsValid())
	{
		const FbxFileTexture* pTex = Property.GetSrcObject<FbxFileTexture>(0);
		if (pTex != nullptr)
		{
			const CHAR* szFileName = pTex->GetFileName();
			CHAR Drive	[MAX_PATH];
			CHAR Dir	[MAX_PATH];
			CHAR FName	[MAX_PATH];
			CHAR Ext	[MAX_PATH];
			_splitpath_s(szFileName, Drive, Dir, FName, Ext);
			string TexName = FName;
			string ext = Ext;
			if (ext == ".tga" || ".TGA")
			{
				ext.clear();
				ext = ".dds";
			}
			TexName += ext;
			return TexName;
		}
	}
	return string("");
}

bool AFbxLoader::Init()
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager, "");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");

	return true;
}

bool AFbxLoader::Render()
{
	return true;
}

bool AFbxLoader::Frame()
{
	return true;
}

bool AFbxLoader::Release()
{
	for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
	{
		m_ObjList[iObj]->Release();
	}
	m_pFbxScene->Destroy();
	m_pFbxImporter->Destroy();
	m_pFbxManager->Destroy();
	return true;
}

