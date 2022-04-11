#include "FbxImporter.h"


//-------------------------  AFbxImporter  -----------------------------------


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
		m_pTreeList.push_back(pFbx);
		m_pFbxNodeMap.insert(make_pair(pNode, pFbx->m_iIndex));
		m_pFbxModelMap.insert(make_pair(pFbx->m_csName, pFbx));
	}

	//Camera, Light, Mesh, Shape, Animation �۾� �� Mesh�� ������ �۾��� �Ѵ�.
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

	//������� (�ʱ� ���� ��ġ�� ��ȯ�� �� ����Ѵ�)
	FbxAMatrix geom;
	FbxVector4 trans = pObj->m_pFbxNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 rot = pObj->m_pFbxNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scale = pObj->m_pFbxNode->GetGeometricScaling(FbxNode::eSourcePivot);
	geom.SetT(trans);		geom.SetR(rot);		geom.SetS(scale);

	FbxAMatrix normalMatrix = geom;
	normalMatrix = normalMatrix.Inverse();
	normalMatrix = normalMatrix.Transpose();

	//Layer ����. (�������� ���� ������)
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

	//1���� ������Ʈ�� �������� �ؽ��ĸ� ����Ѵ�. ������ �ؽ����� �̸��� ��� �����Ѵ�.
	//� ���̽�(������)�� � �ؽ�ó�� ����ϴ���?. ���� �ؽ�ó�� ����ϴ� ������鳢�� �����Ѵ�.

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

	//�ﰢ��, �簢��
	int iBasePolyIndex = 0;
	int iNumPolyCount = pFbxMesh->GetPolygonCount();
	FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
	int iNumFace = 0;
	for (int iPoly = 0; iPoly < iNumPolyCount; iPoly++)
	{
		int iPolySize = pFbxMesh->GetPolygonSize(iPoly);

		//���̽� ������ ����������� -2 (����-2) �������� �簢���� ��쵵 ������ 
		//������ ���� �����Ͽ� ����ϱ� ������ ��������2���� ����� ��(?)
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

				//Color�� ����
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

				//normal��
				FbxVector4 normal = ReadNormal(pFbxMesh, iCornerIndex[iIndex], iBasePolyIndex + iVertexIndex[iIndex]);
				normal = normalMatrix.MultT(normal);
				tVertex.n.x = normal.mData[0];
				tVertex.n.y = normal.mData[2];	//z
				tVertex.n.z = normal.mData[1];	//y

				AVertexIW iwVertex;
				if (pObj->m_bSkinned)
				{
					AWeight* pWeight = &pObj->m_WeightList[iCornerIndex[iIndex]];
					for (int i = 0; i < 4; i++)
					{
						iwVertex.i[i] = pWeight->Index[i];
						iwVertex.w[i] = pWeight->Weight[i];
					}
				}
				else
				{
					//��Ű�� ���� �Ϲ� ������Ʈ�� ������ ��Ű��ȭ �۾��Ͽ� ��������ϵ��� �Ѵ�.
					iwVertex.i[0] = pObj->m_iIndex;
					iwVertex.w[0] = 1.0f;
				}

				//pObj->m_pSubVertexList[iSubMtrl].push_back(tVertex); //36
				pObj->m_pSubVertexList[iSubMtrl].push_back(tVertex);
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
	// ������ ������ �����Ѵ�.
	int iVertexCount = pFbxMesh->GetControlPointsCount();
	pObject->m_WeightList.resize(iVertexCount);

	for (int dwDeformerIndex = 0; dwDeformerIndex < iDeformerCount; dwDeformerIndex++)
	{
		auto pSkin = reinterpret_cast<FbxSkin*>(pFbxMesh->GetDeformer(dwDeformerIndex, FbxDeformer::eSkin));
		DWORD dwClusterCount = pSkin->GetClusterCount();

		// dwClusterCount�� ����� ��ü ������ ������ ��
		for (int dwClusterIndex = 0; dwClusterIndex < dwClusterCount; dwClusterIndex++)
		{
			auto pCluster = pSkin->GetCluster(dwClusterIndex);
			////
			FbxAMatrix matXBindPose;
			FbxAMatrix matReferenceGlobalInitPosition;
			pCluster->GetTransformLinkMatrix(matXBindPose);
			pCluster->GetTransformMatrix(matReferenceGlobalInitPosition);
			FbxMatrix matBindPose = matReferenceGlobalInitPosition.Inverse() * matXBindPose;

			TMatrix matInvBindPos = DxConvertMatrix(ConvertMatrix(matBindPose));
			matInvBindPos = matInvBindPos.Invert();
			int  iBoneIndex = m_pFbxNodeMap.find(pCluster->GetLink())->second;
			std::wstring name = m_pTreeList[iBoneIndex]->m_csName;
			pObject->m_dxMatrixBindPoseMap.insert(make_pair(name, matInvBindPos));

			int  dwClusterSize = pCluster->GetControlPointIndicesCount();
			// ������ �޴� �������� �ε���
			int* pIndices = pCluster->GetControlPointIndices();
			double* pWeights = pCluster->GetControlPointWeights();
			// iBoneIndex�� ������ �޴� �������� dwClusterSize�� �ִ�.
			for (int i = 0; i < dwClusterSize; i++)
			{
				// n�� ����(pIndices[i])�� iBoneIndex�� ��Ŀ� 
				// pWeights[i]�� ����ġ�� ����Ǿ���.
				int iVertexIndex = pIndices[i];
				float fWeight = pWeights[i];
				pObject->m_WeightList[iVertexIndex].InsertWeight(iBoneIndex, fWeight);
			}
		}
	}
	return true;
}



//-------------------------  AFbxImporter  -----------------------------------

//Animation �߰�
TMatrix	AFbxImporter::DxConvertMatrix(TMatrix m)
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

TMatrix	AFbxImporter::ConvertMatrix(FbxMatrix& m)
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

TMatrix	AFbxImporter::ConvertAMatrix(FbxAMatrix& m)
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

void AFbxImporter::ParseAnimation()
{
	FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
	FbxAnimStack* pStack = m_pFbxScene->GetSrcObject<FbxAnimStack>(0);
	if (pStack = nullptr) return;

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

	//1�ʿ� 30 Frame, 1 Frame = 160 Tick, 50Frame���� ������.
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

			//��� SRT�� �����Ͽ� ��� ����
			T::D3DXMatrixDecompose(&aTrack.s, &aTrack.r, &aTrack.t, &aTrack.matTrack);
			m_pTreeList[iObj]->m_AnimTrack.push_back(aTrack);
		}
	}
}


//-------------------------  AFbxImporter ������ �⺻�Լ���  -----------------------------------

bool AFbxImporter::Init()
{
	m_pFbxManager = FbxManager::Create();
	m_pFbxImporter = FbxImporter::Create(m_pFbxManager,"");
	m_pFbxScene = FbxScene::Create(m_pFbxManager, "");

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