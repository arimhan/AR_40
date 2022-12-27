#include "FbxImporter.h"


//-------------------  AFbxImporter  Load, Mesh, Skinning-------------------------


bool AFbxImporter::Load(ID3D11Device* pd3dDevice, wstring filename) 
{
	if (Load(to_wm(filename).c_str()))
	{
		CreateConstantBuffer(pd3dDevice);
		AShader* pVShader = I_Shader.CreateVertexShader(pd3dDevice, L"../../data/shader/Character.hlsl", "VS");
		AShader* pPShader = I_Shader.CreatePixelShader(pd3dDevice, L"../../data/shader/Character.hlsl", "PS");

		for (int iObj = 0; iObj < m_pDrawList.size(); iObj++)
		{
			m_pDrawList[iObj]->Init();
			m_pDrawList[iObj]->m_pVShader = pVShader;
			m_pDrawList[iObj]->m_pPShader = pPShader;
			if(!m_pDrawList[iObj]->Create(pd3dDevice, m_pContext)) 
			{
				return false;
			}
		}
	}

	return true;
}

bool AFbxImporter::Load(string filename)
{
	Init();

	bool bRet = m_pFbxImporter->Initialize(filename.c_str());
	bRet = m_pFbxImporter->Import(m_pFbxScene);
	m_pRootNode = m_pFbxScene->GetRootNode();
	PreProcess(m_pRootNode, nullptr);
	ParseAnimation();

	for (int iObj = 0; iObj < m_pDrawList.size(); iObj++)
	{
		ParseMesh(m_pDrawList[iObj]);
	}

	Release();

	return true;
}


void AFbxImporter::PreProcess(FbxNode* pNode, AFbxModel* pParent) 
{
	AFbxModel* pFbx = nullptr;
	if (pNode != nullptr)
	{
		pFbx = new AFbxModel;
		pFbx->m_pFbxParent = pNode->GetParent();
		pFbx->m_pFbxNode = pNode;
		pFbx->m_csName = to_mw(pNode->GetName());
		pFbx->m_pParentObj = pParent;
		pFbx->m_iIndex = m_pTreeList.size();	//index를 TreeList만큼 부여
		m_pTreeList.push_back(pFbx);
		m_pFbxNodeMap.insert(make_pair(pNode, pFbx->m_iIndex));
		m_pFbxModelMap.insert(make_pair(pFbx->m_csName, pFbx));
	}

	//Camera, Light, Mesh, Shape, Animation 작업 시 Mesh를 얻어오는 작업을 한다.
	FbxMesh* pMesh = pNode->GetMesh();
	if (pMesh)
	{
		m_pDrawList.push_back(pFbx);
	}
	int iNumChild = pNode->GetChildCount();
	for (int iNode = 0; iNode < iNumChild; iNode++)
	{
		FbxNode* pChild = pNode->GetChild(iNode);
		PreProcess(pChild, pFbx);
	}
}

