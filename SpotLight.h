#pragma once

#include<DirectXMath.h>

class SpotLight
{
private:

	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://サブクラス

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

private: //メンバ変数
	//ライト方向（単位ベクトル）
	XMVECTOR lightdir_ = { 1,0,0,0 };
	//ライト座標（ワールド座標系）
	XMFLOAT3 lightPos_ = { 0,0,0 };
	//ライト色
	XMFLOAT3 lightColor_ = { 1,1,1 };
	//ライト距離減衰係数
	XMFLOAT3 lightAtten_ = { 1.0f,1.0f,1.0f };
	//ライト減衰角度（開始角度、終了角度）
	XMFLOAT2 lightFactorAngleCos = { 0.5f,0.2f };
	//有効フラグ
	bool active_ = false;
};

