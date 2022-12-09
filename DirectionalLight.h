#pragma once

#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>

class DirectionalLight
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

public: //サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMVECTOR lightv;	//ライトへの方向を表すベクトル
		XMFLOAT3 lightcolor; //ライトの色
		unsigned int active;
	};
public: //静的メンバ関数
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

private: //静的メンバ変数
	//デバイス
	static ID3D12Device* device;

	
private: //メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff_;
	D3D12_HEAP_PROPERTIES cbHeapProp_{};
	D3D12_RESOURCE_DESC cbResourceDesc_{};

	//ライト光線方向（単位ベクトル）
	XMVECTOR lightdir_ = { 1,0,0,0 };
	//ライト色
	XMFLOAT3 lightcolor_ = { 1,1,1 };
	//ダーティフラグ
	bool dirty_ = false;

	
	bool active = false;
};