void AFbxImporter::ParseMesh(AFbxModel* pObj) 
{
	FbxMesh* pFbxMesh = pObj->m_pFbxNode->GetMesh();

	pObj->m_bSkinned = ParseMeshSkinning(pFbxMesh, pObj); // m_bSkinned 불러오기
	
	//기하행렬 (초기 정점 위치를 변환할 때 사용한다)
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
	vector<FbxLayerElementTangent*> pVertexTangentSet;
	vector<FbxLayerElementMaterial*> pMaterialSet;
	vector<FbxLayerElementNormal*> pVertexNormalSets;

	int iLayerCount = pFbxMesh->GetLayerCount();
	bool bFlag = false;

	if (iLayerCount == 0 || pFbxMesh->GetLayer(0)->GetNormals() == nullptr)
	{
		pFbxMesh->InitNormals();
#if (FBXSDK_VERSION_MAJOR >= 2015)
		pFbxMesh->GenerateNormals();
#else
		pFbxMesh->ComputeVertexNormals();
#endif
	}

	if (pFbxMesh->GetLayer(0)->GetNormals() == nullptr)
	{
		bFlag = pFbxMesh->GenerateTangentsData(0);
	}

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
		if (pFbxLayer->GetTangents() != nullptr)
		{
			pVertexTangentSet.push_back(pFbxLayer->GetTangents());
		}
		if (pFbxLayer->GetNormals() != nullptr)
		{
			pVertexNormalSets.push_back(pFbxLayer->GetNormals());
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
		pObj->m_pSubIWVertexList.resize(iNumMtrl);
	}
	else
	{
		pObj->m_pSubVertexList.resize(1);
		pObj->m_pSubIWVertexList.resize(1);
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
			iCornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, 0);
			iCornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, iFace+2);
			iCornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, iFace+1);

			//UV
			int u[3];
			u[0] = pFbxMesh->GetTextureUVIndex(iPoly, 0);
			u[1] = pFbxMesh->GetTextureUVIndex(iPoly, iFace + 2);
			u[2] = pFbxMesh->GetTextureUVIndex(iPoly, iFace + 1);

			for (int iIndex = 0; iIndex < 3; iIndex++)
			{
				int DCCIndex = iCornerIndex[iIndex];
				AVertex aVertex;
				//max (x,z,y) -> dx (x,y,z)
				//FbxVector4 v = pVertexPositions[iCornerIndex[iIndex]];
				//v = geom.MultT(v);
				auto v = geom.MultT(pVertexPositions[DCCIndex]);

				aVertex.p.x = v.mData[0];
				aVertex.p.y = v.mData[2]; //y,z값 바꿀것
				aVertex.p.z = v.mData[1];

				
				if (pVertexUvSet.size() > 0)
				{
					FbxLayerElementUV* pUVset = pVertexUvSet[0];
					FbxVector2 uv;
					ReadTextureCoord(pFbxMesh, pUVset, DCCIndex, u[iIndex], uv);
					aVertex.t.x = uv.mData[0];
					aVertex.t.y = 1.0f - uv.mData[1];
				}

				//Color값 세팅
				FbxColor color = FbxColor(1, 1, 1, 1);
				if (pVertexColorSet.size() > 0)
				{
					color = ReadColor(pFbxMesh, pVertexColorSet.size(), pVertexColorSet[0],
						DCCIndex, iBasePolyIndex + iVertexIndex[iIndex]);
				}
				aVertex.c.x = color.mRed;
				aVertex.c.y = color.mGreen;
				aVertex.c.z = color.mBlue;
				aVertex.c.w = pObj->m_iIndex;//1;

				//normal값
				if (pVertexNormalSets.size() <= 0)
				{
					FbxVector4 Normal = ReadNormal(pFbxMesh, DCCIndex, iBasePolyIndex + iVertexIndex[iIndex]);
					Normal = normalMatrix.MultT(Normal);
					aVertex.n.x = Normal.mData[0];
					aVertex.n.y = Normal.mData[2];	//z
					aVertex.n.z = Normal.mData[1];	//y
					D3DXVec3Normalize(&aVertex.n, &aVertex.n);
				}
				else //Noraml이 있으면 Store vertex normal
				{

					FbxVector4 FinalNormal = ReadNormal(pFbxMesh, pVertexNormalSets.size(), pVertexNormalSets[0],
						DCCIndex, iBasePolyIndex + iVertexIndex[iIndex]);
					FinalNormal = normalMatrix.MultT(FinalNormal);
					FinalNormal.Normalize();
					aVertex.n.x = FinalNormal.mData[0];
					aVertex.n.y = FinalNormal.mData[2];	//z
					aVertex.n.z = FinalNormal.mData[1];	//y
					D3DXVec3Normalize(&aVertex.n, &aVertex.n);
				}


				AVertexIW iwVertex;
				if (pObj->m_bSkinned)
				{
					AWeight* pWeight = &pObj->m_WeightList[DCCIndex];
					for (int i = 0; i < 4; i++)
					{
						iwVertex.i[i] = pWeight->Index[i];
						iwVertex.w[i] = pWeight->Weight[i];
					}
				}
				else
				{
					//스키닝 없는 일반 오브젝트를 강제로 스키닝화 작업하여 재생가능하도록 한다.
					iwVertex.i[0] = pObj->m_iIndex;
					iwVertex.w[0] = 1.0f;
				}

				//pObj->m_pSubVertexList[iSubMtrl].push_back(tVertex); //36
				pObj->m_pSubVertexList[iSubMtrl].push_back(aVertex);
				pObj->m_pSubIWVertexList[iSubMtrl].push_back(iwVertex);
			}
		}
		iBasePolyIndex += iPolySize;
	}
}

