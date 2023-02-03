#pragma once

#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class LightGroup
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


public: //定数

	static const int DirLightNum = 3;

	static const int PointLightNum = 3;

	static const int SpotLightNum = 3;

public: //サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		//環境光の色
		XMFLOAT3 ambientColor_;

		float pad1;
		//平行光源用
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//点光源用
		PointLight::ConstBufferData pointLights[PointLightNum];
		//スポットライト用
		SpotLight::ConstBufferData spotLights[SpotLightNum];

	};
public: //静的メンバ関数

	static void StaticInitialize(ID3D12Device* device);

	static LightGroup* Create();

private: //静的メンバ変数

	//デバイス
	static ID3D12Device* device;

public: //メンバ関数

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

public: //アクセッサ

	void SetPointLightActive(int index, bool active);

	void SetPointLightPos(int index, const XMFLOAT3& lightpos);

	void SetPointLightColor(int index, const XMFLOAT3& lightcolor);

	void SetPointLightAtten(int index, const XMFLOAT3& lightAtten);



	void SetSpotLightActive(int index, bool active);

	void SetSpotLightDir(int index, const XMVECTOR& lightdir);

	void SetSpotLightPos(int index, const XMFLOAT3& lightpos);

	void SetSpotLightColor(int index, const XMFLOAT3& lightcolor);

	void SetSpotLightAtten(int index, const XMFLOAT3& lightAtten);

	void SetSpotLightFactorAngle(int index, const XMFLOAT2& lightFactorAngle);

private: //メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff_;
	

	D3D12_HEAP_PROPERTIES cbHeapProp_{};
	D3D12_RESOURCE_DESC cbResourceDesc_{};

	//環境光の色
	XMFLOAT3 ambientColor_ = {1,1,1};
	
	//平行光源の配列
	DirectionalLight dirLights[DirLightNum];

	//ダーティフラグ
	bool dirty_ = false;

	PointLight pointLights[PointLightNum];

	SpotLight spotLights[SpotLightNum];

};

