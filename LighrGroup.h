#pragma once

#include "PointLight.h"
#include "Light.h"
#include <DirectXMath.h>


class LighrGroup
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	//点光源の数
	static const int PointLightNum = 3;

	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		//環境光の色
		XMFLOAT3 ambientColor;
		float pad1;

		//点光源用
		PointLight::ConstBufferData pointLights[PointLightNum];
	};
};