string AFbxImporter::ParseMaterial(FbxSurfaceMaterial* pMtrl) 
{
	string name = pMtrl->GetName();
	auto Property = pMtrl->FindProperty(FbxSurfaceMaterial::sDiffuse);

	if (Property.IsValid())
	{
		const FbxFileTexture* pTex = Property.GetSrcObject<FbxFileTexture>(0);
		if (pTex != nullptr)
		{
			const CHAR* szFileName = pTex->GetFileName();
			CHAR Drive[MAX_PATH];
			CHAR Dir[MAX_PATH];
			CHAR FName[MAX_PATH];
			CHAR Ext[MAX_PATH];
			_splitpath_s(szFileName, Drive, Dir, FName, Ext);
			string TexName = FName;
			string ext = Ext;
			if (ext == ".tga" || ext == ".TGA")
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

bool AFbxImporter::ParseMeshSkinning(FbxMesh* pFbxMesh, AFbxModel* pObject)
{
	int iDeformerCount = pFbxMesh->GetDeformerCount(FbxDeformer::eSkin);
	if (iDeformerCount == 0)
	{
		return false;
	}
	// 정점의 개수와 동일한다.
	int iVertexCount = pFbxMesh->GetControlPointsCount();
	pObject->m_WeightList.resize(iVertexCount);

	for (int dwDeformerIndex = 0; dwDeformerIndex < iDeformerCount; dwDeformerIndex++)
	{
		auto pSkin = reinterpret_cast<FbxSkin*>(pFbxMesh->GetDeformer(dwDeformerIndex, FbxDeformer::eSkin));
		DWORD dwClusterCount = pSkin->GetClusterCount();

		// dwClusterCount의 행렬이 전체 정점에 영향을 줌
		for (int dwClusterIndex = 0; dwClusterIndex < dwClusterCount; dwClusterIndex++)
		{
			auto pCluster = pSkin->GetCluster(dwClusterIndex);
			////
			FbxAMatrix matXBindPose;
			FbxAMatrix matReferenceGlobalInitPosition;
			pCluster->GetTransformLinkMatrix(matXBindPose);
			pCluster->GetTransformMatrix(matReferenceGlobalInitPosition);
			FbxMatrix matBindPose = matReferenceGlobalInitPosition.Inverse() * matXBindPose;

			A::AMatrix matInvBindPos = DxConvertMatrix(ConvertMatrix(matBindPose));
			matInvBindPos = matInvBindPos.Invert();
			int  iBoneIndex = m_pFbxNodeMap.find(pCluster->GetLink())->second;
			std::wstring name = m_pTreeList[iBoneIndex]->m_csName;
			pObject->m_dxMatrixBindPoseMap.insert(make_pair(name, matInvBindPos));

			int  dwClusterSize = pCluster->GetControlPointIndicesCount();
			// 영향을 받는 정점들의 인덱스
			int* pIndices = pCluster->GetControlPointIndices();
			double* pWeights = pCluster->GetControlPointWeights();
			// iBoneIndex의 영향을 받는 정점들이 dwClusterSize개 있다.
			for (int i = 0; i < dwClusterSize; i++)
			{
				// n번 정점(pIndices[i])은 iBoneIndex의 행렬에 
				// pWeights[i]의 가중치로 적용되었다.
				int iVertexIndex = pIndices[i];
				float fWeight = pWeights[i];
				pObject->m_WeightList[iVertexIndex].InsertWeight(iBoneIndex, fWeight);
			}
		}
	}
	return true;
}



//-------------------------  Animation  -----------------------------------

//Animation 추가
A::AMatrix	AFbxImporter::DxConvertMatrix(A::AMatrix m)
{
	A::AMatrix mat;
	mat._11 = m._11;	mat._12 = m._13;	mat._13 = m._12;
	mat._21 = m._31;	mat._22 = m._33;	mat._23 = m._32;
	mat._31 = m._21;	mat._32 = m._23;	mat._33 = m._22;
	mat._41 = m._41;	mat._42 = m._43;	mat._43 = m._42;

	mat._14 = mat._24 = mat._34 = 0.0f;

	mat._44 = 1.0f;
	return mat;
}

A::AMatrix	AFbxImporter::ConvertMatrix(FbxMatrix& m)
{
	A::AMatrix mat;
	float* pMatArray = reinterpret_cast<float*>(&mat);
	double* pSrcArray = reinterpret_cast<double*>(&m);

	for (int i = 0; i < 16; i++)
	{
		pMatArray[i] = pSrcArray[i];
	}
	return mat;
}

A::AMatrix	AFbxImporter::ConvertAMatrix(FbxAMatrix& m)
{
	A::AMatrix mat;
	float* pMatArray = reinterpret_cast<float*>(&mat);
	double* pSrcArray = reinterpret_cast<double*>(&m);

	for (int i = 0; i < 16; i++)
	{
		pMatArray[i] = pSrcArray[i];
	}
	return mat;
}

void AFbxImporter::ParseAnimation()
{
	FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
	FbxAnimStack* pStack = m_pFbxScene->GetSrcObject<FbxAnimStack>(0);
	if (pStack == nullptr) return;

	FbxString TakeName = pStack->GetName();
	FbxTakeInfo* pTakeInfo = m_pFbxScene->GetTakeInfo(TakeName);
	FbxTimeSpan LocalTimeSpan = pTakeInfo->mLocalTimeSpan;
	FbxTime		Start =		LocalTimeSpan.GetStart();
	FbxTime		End =		LocalTimeSpan.GetStop();
	FbxTime		Duration =	LocalTimeSpan.GetDuration();

	FbxTime::EMode TimeMode = FbxTime::GetGlobalTimeMode();
	FbxLongLong s = Start.GetFrameCount(TimeMode);
	FbxLongLong n = End.GetFrameCount(TimeMode);
	m_Scene.iStart = s;
	m_Scene.iEnd = n;
	m_Scene.iFrameSpeed = 30; //30Frame

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

			//행렬 SRT를 분해하여 요소 전달
			A::D3DXMatrixDecompose(&aTrack.s, &aTrack.r, &aTrack.t, &aTrack.matTrack);
			m_pTreeList[iObj]->m_AnimTrack.push_back(aTrack);
		}
	}
}


//-------------------------  AFbxImporter 재정의 기본함수들  -----------------------------------

bool AFbxImporter::Init()
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager,"");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");

	FbxAxisSystem m_SceneAxisSystem = m_pFbxScene->GetGlobalSettings().GetAxisSystem();
	FbxAxisSystem::MayaZUp.ConvertScene(m_pFbxScene);
	m_SceneAxisSystem = m_pFbxScene->GetGlobalSettings().GetAxisSystem();

	FbxSystemUnit m_SceneSystemUnit = m_pFbxScene->GetGlobalSettings().GetSystemUnit();
	if (m_SceneSystemUnit.GetScaleFactor() != 1.0f)
	{
		FbxSystemUnit::cm.ConvertScene(m_pFbxScene);
	}

	return true;
}
bool AFbxImporter::Render() { return true; }

bool AFbxImporter::Frame() { return true; }

bool AFbxImporter::Release()
{
	if (m_pBoneCB) m_pBoneCB->Release();


	for (int iObj = 0; iObj < m_pDrawList.size(); iObj++)
	{
		m_pDrawList[iObj]->Release();
	}

	if (m_pFbxScene)m_pFbxScene			->Destroy();
	if (m_pFbxImporter)m_pFbxImporter	->Destroy();
	if (m_pFbxManager)m_pFbxManager		->Destroy();

	m_pBoneCB =			nullptr;
	m_pFbxScene =		nullptr;
	m_pFbxImporter =	nullptr;
	m_pFbxManager =		nullptr;

	return true;

}
bool AFbxImporter::CreateConstantBuffer(ID3D11Device* pDevice)
{
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(ABoneWorld);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (FAILED(hr = pDevice->CreateBuffer(&bd, NULL,
		&m_pBoneCB)))
	{
		return false;
	}
	return true;
}