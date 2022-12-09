#pragma once

#include <DirectXMath.h>

class PointLight
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
		XMFLOAT3 lightpos;
		float pad1;
		XMFLOAT3 lightcolor;
		float pad2;
		XMFLOAT3 lightatten;
		unsigned int active;
	};

public://メンバ関数

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

private://メンバ変数
	//ライト座標（ワールド座標系）
	XMFLOAT3 lightPos_ = { 0,0,0 };
	//ライト色
	XMFLOAT3 lightColor_ = { 1,1,1 };
	//ライト距離減衰係数
	XMFLOAT3 lightAtten_ = { 1.0f,1.0f,1.0f };
	//有効フラグ
	bool active_ = false;

};

