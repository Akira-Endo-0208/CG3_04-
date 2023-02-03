#pragma once

#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>

class DirectionalLight
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

public: //�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMVECTOR lightv;	//���C�g�ւ̕�����\���x�N�g��
		XMFLOAT3 lightcolor; //���C�g�̐F
		unsigned int active;
	};
public: //�ÓI�����o�֐�
	static void StaticInitialize(ID3D12Device* device);

	void Initialize();

	void CreateConstBuffer();

	void TransferConstBuffer();

	inline const XMVECTOR& GetLightDir() { return lightdir_; }

	void SetLightDir(const XMVECTOR& lightdir);

	inline const XMFLOAT3& GetLightColor() { return lightcolor_; }

	void SetLightColor(const XMFLOAT3& lightcolor);


	inline void SetActive(bool active) { this->active = active; }

	inline bool IsActive() 
	{ return active; }

private: //�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;

	
private: //�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff_;
	D3D12_HEAP_PROPERTIES cbHeapProp_{};
	D3D12_RESOURCE_DESC cbResourceDesc_{};

	//���C�g���������i�P�ʃx�N�g���j
	XMVECTOR lightdir_ = { 1,0,0,0 };
	//���C�g�F
	XMFLOAT3 lightcolor_ = { 1,1,1 };
	//�_�[�e�B�t���O
	bool dirty_ = false;

	
	bool active = false;
};

