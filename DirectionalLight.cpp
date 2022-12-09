#include "DirectionalLight.h"
using namespace DirectX;

ID3D12Device* DirectionalLight::device = nullptr;

void DirectionalLight::StaticInitialize(ID3D12Device* device)
{
	//再初期化チェック
	assert(!DirectionalLight::device);
	//nullptrチェック
	assert(device);
	//静的メンバ変数のセット
	DirectionalLight::device = device;
}

void DirectionalLight::Initialize()
{
	//ヒープ設定
	cbHeapProp_.Type = D3D12_HEAP_TYPE_UPLOAD;

	//リソース設定
	cbResourceDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc_.Width = (sizeof(ConstBufferData) + 0xff) & ~0xff;
	cbResourceDesc_.Height = 1;
	cbResourceDesc_.DepthOrArraySize = 1;
	cbResourceDesc_.MipLevels = 1;
	cbResourceDesc_.SampleDesc.Count = 1;
	cbResourceDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	CreateConstBuffer();
	
	//定数バッファへデータ転送
	TransferConstBuffer();
}

void DirectionalLight::CreateConstBuffer()
{
	HRESULT result;
	result = device->CreateCommittedResource(
		&cbHeapProp_, //ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc_, //リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
}

void DirectionalLight::TransferConstBuffer()
{
	HRESULT result;

	//定数バッファへデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff_->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->lightv = -lightdir_;
		constMap->lightcolor = lightcolor_;
		constBuff_->Unmap(0, nullptr);

	}
}

void DirectionalLight::SetLightDir(const XMVECTOR& lightdir)
{
	//正規化してセット
	this->lightdir_ = XMVector3Normalize(lightdir);
	dirty_ = true;

}

void DirectionalLight::SetLightColor(const XMFLOAT3& lightcolor)
{
	this->lightcolor_ = lightcolor;
}

