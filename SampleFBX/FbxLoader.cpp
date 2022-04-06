#include "FbxLoader.h"


bool AFbxLoader::Load(string filename)
{
	bool bRet = m_pFbxImporter->Initialize(filename.c_str());
	bRet = m_pFbxImporter->Import(m_pFbxScene);
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode, nullptr);
	ParseAnimation();

	for (int iObj = 0; iObj < m_pDrawList.size(); iObj++)
	{
		ParseMesh(m_pDrawList[iObj]);
	}
	return true;
}

void AFbxLoader::PreProcess(FbxNode* pNode, AFbxObject* pParent)
{
	AFbxObject* pfbx = nullptr;
	if (pNode != nullptr)
	{
		pfbx = new AFbxObject;
		pfbx->m_pFbxParent = pNode->GetParent();
		pfbx->m_pFbxNode = pNode;
		pfbx->m_csName = to_mw(pNode->GetName());
		pfbx->m_pParentObj = pParent;
		m_pTreeList.push_back(pfbx);
	}

	//Camera, Light, Mesh, Shape, Animation 작업 시 Mesh를 얻어오는 작업을 한다.
	FbxMesh* pMesh = pNode->GetMesh();
	if (pMesh)
	{
		m_pDrawList.push_back(pfbx);
	}
	int iNumChild = pNode->GetChildCount();
	for (int iNode = 0; iNode < iNumChild; iNode++)
	{
		FbxNode* pChild = pNode->GetChild(iNode);
		PreProcess(pChild, pfbx);
	}
}

void AFbxLoader::ParseMesh(AFbxObject* pObj)
{
	FbxMesh* pFbxMesh = pObj->m_pFbxNode->GetMesh();
	FbxAMatrix geom;
	FbxVector4 trans = pObj->m_pFbxNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 rot = pObj->m_pFbxNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scale = pObj->m_pFbxNode->GetGeometricScaling(FbxNode::eSourcePivot);
	geom.SetT(trans);		geom.SetR(rot);		geom.SetS(scale);

	FbxAMatrix normalMatrix = geom;
	normalMatrix = normalMatrix.Inverse();
	normalMatrix = normalMatrix.Transpose();

	//Layer 개념. (여러번에 걸쳐 랜더링)
	vector<FbxLayerElementUV*> pVertexUvSet;
	vector<FbxLayerElementVertexColor*> pVertexColorSet;
	vector<FbxLayerElementMaterial*> pMaterialSet;

	int iLayerCount = pFbxMesh->GetLayerCount();
	for (int iLayer = 0; iLayer < iLayerCount; iLayer++)
	{
		FbxLayer* pFbxLayer = pFbxMesh->GetLayer(iLayer);
		if (pFbxLayer->GetUVs() != nullptr)
		{
			pVertexUvSet.push_back(pFbxLayer->GetUVs());
		}
		if (pFbxLayer->GetVertexColors() != nullptr)
		{
			pVertexColorSet.push_back(pFbxLayer->GetVertexColors());
		}
		if (pFbxLayer->GetMaterials() != nullptr)
		{
			pMaterialSet.push_back(pFbxLayer->GetMaterials());
		}
	}

	//1개의 오브젝트가 여러장의 텍스쳐를 사용한다. 각각의 텍스쳐의 이름을 얻고 저장한다.
	//어떤 페이스(폴리곤)가 어떤 텍스처를 사용하는지?. 같은 텍스처를 사용하는 폴리곤들끼리 저장한다.
	
	int iNumMtrl = pObj->m_pFbxNode->GetMaterialCount();
	for (int iMtrl = 0; iMtrl < iNumMtrl; iMtrl++)
	{
		FbxSurfaceMaterial* pSurface = pObj->m_pFbxNode->GetMaterial(iMtrl);
		if (pSurface)
		{
			string TextureName = ParseMaterial(pSurface);
			wstring szTexFileName = L"../../data/fbx/";
			szTexFileName += to_mw(TextureName);
			pObj->m_szTexFileList.push_back(szTexFileName);
			pObj->m_pTextureList.push_back(I_Texture.Load(pObj->m_szTexFileList[iMtrl]));
		}
	}
	if (pObj->m_szTexFileList.size() > 0)
	{
		pObj->m_szTexFileName = pObj->m_szTexFileList[0];
	}
	if (iNumMtrl > 0)
	{
		pObj->m_pSubVertexList.resize(iNumMtrl);
	}
	else
	{
		pObj->m_pSubVertexList.resize(1);
	}

	//삼각형, 사각형
	int iBasePolyIndex = 0;
	int iNumPolyCount = pFbxMesh->GetPolygonCount();
	FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
	int iNumFace = 0;
	for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
	{
		int iPolySize = pFbxMesh->GetPolygonSize(iPoly);

		//페이스 갯수는 폴리곤사이즈 -2 (정점-2) 폴리곤은 사각형인 경우도 있으며 
		//공유된 정점 포함하여 계산하기 때문에 공유정점2개를 빼줘야 함(?)
		iNumFace = iPolySize - 2;


		int iSubMtrl = 0;
		if (iNumMtrl >= 1 && pMaterialSet[0] != nullptr)
		{
			iSubMtrl = GetSubMaterialIndex(iPoly, pMaterialSet[0]);
		}
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
				v = geom.MultT(v);
				tVertex.p.x = v.mData[0];
				tVertex.p.y = v.mData[2]; //y,z값 바꿀것
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

				//Color값 세팅
				FbxColor color = FbxColor(1, 1, 1, 1);
				if (pVertexColorSet.size() > 0)
				{
					color = ReadColor(pFbxMesh, pVertexColorSet.size(), pVertexColorSet[0], 
						iCornerIndex[iIndex], iBasePolyIndex + iVertexIndex[iIndex]);
				}
				tVertex.c.x = color.mRed;
				tVertex.c.y = color.mGreen;
				tVertex.c.z = color.mBlue;
				tVertex.c.w = 1;

				//normal값
				FbxVector4 normal = ReadNormal(pFbxMesh, iCornerIndex[iIndex], iBasePolyIndex + iVertexIndex[iIndex]);
				normal = normalMatrix.MultT(normal);
				tVertex.n.x = normal.mData[0];	
				tVertex.n.y = normal.mData[2];	//z
				tVertex.n.z = normal.mData[1];	//y

				pObj->m_pSubVertexList[iSubMtrl].push_back(tVertex); //36
			}
		}
		iBasePolyIndex += iPolySize;
	}
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
	for (int iObj = 0; iObj < m_pDrawList.size(); iObj++)
	{
		m_pDrawList[iObj]->Release();
	}
	m_pFbxScene->Destroy();
	m_pFbxImporter->Destroy();
	m_pFbxManager->Destroy();
	return true;
}



