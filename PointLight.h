#pragma once

#include <DirectXMath.h>

class PointLight
{

private:

	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://�T�u�N���X

	struct ConstBufferData
	{
		XMFLOAT3 lightpos;
		float pad1;
		XMFLOAT3 lightcolor;
		float pad2;
		XMFLOAT3 lightatten;
		unsigned int active;
	};

public://�����o�֐�

	inline void SetLightPos(const XMFLOAT3& lightpos)
	{
		this->lightPos_ = lightpos;
	}

	inline const XMFLOAT3& GetLightPos() { return lightPos_; }

	inline void SetLightColor(const XMFLOAT3& lightcolor)
	{
		this->lightColor_ = lightcolor;
	}

	inline const XMFLOAT3& GetLightColor() { return lightColor_; }

	inline void SetLightAtten(const XMFLOAT3& lightAtten)
	{
		this->lightAtten_ = lightAtten;
	}

	inline const XMFLOAT3& GetLightAtten() { return lightAtten_; }

	inline void SetActive(bool active) { this->active_ = active; }

	inline bool IsActive()
	{
		return active_;
	}

private://�����o�ϐ�
	//���C�g���W�i���[���h���W�n�j
	XMFLOAT3 lightPos_ = { 0,0,0 };
	//���C�g�F
	XMFLOAT3 lightColor_ = { 1,1,1 };
	//���C�g���������W��
	XMFLOAT3 lightAtten_ = { 1.0f,1.0f,1.0f };
	//�L���t���O
	bool active_ = false;

};

