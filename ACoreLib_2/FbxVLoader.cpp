#include "FbxImporter.h"

void AFbxImporter::ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVset,
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

FbxColor AFbxImporter::ReadColor(const FbxMesh* pMesh, DWORD dwVertexColorCount, FbxLayerElementVertexColor* pVertexColorSet,
	DWORD dwDCCIndex, DWORD dwVertexIndex)
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


FbxVector4	AFbxImporter::ReadNormal(const FbxMesh* pMesh, int ictrPointIndex, int iVcounter)
{
	//Mesh의 노말이 존재하면 노말획득
	if (pMesh->GetElementNormalCount() < 1) {}
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


//정점 노말을 읽는 함수
FbxVector4	AFbxImporter::ReadNormal(const FbxMesh* pMesh, DWORD dwVertexNormalCount, FbxLayerElementNormal* pVertexNormalSets,
	int ictrPointIndex, int iVIndex)
{
	FbxVector4 Value(0, 0, 0);
	if (dwVertexNormalCount < 1) { return Value; }
	int iVNormalLayer = pMesh->GetElementNormalCount();

	//Get Normal
	const FbxGeometryElementNormal* pVNormal = pMesh->GetElementNormal(0);
	
	//Create Vecter(for Save Normal)
	switch (pVertexNormalSets->GetMappingMode()) //Mapping Mode
	{
	case FbxGeometryElement::eByControlPoint:
	{
		//Control Point Mapping
		switch (pVertexNormalSets->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			Value[0] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(ictrPointIndex).mData[0]);
			Value[1] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(ictrPointIndex).mData[1]);
			Value[2] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(ictrPointIndex).mData[2]);
		}break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = pVertexNormalSets->GetIndexArray().GetAt(ictrPointIndex);

			//Get Index
			Value[0] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(index).mData[0]);
			Value[1] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(index).mData[1]);
			Value[2] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(index).mData[2]);
		}break;
		}break;
	}break;
	//PolygonVertex
	case FbxGeometryElement::eByPolygonVertex:
	{
		//Control Point Mapping
		switch (pVNormal->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			Value[0] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(iVIndex).mData[0]);
			Value[1] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(iVIndex).mData[1]);
			Value[2] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(iVIndex).mData[2]);
		}break;
		case FbxGeometryElement::eIndexToDirect:
		{
			int index = pVertexNormalSets->GetIndexArray().GetAt(iVIndex);

			//Get Index
			Value[0] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(index).mData[0]);
			Value[1] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(index).mData[1]);
			Value[2] = static_cast<float>(pVertexNormalSets->GetDirectArray().GetAt(index).mData[2]);
		}break;
		}
	}break;
	}
	return Value;
}

FbxVector4	AFbxImporter::ReadTangent(const FbxMesh* pMesh, DWORD dwVertexTangentCount, FbxGeometryElementTangent* pVertexTangentSets,
	DWORD dwDCCIndex, DWORD dwVertexIndex)
{
	FbxVector4 tanret(0, 0, 0);
	if (dwVertexTangentCount < 1) { return tanret; }
	int dwVTangentCountLayer = pMesh->GetElementTangentCount();
	//Get Normal
	const FbxGeometryElementTangent* pVTangent = pMesh->GetElementTangent(0);

	if (pVTangent != nullptr)
	{
		//Create Vecter(for Save Normal)
		switch (pVTangent->GetMappingMode()) //Mapping Mode
		{
		case FbxGeometryElement::eByControlPoint:
		{
			//Control Point Mapping
			switch (pVTangent->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				tanret[0] = static_cast<float>(pVTangent->GetDirectArray().GetAt(dwDCCIndex).mData[0]);
				tanret[1] = static_cast<float>(pVTangent->GetDirectArray().GetAt(dwDCCIndex).mData[1]);
				tanret[2] = static_cast<float>(pVTangent->GetDirectArray().GetAt(dwDCCIndex).mData[2]);
			}break;
			case FbxGeometryElement::eIndexToDirect:
			{
				int index = pVTangent->GetIndexArray().GetAt(dwDCCIndex);

				//Get Index
				tanret[0] = static_cast<float>(pVTangent->GetDirectArray().GetAt(index).mData[0]);
				tanret[1] = static_cast<float>(pVTangent->GetDirectArray().GetAt(index).mData[1]);
				tanret[2] = static_cast<float>(pVTangent->GetDirectArray().GetAt(index).mData[2]);
			}break;
			default:
			{
				assert(0);
			}break;
			}break;
		}
		//PolygonVertex
		case FbxGeometryElement::eByPolygonVertex:
		{
			//Control Point Mapping
			switch (pVTangent->GetReferenceMode())
			{
			case FbxGeometryElement::eDirect:
			{
				int iTIndex = dwVertexIndex;
				tanret[0] = static_cast<float>(pVTangent->GetDirectArray().GetAt(iTIndex).mData[0]);
				tanret[1] = static_cast<float>(pVTangent->GetDirectArray().GetAt(iTIndex).mData[1]);
				tanret[2] = static_cast<float>(pVTangent->GetDirectArray().GetAt(iTIndex).mData[2]);
			}break;
			case FbxGeometryElement::eIndexToDirect:
			{

				int iTIndex = pVTangent->GetIndexArray().GetAt(dwVertexIndex);
				//Get Index
				tanret[0] = static_cast<float>(pVTangent->GetDirectArray().GetAt(iTIndex).mData[0]);
				tanret[1] = static_cast<float>(pVTangent->GetDirectArray().GetAt(iTIndex).mData[1]);
				tanret[2] = static_cast<float>(pVTangent->GetDirectArray().GetAt(iTIndex).mData[2]);
			}break;
			default:
			{
				assert(0);
			}
			}
		}
		}
	}
	return tanret;
}


int	 AFbxImporter::GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMtrlSetList)
{
	// SubMtrl 매핑방식
	// eNone, eBycontrolPoint(제어점), eByPolygonVertex, eByPolygon(폴리곤마다), eAllSame (전체표면에 1개의 매핑좌표 존재)
	int iSubMtrl = 0;
	if (pMtrlSetList != nullptr)
	{
		switch (pMtrlSetList->GetMappingMode())
		{
		case FbxLayerElement::eByPolygon:
		{
			//매빙 정보가 배열에 저장되는 방식
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
		default:
		{}break;
		}
	}
	return iSubMtrl;
}