#include "LightGroup.h"

using namespace DirectX;

ID3D12Device* LightGroup::device = nullptr;

void LightGroup::StaticInitialize(ID3D12Device* device) {
	//�ď������`�F�b�N
	assert(!LightGroup::device);

	//nullptr�`�F�b�N
	assert(device);

	LightGroup::device = device;
}

LightGroup* LightGroup::Create()
{
	//3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	LightGroup* instance = new LightGroup();

	//������
	instance->Initialize();

	return instance;
}

void LightGroup::Initialize()
{
	DefaultLightSetting();

	//�q�[�v�ݒ�
	cbHeapProp_.Type = D3D12_HEAP_TYPE_UPLOAD;

	//���\�[�X�ݒ�
	cbResourceDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc_.Width = (sizeof(ConstBufferData) + 0xff) & ~0xff;
	cbResourceDesc_.Height = 1;
	cbResourceDesc_.DepthOrArraySize = 1;
	cbResourceDesc_.MipLevels = 1;
	cbResourceDesc_.SampleDesc.Count = 1;
	cbResourceDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	CreateConstBuffer();

	//�萔�o�b�t�@�փf�[�^�]��
	TransferConstBuffer();
}

void LightGroup::Update()
{
	if (dirty_) {
		TransferConstBuffer();
		dirty_ = false;
	}

}

void LightGroup::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//�萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff_->GetGPUVirtualAddress());

}

void LightGroup::CreateConstBuffer()
{
	HRESULT result;
	result = device->CreateCommittedResource(
		&cbHeapProp_, //�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc_, //���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff_));
	assert(SUCCEEDED(result));
}

void LightGroup::TransferConstBuffer()
{
	HRESULT result;

	//�萔�o�b�t�@�փf�[�^�]��
	ConstBufferData* constMap = nullptr;
	result = constBuff_->Map(0, nullptr, (void**)&constMap);

	if (SUCCEEDED(result)) {
		constMap->ambientColor_ = ambientColor_;

		for (int i = 0; i < DirLightNum; i++) {
			//���C�g���L���Ȃ�ݒ��]��
			if (dirLights[i].IsActive()) {
				constMap->dirLights[i].active = 1;
				constMap->dirLights[i].lightv = -dirLights[i].GetLightDir();
				constMap->dirLights[i].lightcolor = dirLights[i].GetLightColor();
			}
			else {
				constMap->dirLights[i].active = 0;
			}
		}

		for (int i = 0; i < PointLightNum; i++)
		{
			//���C�g���L���Ȃ�ݒ��]��
			if (pointLights[i].IsActive()) {
				constMap->pointLights[i].active = 1;
				constMap->pointLights[i].lightpos = pointLights[i].GetLightPos();

				constMap->pointLights[i].lightcolor = pointLights[i].GetLightColor();

				constMap->pointLights[i].lightatten =
					pointLights[i].GetLightAtten();
			}
			else {
				constMap->pointLights[i].active = 0;
			}
		}
		constBuff_->Unmap(0, nullptr);

	}
}

void LightGroup::SetAmbientColor(const XMFLOAT3& color)
{
	ambientColor_ = color;
	dirty_ = true;
}

void LightGroup::SetDirLightActive(int index, bool active)
{
	assert(0 <= index && index < DirLightNum);
	dirLights[index].SetActive(active);
}

void LightGroup::SetDirLightDir(int index, const XMVECTOR& lightdir)
{
	assert(0 <= index && index < DirLightNum);
	dirLights[index].SetLightDir(lightdir);
	dirty_ = true;
}

void LightGroup::SetDirLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < DirLightNum);
	dirLights[index].SetLightColor(lightcolor);
	dirty_ = true;
}

void LightGroup::DefaultLightSetting()
{
	dirLights[0].SetActive(true);
	dirLights[0].SetLightColor({ 1.0f,1.0f,1.0f });
	dirLights[0].SetLightDir({ 0.0f,-1.0f,0.0f,0 });

	dirLights[1].SetActive(true);
	dirLights[1].SetLightColor({ 1.0f,1.0f,1.0f });
	dirLights[1].SetLightDir({ +0.5f,+0.1f,+0.2f,0 });

	dirLights[2].SetActive(true);
	dirLights[2].SetLightColor({ 1.0f,1.0f,1.0f });
	dirLights[2].SetLightDir({ -0.5f,+0.1f,-0.2f,0 });
}

void LightGroup::SetPointLightActive(int index, bool active)
{
	assert(0 <= index && index < PointLightNum);
	pointLights[index].SetActive(active);
}

void LightGroup::SetPointLightPos(int index, const XMFLOAT3& lightpos)
{

	assert(0 <= index && index < PointLightNum);
	pointLights[index].SetLightPos(lightpos);
	dirty_ = true;

}

void LightGroup::SetPointLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < PointLightNum);
	pointLights[index].SetLightColor(lightcolor);
	dirty_ = true;
}

void LightGroup::SetPointLightAtten(int index, const XMFLOAT3& lightAtten)
{
	assert(0 <= index && index < PointLightNum);
	pointLights[index].SetLightAtten(lightAtten);
	dirty_ = true;
}

