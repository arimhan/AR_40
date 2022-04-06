#include "FbxLoader.h"


//FbxVLoader.cpp
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

void AFbxLoader::ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVset,
	int iVIndex, int iUVIndex, FbxVector2& uv)
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

FbxColor AFbxLoader::ReadColor(const FbxMesh* pMesh, DWORD dwVertexColorCount,
	FbxLayerElementVertexColor* pVertexColorSet, DWORD dwDCCIndex, DWORD dwVertexIndex)
{
	FbxColor Value(1, 1, 1, 1);

	if (dwVertexColorCount > 0 && pVertexColorSet != NULL)
	{
		switch (pVertexColorSet->GetMappingMode())
		{
		case FbxLayerElement::eByControlPoint:

			switch (pVertexColorSet->GetReferenceMode())
			{
			case FbxLayerElement::eDirect:
			{
				Value = pVertexColorSet->GetDirectArray().GetAt(dwDCCIndex);
			}break;

			case FbxLayerElement::eIndexToDirect:
			{
				int iColorIndex = pVertexColorSet->GetIndexArray().GetAt(dwDCCIndex);
				Value = pVertexColorSet->GetDirectArray().GetAt(iColorIndex);
			}break;
			}
		case FbxLayerElement::eByPolygonVertex:
			switch (pVertexColorSet->GetReferenceMode())
			{
			case FbxLayerElement::eDirect:
			{
				int iColorIndex = dwVertexIndex;
				Value = pVertexColorSet->GetDirectArray().GetAt(iColorIndex);
			}break;
			case FbxLayerElement::eIndexToDirect:
			{
				int iColorIndex = pVertexColorSet->GetIndexArray().GetAt(dwVertexIndex);
				Value = pVertexColorSet->GetDirectArray().GetAt(iColorIndex);
			}break;
			}
			break;
		}
	}
	return Value;
}
FbxVector4 AFbxLoader::ReadNormal(const FbxMesh* pMesh, int ictrPointIndex, int iVcounter) 
{
	//Mesh의 노말이 존재하면 노말획득
	if(pMesh->GetElementNormalCount() < 1) {}
	const FbxGeometryElementNormal* pVertexNormal = pMesh->GetElementNormal(0);
	FbxVector4 fvresult;
	//노말 벡터를 저장할 벡터 세팅
	switch (pVertexNormal->GetMappingMode()) //매핑 모드
	{
		//제어점마다 1개의 매핑 좌표가 있다.
		case FbxGeometryElement::eByControlPoint:
		{
			// 컨트롤 포인트 매핑
			switch (pVertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				fvresult[0] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(ictrPointIndex).mData[0]);
				fvresult[1] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(ictrPointIndex).mData[1]);
				fvresult[2] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(ictrPointIndex).mData[2]);
			}break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int index = pVertexNormal->GetIndexArray().GetAt(ictrPointIndex);
				//인덱스를 얻어온다
				fvresult[0] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(index).mData[0]);
				fvresult[1] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(index).mData[1]);
				fvresult[2] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(index).mData[2]);
			}break;
			}
		}break;

		//정점마다 1개의 매핑 좌표 존재
		case FbxGeometryElement::eByPolygonVertex:
		{
			switch (pVertexNormal->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				fvresult[0] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(ictrPointIndex).mData[0]);
				fvresult[1] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(ictrPointIndex).mData[1]);
				fvresult[2] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(ictrPointIndex).mData[2]);
			}break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int index = pVertexNormal->GetIndexArray().GetAt(ictrPointIndex);
				//인덱스를 얻어온다
				fvresult[0] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(index).mData[0]);
				fvresult[1] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(index).mData[1]);
				fvresult[2] = static_cast<float>(pVertexNormal->GetDirectArray().GetAt(index).mData[2]);
			}break;
			}
		}break;
	}
	return fvresult;
}

int	 AFbxLoader::GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMtrlSetList) 
{
	// SubMtrl
	int iSubMtrl = 0;
	if (pMtrlSetList != nullptr)
	{
		switch (pMtrlSetList->GetMappingMode())
		{
		case FbxLayerElement::eByPolygon:
		{
			switch (pMtrlSetList->GetReferenceMode())
			{
			case FbxLayerElement::eIndex:
			{
				iSubMtrl = iPoly;
			}break;
			case FbxLayerElement::eIndexToDirect:
			{
				iSubMtrl = pMtrlSetList->GetIndexArray().GetAt(iPoly);
			}break;
			}
		}
		default :
		{}break;
		}
	}
	return iSubMtrl;
}