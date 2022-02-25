#include "Sprite.h"

void ASprite::SetRectSouceArray(RECT rt)
{
	m_rtArray.push_back(rt);
}
bool ASprite::Init() { return true; }
bool ASprite::Frame() { return true; }
bool ASprite::Render()
{
	ADxObject::Render();
	return true;
}
bool ASprite::Release() { return true; }
bool ASprite::Load(ID3D11Device* pd3dDevice, wstring filename) { return true; }

ASprite* ASpriteMgr::Load(wstring filename)
{
	TCHAR pBuffer[256] = { 0, };
	TCHAR pTemp[256] = { 0, };

	int iNumSprite = 0;
	float fAnimTimer;
	FILE* fp_src;
	_wfopen_s(&fp_src, filename.c_str(), _T("rt"));
	if (fp_src == NULL) return nullptr;

	_fgetts(pBuffer, _countof(pBuffer), fp_src);
	_stscanf_s(pBuffer, _T("%s %d %f"), pTemp, (unsigned int)_countof(pTemp), &iNumSprite);

	for (int iCnt = 0; iCnt < iNumSprite; iCnt++)
	{
		TCHAR name[256] = { 0, };
		ASprite* pSprite = new ASprite;
		int iNumFrame = 0;
		_fgetts(pBuffer, _countof(pBuffer), fp_src);
		_stscanf_s(pBuffer, _T("%s %d %f"), name, (unsigned int)_countof(name), &iNumFrame, &pSprite->m_fAnimTime);

		RECT rt;
		for (int iFrame = 0; iFrame < iNumFrame; iFrame++)
		{
			_fgetts(pBuffer, _countof(pBuffer), fp_src);
			_stscanf_s(pBuffer, _T("%s %d %d %d %d"), pTemp, (unsigned int)_countof(pTemp), &rt.left, &rt.top, &rt.right, &rt.bottom);
			pSprite->m_rtArray.push_back(rt);
		}
		pSprite->m_csName = name;
		m_list.insert(make_pair(pSprite->m_csName, pSprite));
		m_iIndex++;
	}
	fclose(fp_src);
	return nullptr;
}
