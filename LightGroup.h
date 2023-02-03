#pragma once

#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include "DirectionalLight.h"
class LightGroup
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;


public: //�萔

	static const int DirLightNum = 3;

public: //�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		//�����̐F
		XMFLOAT3 ambientColor_;

		float pad1;
		//���s�����p
		DirectionalLight::ConstBufferData dirLights[DirLightNum];

	};
public: //�ÓI�����o�֐�

	static void StaticInitialize(ID3D12Device* device);

	static LightGroup* Create();

private: //�ÓI�����o�ϐ�

	//�f�o�C�X
	static ID3D12Device* device;

public: //�����o�֐�

	void Initialize();

	void Update();

	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	void CreateConstBuffer();

	void TransferConstBuffer();

	void SetAmbientColor(const XMFLOAT3& color);

	void SetDirLightActive(int index, bool active);

	void SetDirLightDir(int index, const XMVECTOR& lightdir);

	void SetDirLightColor(int index, const XMFLOAT3& lightcolor);

	void DefaultLightSetting();

private: //�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff_;
	

	D3D12_HEAP_PROPERTIES cbHeapProp_{};
	D3D12_RESOURCE_DESC cbResourceDesc_{};

	//�����̐F
	XMFLOAT3 ambientColor_ = {1,1,1};
	
	//���s�����̔z��
	DirectionalLight dirLights[DirLightNum];

	//�_�[�e�B�t���O
	bool dirty_ = false;

};

