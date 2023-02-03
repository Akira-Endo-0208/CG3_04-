#pragma once

#include<DirectXMath.h>

class SpotLight
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
		XMVECTOR lightv;
		XMFLOAT3 lightpos;
		float pad1;
		XMFLOAT3 lightcolor;
		float pad2;
		XMFLOAT3 lightatten;
		float pad3;
		XMFLOAT2 lightActorAnglecos;
		unsigned int active;
		float pad4;
	};

public:

	void SetLightDir(const XMVECTOR& lightdir)
	{
		this->lightdir_ = DirectX::XMVector3Normalize(lightdir);
	}

	inline const XMVECTOR& GetLightDir() { return lightdir_; }


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

	inline void SetLightFactorAngle(const XMFLOAT2& lightFactorAngle) {
		this->lightFactorAngleCos.x = cosf(DirectX::XMConvertToRadians(lightFactorAngle.x));
		this->lightFactorAngleCos.y = cosf(DirectX::XMConvertToRadians(lightFactorAngle.y));
	}

	inline const XMFLOAT2& GetLightFactorAngleCos()
	{
		return lightFactorAngleCos;
	}
	inline void SetActive(bool active) { this->active_ = active; }

	inline bool IsActive()
	{
		return active_;
	}

private: //�����o�ϐ�
	//���C�g�����i�P�ʃx�N�g���j
	XMVECTOR lightdir_ = { 1,0,0,0 };
	//���C�g���W�i���[���h���W�n�j
	XMFLOAT3 lightPos_ = { 0,0,0 };
	//���C�g�F
	XMFLOAT3 lightColor_ = { 1,1,1 };
	//���C�g���������W��
	XMFLOAT3 lightAtten_ = { 1.0f,1.0f,1.0f };
	//���C�g�����p�x�i�J�n�p�x�A�I���p�x�j
	XMFLOAT2 lightFactorAngleCos = { 0.5f,0.2f };
	//�L���t���O
	bool active_ = false;
};