//Animation 추가
TMatrix	AFbxLoader::DxConvertMatrix(TMatrix m) 
{
	TMatrix mat;
	mat._11 = m._11;	mat._12 = m._13;	mat._13 = m._12;
	mat._21 = m._31;	mat._22 = m._33;	mat._23 = m._32;
	mat._31 = m._21;	mat._32 = m._23;	mat._33 = m._22;
	mat._41 = m._41;	mat._42 = m._43;	mat._43 = m._42;

	mat._14 = mat._24 = mat._34 = 0.0f;

	mat._44 = 1.0f;
	return mat;
}
TMatrix	AFbxLoader::ConvertMatrix(FbxMatrix& m) 
{
	TMatrix mat;
	float* pMatArray = reinterpret_cast<float*>(&mat);
	double* pSrcArray = reinterpret_cast<double*>(&m);

	for (int i = 0; i < 16; i++)
	{
		pMatArray[i] = pSrcArray[i];
	}
	return mat;
}
TMatrix	AFbxLoader::ConvertAMatrix(FbxAMatrix& m) 
{
	TMatrix mat;
	float* pMatArray = reinterpret_cast<float*>(&mat);
	double* pSrcArray = reinterpret_cast<double*>(&m);

	for (int i = 0; i < 16; i++)
	{
		pMatArray[i] = pSrcArray[i];
	}
	return mat;
}
void AFbxLoader::ParseAnimation() 
{
	FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
	FbxAnimStack* pStack = m_pFbxScene->GetSrcObject<FbxAnimStack>(0);
	FbxString TakeName = pStack->GetName();
	FbxTakeInfo* pTakeInfo = m_pFbxScene->GetTakeInfo(TakeName);

	FbxTimeSpan LocalTimeSpan = pTakeInfo->mLocalTimeSpan;
	FbxTime		Start		= LocalTimeSpan.GetStart();
	FbxTime		End			= LocalTimeSpan.GetStop();
	FbxTime		Duration	= LocalTimeSpan.GetDuration();

	FbxTime::EMode TimeMode = FbxTime::GetGlobalTimeMode();
	FbxLongLong s = Start.GetFrameCount(TimeMode);
	FbxLongLong n = End.GetFrameCount(TimeMode);

	//1초에 30 Frame, 1 Frame = 160 Tick, 50Frame으로 설정함.
	FbxTime time;
	ATrack aTrack;
	for (FbxLongLong t = s; t <= n; t++)
	{
		time.SetFrame(t, TimeMode);
		for (int iObj = 0; iObj < m_pTreeList.size(); iObj++)
		{
			FbxAMatrix matGlobal = m_pTreeList[iObj]->m_pFbxNode->EvaluateGlobalTransform(time);
			aTrack.iFrame = t;
			aTrack.matTrack = DxConvertMatrix(ConvertAMatrix(matGlobal));
			m_pTreeList[iObj]->m_AnimTrack.push_back(aTrack);
		}
	}
}
