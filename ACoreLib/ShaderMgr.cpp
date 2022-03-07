#include "ShaderMgr.h"

bool AShader::CreateVertexShader(ID3D11Device* pd3dDevice, wstring filename, string entry)
{
	//txt파일 생성 및 작성
		//쉐이더 컴파일 -> 오브젝트 파일을 통해서 쉐이더 객체 생성
	HRESULT hr = D3DCompileFromFile(filename.c_str(), NULL, NULL, entry.c_str(), "vs_5_0", 0, 0, &m_pVSCodeResult, &m_pErrorMsgs);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (char*)m_pErrorMsgs->GetBufferPointer(), "ERROR", MB_OK);
		if (m_pErrorMsgs) m_pErrorMsgs->Release();
		return false;
	}
	hr = pd3dDevice->CreateVertexShader(m_pVSCodeResult->GetBufferPointer(), m_pVSCodeResult->GetBufferSize(),
		NULL, &m_pVertexShader);
	if (FAILED(hr)) { return false; }
	return true;
}
bool AShader::CreatePixelShader(ID3D11Device* pd3dDevice, wstring filename, string entry)
{
	HRESULT hr = D3DCompileFromFile(filename.c_str(), NULL, NULL, entry.c_str(), "ps_5_0", 0, 0, &m_pPSCodeResult, &m_pErrorMsgs);
	if (FAILED(hr))
	{
		MessageBoxA(NULL, (char*)m_pErrorMsgs->GetBufferPointer(), "ERROR", MB_OK);
		if (m_pErrorMsgs) m_pErrorMsgs->Release();
		return false;
	}
	hr = pd3dDevice->CreatePixelShader(m_pPSCodeResult->GetBufferPointer(), m_pPSCodeResult->GetBufferSize(),
		NULL, &m_pPixelShader);
	if (FAILED(hr)) { return false; }
	return true;
}
bool AShader::Load(ID3D11Device* pd3dDevice, wstring filename)
{
	if (!CreateVertexShader(pd3dDevice, filename)) { return false; }
	if (!CreatePixelShader(pd3dDevice, filename)) { return false; }
    return true;
}
bool AShader::Init() { return true; }
bool AShader::Frame() { return true; }
bool AShader::Render() { return true; }
bool AShader::Release()
{
	if (m_pVertexShader) m_pVertexShader->Release();
	if (m_pPixelShader)	 m_pPixelShader->Release();
	m_pVertexShader		 = nullptr;
	m_pPixelShader		 = nullptr;
	return true;
}

AShader* AShaderMgr::CreateVertexShader(ID3D11Device* pd3dDevice, wstring filename, string entry)
{
	wstring name = Splitpath(filename, to_mw(entry));
	AShader* pData = GetPtr(name);
	if (pData != nullptr) { return pData; }
	pData = new AShader;
	if (!pData->CreateVertexShader(pd3dDevice, filename, entry))
	{
		delete pData;
		//return nullptr;
	}
	shared_ptr<AShader> pNewData = std::make_shared<AShader>();
	pNewData->m_csName = name;
	m_list.insert(make_pair(pNewData->m_csName, pNewData));
	m_iIndex++;
	return pNewData.get();
}
AShader* AShaderMgr::CreatePixelShader(ID3D11Device* pd3dDevice, wstring filename, string entry)
{
	wstring name = Splitpath(filename, to_mw(entry));
	AShader* pData = GetPtr(name);
	if (pData != nullptr) { return pData; }

	auto pNewData = make_shared<AShader>();
	//pData = new AShader;
	if (!pData->CreatePixelShader(pd3dDevice, filename, entry))
	{
		//delete pData;
		return nullptr;
	}
	pData->m_csName = name;
	m_list.insert(make_pair(pData->m_csName, pData));
	m_iIndex++;
	return pData;
}
