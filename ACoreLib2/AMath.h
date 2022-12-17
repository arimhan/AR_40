#pragma once
#include <d3d11_1.h> 
//#include <d3dx11.h> 
#if !defined(__d3d11_h__) && !defined(__d3d11_x_h__) && !defined(__d3d12_h__) && !defined(__d3d12_x_h__)
#error include d3d11.h or d3d12.h before including TMath.h
#endif

#if !defined(_XBOX_ONE) || !defined(_TITLE)
//#include <dxgi1_2.h>
#endif

#include <functional>
#include <assert.h>
#include <memory.h>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#ifndef XM_CONSTEXPR
#define XM_CONSTEXPR
#endif

using namespace DirectX;
using namespace DirectX::PackedVector;

namespace A
{
	struct AVector2;
	struct AVector3;
	struct AVector4;
	struct AMatrix;
	struct AQuaternion;
	struct APlane;

	//------------------------------------------------------------------------------
	// 2D rectangle
	struct ARectangle
	{
		long x;
		long y;
		long width;
		long height;

		// Creators
		ARectangle() noexcept : x(0), y(0), width(0), height(0) {}
		XM_CONSTEXPR ARectangle(long ix, long iy, long iw, long ih) : x(ix), y(iy), width(iw), height(ih) {}
		explicit ARectangle(const RECT& rct) : x(rct.left), y(rct.top), width(rct.right - rct.left), height(rct.bottom - rct.top) {}

		ARectangle(const ARectangle&) = default;
		ARectangle& operator=(const ARectangle&) = default;

		ARectangle(ARectangle&&) = default;
		ARectangle& operator=(ARectangle&&) = default;

		operator RECT() { RECT rct; rct.left = x; rct.top = y; rct.right = (x + width); rct.bottom = (y + height); return rct; }
#ifdef __cplusplus_winrt
		operator Windows::Foundation::Rect() { return Windows::Foundation::Rect(float(x), float(y), float(width), float(height)); }
#endif

		// Comparison operators
		bool operator == (const ARectangle& r) const { return (x == r.x) && (y == r.y) && (width == r.width) && (height == r.height); }
		bool operator == (const RECT& rct) const { return (x == rct.left) && (y == rct.top) && (width == (rct.right - rct.left)) && (height == (rct.bottom - rct.top)); }

		bool operator != (const ARectangle& r) const { return (x != r.x) || (y != r.y) || (width != r.width) || (height != r.height); }
		bool operator != (const RECT& rct) const { return (x != rct.left) || (y != rct.top) || (width != (rct.right - rct.left)) || (height != (rct.bottom - rct.top)); }

		// Assignment operators
		ARectangle& operator=(_In_ const RECT& rct) { x = rct.left; y = rct.top; width = (rct.right - rct.left); height = (rct.bottom - rct.top); return *this; }

		// ARectangle operations
		AVector2 Location() const;
		AVector2 Center() const;

		bool IsEmpty() const { return (width == 0 && height == 0 && x == 0 && y == 0); }

		bool Contains(long ix, long iy) const { return (x <= ix) && (ix < (x + width)) && (y <= iy) && (iy < (y + height)); }
		bool Contains(const AVector2& point) const;
		bool Contains(const ARectangle& r) const { return (x <= r.x) && ((r.x + r.width) <= (x + width)) && (y <= r.y) && ((r.y + r.height) <= (y + height)); }
		bool Contains(const RECT& rct) const { return (x <= rct.left) && (rct.right <= (x + width)) && (y <= rct.top) && (rct.bottom <= (y + height)); }

		void Inflate(long horizAmount, long vertAmount);

		bool Intersects(const ARectangle& r) const { return (r.x < (x + width)) && (x < (r.x + r.width)) && (r.y < (y + height)) && (y < (r.y + r.height)); }
		bool Intersects(const RECT& rct) const { return (rct.left < (x + width)) && (x < rct.right) && (rct.top < (y + height)) && (y < rct.bottom); }

		void Offset(long ox, long oy) { x += ox; y += oy; }

		// Static functions
		static ARectangle Intersect(const ARectangle& ra, const ARectangle& rb);
		static RECT Intersect(const RECT& rcta, const RECT& rctb);

		static ARectangle Union(const ARectangle& ra, const ARectangle& rb);
		static RECT Union(const RECT& rcta, const RECT& rctb);
	};

	//------------------------------------------------------------------------------
	// 2D vector
	struct AVector2 : DirectX::XMFLOAT2
	{
		AVector2() noexcept : XMFLOAT2(0.f, 0.f) {}
		XM_CONSTEXPR explicit AVector2(float x) : XMFLOAT2(x, x) {}
		XM_CONSTEXPR AVector2(float _x, float _y) : XMFLOAT2(_x, _y) {}
		explicit AVector2(_In_reads_(2) const float *pArray) : XMFLOAT2(pArray) {}
		AVector2(XMFLOAT2 V) { x = V.x; y = V.y; }
		AVector2(const XMFLOAT2& V) { this->x = V.x; this->y = V.y; }
		explicit AVector2(const DirectX::XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; }

		AVector2(const AVector2&) = default;
		AVector2& operator=(const AVector2&) = default;

		AVector2(AVector2&&) = default;
		AVector2& operator=(AVector2&&) = default;

		operator DirectX::XMVECTOR() const { return XMLoadFloat2(this); }

		// Comparison operators
		bool operator == (const AVector2& V) const;
		bool operator != (const AVector2& V) const;

		// Assignment operators
		AVector2& operator= (const DirectX::XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; return *this; }
		AVector2& operator+= (const AVector2& V);
		AVector2& operator-= (const AVector2& V);
		AVector2& operator*= (const AVector2& V);
		AVector2& operator*= (float S);
		AVector2& operator/= (float S);

		// Unary operators
		AVector2 operator+ () const { return *this; }
		AVector2 operator- () const { return AVector2(-x, -y); }

		// Vector operations
		bool InBounds(const AVector2& Bounds) const;

		float Length() const;
		float LengthSquared() const;

		float Dot(const AVector2& V) const;
		void Cross(const AVector2& V, AVector2& result) const;
		AVector2 Cross(const AVector2& V) const;

		void Normalize();
		void Normalize(AVector2& result) const;

		void Clamp(const AVector2& vmin, const AVector2& vmax);
		void Clamp(const AVector2& vmin, const AVector2& vmax, AVector2& result) const;

		// Static functions
		static float Distance(const AVector2& v1, const AVector2& v2);
		static float DistanceSquared(const AVector2& v1, const AVector2& v2);

		static void Min(const AVector2& v1, const AVector2& v2, AVector2& result);
		static AVector2 Min(const AVector2& v1, const AVector2& v2);

		static void Max(const AVector2& v1, const AVector2& v2, AVector2& result);
		static AVector2 Max(const AVector2& v1, const AVector2& v2);

		static void Lerp(const AVector2& v1, const AVector2& v2, float t, AVector2& result);
		static AVector2 Lerp(const AVector2& v1, const AVector2& v2, float t);

		static void SmoothStep(const AVector2& v1, const AVector2& v2, float t, AVector2& result);
		static AVector2 SmoothStep(const AVector2& v1, const AVector2& v2, float t);

		static void Barycentric(const AVector2& v1, const AVector2& v2, const AVector2& v3, float f, float g, AVector2& result);
		static AVector2 Barycentric(const AVector2& v1, const AVector2& v2, const AVector2& v3, float f, float g);

		static void CatmullRom(const AVector2& v1, const AVector2& v2, const AVector2& v3, const AVector2& v4, float t, AVector2& result);
		static AVector2 CatmullRom(const AVector2& v1, const AVector2& v2, const AVector2& v3, const AVector2& v4, float t);

		static void Hermite(const AVector2& v1, const AVector2& t1, const AVector2& v2, const AVector2& t2, float t, AVector2& result);
		static AVector2 Hermite(const AVector2& v1, const AVector2& t1, const AVector2& v2, const AVector2& t2, float t);

		static void Reflect(const AVector2& ivec, const AVector2& nvec, AVector2& result);
		static AVector2 Reflect(const AVector2& ivec, const AVector2& nvec);

		static void Refract(const AVector2& ivec, const AVector2& nvec, float refractionIndex, AVector2& result);
		static AVector2 Refract(const AVector2& ivec, const AVector2& nvec, float refractionIndex);

		static void Transform(const AVector2& v, const AQuaternion& quat, AVector2& result);
		static AVector2 Transform(const AVector2& v, const AQuaternion& quat);

		static void Transform(const AVector2& v, const AMatrix& m, AVector2& result);
		static AVector2 Transform(const AVector2& v, const AMatrix& m);
		static void Transform(_In_reads_(count) const AVector2* varray, size_t count, const AMatrix& m, _Out_writes_(count) AVector2* resultArray);

		static void Transform(const AVector2& v, const AMatrix& m, AVector4& result);
		static void Transform(_In_reads_(count) const AVector2* varray, size_t count, const AMatrix& m, _Out_writes_(count) AVector4* resultArray);

		static void TransformNormal(const AVector2& v, const AMatrix& m, AVector2& result);
		static AVector2 TransformNormal(const AVector2& v, const AMatrix& m);
		static void TransformNormal(_In_reads_(count) const AVector2* varray, size_t count, const AMatrix& m, _Out_writes_(count) AVector2* resultArray);

		// Constants
		static const AVector2 Zero;
		static const AVector2 One;
		static const AVector2 UnitX;
		static const AVector2 UnitY;
	};

	// Binary operators
	AVector2 operator+ (const AVector2& V1, const AVector2& V2);
	AVector2 operator- (const AVector2& V1, const AVector2& V2);
	AVector2 operator* (const AVector2& V1, const AVector2& V2);
	AVector2 operator* (const AVector2& V, float S);
	AVector2 operator/ (const AVector2& V1, const AVector2& V2);
	AVector2 operator* (float S, const AVector2& V);

	//------------------------------------------------------------------------------
	// 3D vector
	struct AVector3 : DirectX::XMFLOAT3
	{
		AVector3() noexcept : DirectX::XMFLOAT3(0.f, 0.f, 0.f) {}
		XM_CONSTEXPR explicit AVector3(float x) : DirectX::XMFLOAT3(x, x, x) {}
		XM_CONSTEXPR AVector3(float _x, float _y, float _z) : DirectX::XMFLOAT3(_x, _y, _z) {}
		AVector3(const float *pArray) : DirectX::XMFLOAT3(pArray) {}
		AVector3(DirectX::XMFLOAT3 V) { x = V.x; y = V.y; z = V.z; }
		AVector3(const DirectX::XMFLOAT3& V) { this->x = V.x; this->y = V.y; this->z = V.z; }
		explicit AVector3(const DirectX::XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; }

		AVector3(const AVector3&) = default;
		AVector3& operator=(const AVector3&) = default;

		AVector3(AVector3&&) = default;
		AVector3& operator=(AVector3&&) = default;

		operator DirectX::XMVECTOR() const { return XMLoadFloat3(this); }

		float operator [](int i)
		{
			if (i == 0) return x;
			if (i == 1) return y;
			if (i == 2) return z;
			return 0.0f;
		}

		// Comparison operators
		bool operator == (const AVector3& V) const;
		bool operator != (const AVector3& V) const;

		// Assignment operators
		AVector3& operator= (const DirectX::XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; return *this; }
		AVector3& operator+= (const AVector3& V);
		AVector3& operator-= (const AVector3& V);
		AVector3& operator*= (const AVector3& V);
		AVector3& operator*= (float S);
		AVector3& operator/= (float S);

		// Unary operators
		AVector3 operator+ () const { return *this; }
		AVector3 operator- () const;

		// Vector operations
		bool InBounds(const AVector3& Bounds) const;

		float Length() const;
		float LengthSquared() const;

		float Dot(const AVector3& V) const;
		void Cross(const AVector3& V, AVector3& result) const;
		AVector3 Cross(const AVector3& V) const;

		void Normalize();
		void Normalize(AVector3& result) const;

		void Clamp(const AVector3& vmin, const AVector3& vmax);
		void Clamp(const AVector3& vmin, const AVector3& vmax, AVector3& result) const;

		// Static functions
		static float Distance(const AVector3& v1, const AVector3& v2);
		static float DistanceSquared(const AVector3& v1, const AVector3& v2);

		static void Min(const AVector3& v1, const AVector3& v2, AVector3& result);
		static AVector3 Min(const AVector3& v1, const AVector3& v2);

		static void Max(const AVector3& v1, const AVector3& v2, AVector3& result);
		static AVector3 Max(const AVector3& v1, const AVector3& v2);

		static void Lerp(const AVector3& v1, const AVector3& v2, float t, AVector3& result);
		static AVector3 Lerp(const AVector3& v1, const AVector3& v2, float t);

		static void SmoothStep(const AVector3& v1, const AVector3& v2, float t, AVector3& result);
		static AVector3 SmoothStep(const AVector3& v1, const AVector3& v2, float t);

		static void Barycentric(const AVector3& v1, const AVector3& v2, const AVector3& v3, float f, float g, AVector3& result);
		static AVector3 Barycentric(const AVector3& v1, const AVector3& v2, const AVector3& v3, float f, float g);

		static void CatmullRom(const AVector3& v1, const AVector3& v2, const AVector3& v3, const AVector3& v4, float t, AVector3& result);
		static AVector3 CatmullRom(const AVector3& v1, const AVector3& v2, const AVector3& v3, const AVector3& v4, float t);

		static void Hermite(const AVector3& v1, const AVector3& t1, const AVector3& v2, const AVector3& t2, float t, AVector3& result);
		static AVector3 Hermite(const AVector3& v1, const AVector3& t1, const AVector3& v2, const AVector3& t2, float t);

		static void Reflect(const AVector3& ivec, const AVector3& nvec, AVector3& result);
		static AVector3 Reflect(const AVector3& ivec, const AVector3& nvec);

		static void Refract(const AVector3& ivec, const AVector3& nvec, float refractionIndex, AVector3& result);
		static AVector3 Refract(const AVector3& ivec, const AVector3& nvec, float refractionIndex);

		static void Transform(const AVector3& v, const AQuaternion& quat, AVector3& result);
		static AVector3 Transform(const AVector3& v, const AQuaternion& quat);

		static void Transform(const AVector3& v, const AMatrix& m, AVector3& result);
		static AVector3 Transform(const AVector3& v, const AMatrix& m);
		static void Transform(_In_reads_(count) const AVector3* varray, size_t count, const AMatrix& m, _Out_writes_(count) AVector3* resultArray);

		static void Transform(const AVector3& v, const AMatrix& m, AVector4& result);
		static void Transform(_In_reads_(count) const AVector3* varray, size_t count, const AMatrix& m, _Out_writes_(count) AVector4* resultArray);

		static void TransformNormal(const AVector3& v, const AMatrix& m, AVector3& result);
		static AVector3 TransformNormal(const AVector3& v, const AMatrix& m);
		static void TransformNormal(_In_reads_(count) const AVector3* varray, size_t count, const AMatrix& m, _Out_writes_(count) AVector3* resultArray);

		// Constants
		static const AVector3 Zero;
		static const AVector3 One;
		static const AVector3 UnitX;
		static const AVector3 UnitY;
		static const AVector3 UnitZ;
		static const AVector3 Up;
		static const AVector3 Down;
		static const AVector3 Right;
		static const AVector3 Left;
		static const AVector3 Forward;
		static const AVector3 Backward;
	};

	// Binary operators
	AVector3 operator+ (const AVector3& V1, const AVector3& V2);
	AVector3 operator- (const AVector3& V1, const AVector3& V2);
	AVector3 operator* (const AVector3& V1, const AVector3& V2);
	AVector3 operator* (const AVector3& V, float S);
	AVector3 operator/ (const AVector3& V1, const AVector3& V2);
	AVector3 operator* (float S, const AVector3& V);

	//------------------------------------------------------------------------------
	// 4D vector
	struct AVector4 : public XMFLOAT4
	{
		AVector4() noexcept : XMFLOAT4(0.f, 0.f, 0.f, 0.f) {}
		XM_CONSTEXPR explicit AVector4(float x) : XMFLOAT4(x, x, x, x) {}
		XM_CONSTEXPR AVector4(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
		explicit AVector4(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
		AVector4(XMFLOAT4 V) { x = V.x; y = V.y; z = V.z; w = V.w; }
		AVector4(const XMFLOAT4& V) { this->x = V.x; this->y = V.y; this->z = V.z; this->w = V.w; }
		explicit AVector4(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		AVector4(const AVector4&) = default;
		AVector4& operator=(const AVector4&) = default;

		AVector4(AVector4&&) = default;
		AVector4& operator=(AVector4&&) = default;

		operator XMVECTOR() const { return XMLoadFloat4(this); }

		// Comparison operators
		bool operator == (const AVector4& V) const;
		bool operator != (const AVector4& V) const;

		// Assignment operators
		AVector4& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
		AVector4& operator+= (const AVector4& V);
		AVector4& operator-= (const AVector4& V);
		AVector4& operator*= (const AVector4& V);
		AVector4& operator*= (float S);
		AVector4& operator/= (float S);

		// Unary operators
		AVector4 operator+ () const { return *this; }
		AVector4 operator- () const;

		// Vector operations
		bool InBounds(const AVector4& Bounds) const;

		float Length() const;
		float LengthSquared() const;

		float Dot(const AVector4& V) const;
		void Cross(const AVector4& v1, const AVector4& v2, AVector4& result) const;
		AVector4 Cross(const AVector4& v1, const AVector4& v2) const;

		void Normalize();
		void Normalize(AVector4& result) const;

		void Clamp(const AVector4& vmin, const AVector4& vmax);
		void Clamp(const AVector4& vmin, const AVector4& vmax, AVector4& result) const;

		// Static functions
		static float Distance(const AVector4& v1, const AVector4& v2);
		static float DistanceSquared(const AVector4& v1, const AVector4& v2);

		static void Min(const AVector4& v1, const AVector4& v2, AVector4& result);
		static AVector4 Min(const AVector4& v1, const AVector4& v2);

		static void Max(const AVector4& v1, const AVector4& v2, AVector4& result);
		static AVector4 Max(const AVector4& v1, const AVector4& v2);

		static void Lerp(const AVector4& v1, const AVector4& v2, float t, AVector4& result);
		static AVector4 Lerp(const AVector4& v1, const AVector4& v2, float t);

		static void SmoothStep(const AVector4& v1, const AVector4& v2, float t, AVector4& result);
		static AVector4 SmoothStep(const AVector4& v1, const AVector4& v2, float t);

		static void Barycentric(const AVector4& v1, const AVector4& v2, const AVector4& v3, float f, float g, AVector4& result);
		static AVector4 Barycentric(const AVector4& v1, const AVector4& v2, const AVector4& v3, float f, float g);

		static void CatmullRom(const AVector4& v1, const AVector4& v2, const AVector4& v3, const AVector4& v4, float t, AVector4& result);
		static AVector4 CatmullRom(const AVector4& v1, const AVector4& v2, const AVector4& v3, const AVector4& v4, float t);

		static void Hermite(const AVector4& v1, const AVector4& t1, const AVector4& v2, const AVector4& t2, float t, AVector4& result);
		static AVector4 Hermite(const AVector4& v1, const AVector4& t1, const AVector4& v2, const AVector4& t2, float t);

		static void Reflect(const AVector4& ivec, const AVector4& nvec, AVector4& result);
		static AVector4 Reflect(const AVector4& ivec, const AVector4& nvec);

		static void Refract(const AVector4& ivec, const AVector4& nvec, float refractionIndex, AVector4& result);
		static AVector4 Refract(const AVector4& ivec, const AVector4& nvec, float refractionIndex);

		static void Transform(const AVector2& v, const AQuaternion& quat, AVector4& result);
		static AVector4 Transform(const AVector2& v, const AQuaternion& quat);

		static void Transform(const AVector3& v, const AQuaternion& quat, AVector4& result);
		static AVector4 Transform(const AVector3& v, const AQuaternion& quat);

		static void Transform(const AVector4& v, const AQuaternion& quat, AVector4& result);
		static AVector4 Transform(const AVector4& v, const AQuaternion& quat);

		static void Transform(const AVector4& v, const AMatrix& m, AVector4& result);
		static AVector4 Transform(const AVector4& v, const AMatrix& m);
		static void Transform(_In_reads_(count) const AVector4* varray, size_t count, const AMatrix& m, _Out_writes_(count) AVector4* resultArray);

		// Constants
		static const AVector4 Zero;
		static const AVector4 One;
		static const AVector4 UnitX;
		static const AVector4 UnitY;
		static const AVector4 UnitZ;
		static const AVector4 UnitW;
	};

	// Binary operators
	AVector4 operator+ (const AVector4& V1, const AVector4& V2);
	AVector4 operator- (const AVector4& V1, const AVector4& V2);
	AVector4 operator* (const AVector4& V1, const AVector4& V2);
	AVector4 operator* (const AVector4& V, float S);
	AVector4 operator/ (const AVector4& V1, const AVector4& V2);
	AVector4 operator* (float S, const AVector4& V);

	//------------------------------------------------------------------------------
	// 4x4 AMatrix (assumes right-handed cooordinates)
	struct AMatrix : public XMFLOAT4X4
	{
		AMatrix() noexcept
			: XMFLOAT4X4(1.f, 0, 0, 0,
				0, 1.f, 0, 0,
				0, 0, 1.f, 0,
				0, 0, 0, 1.f) {}
		XM_CONSTEXPR AMatrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
			: XMFLOAT4X4(m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33) {}
		explicit AMatrix(const AVector3& r0, const AVector3& r1, const AVector3& r2)
			: XMFLOAT4X4(r0.x, r0.y, r0.z, 0,
				r1.x, r1.y, r1.z, 0,
				r2.x, r2.y, r2.z, 0,
				0, 0, 0, 1.f) {}
		explicit AMatrix(const AVector4& r0, const AVector4& r1, const AVector4& r2, const AVector4& r3)
			: XMFLOAT4X4(r0.x, r0.y, r0.z, r0.w,
				r1.x, r1.y, r1.z, r1.w,
				r2.x, r2.y, r2.z, r2.w,
				r3.x, r3.y, r3.z, r3.w) {}
		AMatrix(const XMFLOAT4X4& M) { memcpy_s(this, sizeof(float) * 16, &M, sizeof(XMFLOAT4X4)); }
		AMatrix(const XMFLOAT3X3& M);
		AMatrix(const XMFLOAT4X3& M);

		explicit AMatrix(_In_reads_(16) const float *pArray) : XMFLOAT4X4(pArray) {}
		AMatrix(CXMMATRIX M) { XMStoreFloat4x4(this, M); }

		AMatrix(const AMatrix&) = default;
		AMatrix& operator=(const AMatrix&) = default;

		AMatrix(AMatrix&&) = default;
		AMatrix& operator=(AMatrix&&) = default;

		operator XMFLOAT4X4() const { return *this; }

		// Comparison operators
		bool operator == (const AMatrix& M) const;
		bool operator != (const AMatrix& M) const;

		// Assignment operators
		AMatrix& operator= (const XMFLOAT3X3& M);
		AMatrix& operator= (const XMFLOAT4X3& M);
		AMatrix& operator+= (const AMatrix& M);
		AMatrix& operator-= (const AMatrix& M);
		AMatrix& operator*= (const AMatrix& M);
		AMatrix& operator*= (float S);
		AMatrix& operator/= (float S);

		AMatrix& operator/= (const AMatrix& M);
		// Element-wise divide

		// Unary operators
		AMatrix operator+ () const { return *this; }
		AMatrix operator- () const;

		// Properties
		AVector3 Up() const { return AVector3(_21, _22, _23); }
		void Up(const AVector3& v) { _21 = v.x; _22 = v.y; _23 = v.z; }

		AVector3 Down() const { return AVector3(-_21, -_22, -_23); }
		void Down(const AVector3& v) { _21 = -v.x; _22 = -v.y; _23 = -v.z; }

		AVector3 Right() const { return AVector3(_11, _12, _13); }
		void Right(const AVector3& v) { _11 = v.x; _12 = v.y; _13 = v.z; }

		AVector3 Left() const { return AVector3(-_11, -_12, -_13); }
		void Left(const AVector3& v) { _11 = -v.x; _12 = -v.y; _13 = -v.z; }

		AVector3 Forward() const { return AVector3(-_31, -_32, -_33); }
		void Forward(const AVector3& v) { _31 = -v.x; _32 = -v.y; _33 = -v.z; }

		AVector3 Backward() const { return AVector3(_31, _32, _33); }
		void Backward(const AVector3& v) { _31 = v.x; _32 = v.y; _33 = v.z; }

		AVector3 Translation() const { return AVector3(_41, _42, _43); }
		void Translation(const AVector3& v) { _41 = v.x; _42 = v.y; _43 = v.z; }

		// AMatrix operations
		bool Decompose(AVector3& scale, AQuaternion& rotation, AVector3& translation);

		AMatrix Transpose() const;
		void Transpose(AMatrix& result) const;

		AMatrix Invert() const;
		void Invert(AMatrix& result) const;

		float Determinant() const;

		// Static functions
		static AMatrix CreateBillboard(const AVector3& object, const AVector3& cameraPosition, const AVector3& cameraUp, _In_opt_ const AVector3* cameraForward = nullptr);

		static AMatrix CreateConstrainedBillboard(const AVector3& object, const AVector3& cameraPosition, const AVector3& rotateAxis,
			_In_opt_ const AVector3* cameraForward = nullptr, _In_opt_ const AVector3* objectForward = nullptr);

		static AMatrix CreateTranslation(const AVector3& position);
		static AMatrix CreateTranslation(float x, float y, float z);

		static AMatrix CreateScale(const AVector3& scales);
		static AMatrix CreateScale(float xs, float ys, float zs);
		static AMatrix CreateScale(float scale);

		static AMatrix CreateRotationX(float radians);
		static AMatrix CreateRotationY(float radians);
		static AMatrix CreateRotationZ(float radians);

		static AMatrix CreateFromAxisAngle(const AVector3& axis, float angle);

		static AMatrix CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane);
		static AMatrix CreatePerspective(float width, float height, float nearPlane, float farPlane);
		static AMatrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane);
		static AMatrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
		static AMatrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);

		static AMatrix CreateLookAt(const AVector3& position, const AVector3& target, const AVector3& up);
		static AMatrix CreateWorld(const AVector3& position, const AVector3& forward, const AVector3& up);

		static AMatrix CreateFromQuaternion(const AQuaternion& quat);

		static AMatrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);

		static AMatrix CreateShadow(const AVector3& lightDir, const APlane& plane);

		static AMatrix CreateReflection(const APlane& plane);

		static void Lerp(const AMatrix& M1, const AMatrix& M2, float t, AMatrix& result);
		static AMatrix Lerp(const AMatrix& M1, const AMatrix& M2, float t);

		static void Transform(const AMatrix& M, const AQuaternion& rotation, AMatrix& result);
		static AMatrix Transform(const AMatrix& M, const AQuaternion& rotation);

		// Constants
		static const AMatrix Identity;
	};

	// Binary operators
	AMatrix operator+ (const AMatrix& M1, const AMatrix& M2);
	AMatrix operator- (const AMatrix& M1, const AMatrix& M2);
	AMatrix operator* (const AMatrix& M1, const AMatrix& M2);
	AMatrix operator* (const AMatrix& M, float S);
	AMatrix operator/ (const AMatrix& M, float S);
	AMatrix operator/ (const AMatrix& M1, const AMatrix& M2);
	// Element-wise divide
	AMatrix operator* (float S, const AMatrix& M);


	//-----------------------------------------------------------------------------
	// APlane
	struct APlane : public XMFLOAT4
	{
		APlane() noexcept : XMFLOAT4(0.f, 1.f, 0.f, 0.f) {}
		XM_CONSTEXPR APlane(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
		APlane(const AVector3& normal, float d) : XMFLOAT4(normal.x, normal.y, normal.z, d) {}
		APlane(const AVector3& point1, const AVector3& point2, const AVector3& point3);
		APlane(const AVector3& point, const AVector3& normal);
		explicit APlane(const AVector4& v) : XMFLOAT4(v.x, v.y, v.z, v.w) {}
		explicit APlane(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
		APlane(XMFLOAT4 V) { x = V.x; y = V.y; z = V.z; w = V.w; }
		APlane(const XMFLOAT4& p) { this->x = p.x; this->y = p.y; this->z = p.z; this->w = p.w; }
		explicit APlane(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		APlane(const APlane&) = default;
		APlane& operator=(const APlane&) = default;

		APlane(APlane&&) = default;
		APlane& operator=(APlane&&) = default;

		operator XMVECTOR() const { return XMLoadFloat4(this); }

		// Comparison operators
		bool operator == (const APlane& p) const;
		bool operator != (const APlane& p) const;

		// Assignment operators
		APlane& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }

		// Properties
		AVector3 Normal() const { return AVector3(x, y, z); }
		void Normal(const AVector3& normal) { x = normal.x; y = normal.y; z = normal.z; }

		float D() const { return w; }
		void D(float d) { w = d; }

		// APlane operations
		void Normalize();
		void Normalize(APlane& result) const;

		float Dot(const AVector4& v) const;
		float DotCoordinate(const AVector3& position) const;
		float DotNormal(const AVector3& normal) const;

		// Static functions
		static void Transform(const APlane& plane, const AMatrix& M, APlane& result);
		static APlane Transform(const APlane& plane, const AMatrix& M);

		static void Transform(const APlane& plane, const AQuaternion& rotation, APlane& result);
		static APlane Transform(const APlane& plane, const AQuaternion& rotation);
		// Input quaternion must be the inverse transpose of the transformation
	};

	//------------------------------------------------------------------------------
	// AQuaternion
	struct AQuaternion : public XMFLOAT4
	{
		AQuaternion() noexcept : XMFLOAT4(0, 0, 0, 1.f) {}
		XM_CONSTEXPR AQuaternion(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
		AQuaternion(const AVector3& v, float scalar) : XMFLOAT4(v.x, v.y, v.z, scalar) {}
		explicit AQuaternion(const AVector4& v) : XMFLOAT4(v.x, v.y, v.z, v.w) {}
		explicit AQuaternion(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
		AQuaternion(XMFLOAT4 V) { x = V.x; y = V.y; z = V.z; w = V.w; }
		AQuaternion(const XMFLOAT4& q) { this->x = q.x; this->y = q.y; this->z = q.z; this->w = q.w; }
		explicit AQuaternion(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		AQuaternion(const AQuaternion&) = default;
		AQuaternion& operator=(const AQuaternion&) = default;

		AQuaternion(AQuaternion&&) = default;
		AQuaternion& operator=(AQuaternion&&) = default;

		//operator int () const { return 0; }
		//SampleClass f;
		//int i = f; //  f.operator int () 를 호출하고 초기화 및 반한됨.
		operator XMVECTOR() const { return XMLoadFloat4(this); }

		// Comparison operators
		bool operator == (const AQuaternion& q) const;
		bool operator != (const AQuaternion& q) const;

		// Assignment operators
		AQuaternion& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
		AQuaternion& operator+= (const AQuaternion& q);
		AQuaternion& operator-= (const AQuaternion& q);
		AQuaternion& operator*= (const AQuaternion& q);
		AQuaternion& operator*= (float S);
		AQuaternion& operator/= (const AQuaternion& q);

		// Unary operators
		AQuaternion operator+ () const { return *this; }
		AQuaternion operator- () const;

		// AQuaternion operations
		float Length() const;
		float LengthSquared() const;

		void Normalize();
		void Normalize(AQuaternion& result) const;

		void Conjugate();
		void Conjugate(AQuaternion& result) const;

		void Inverse(AQuaternion& result) const;

		float Dot(const AQuaternion& Q) const;

		// Static functions
		static AQuaternion CreateFromAxisAngle(const AVector3& axis, float angle);
		static AQuaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
		static AQuaternion CreateFromRotationMatrix(const AMatrix& M);

		static void Lerp(const AQuaternion& q1, const AQuaternion& q2, float t, AQuaternion& result);
		static AQuaternion Lerp(const AQuaternion& q1, const AQuaternion& q2, float t);

		static void Slerp(const AQuaternion& q1, const AQuaternion& q2, float t, AQuaternion& result);
		static AQuaternion Slerp(const AQuaternion& q1, const AQuaternion& q2, float t);

		static void Concatenate(const AQuaternion& q1, const AQuaternion& q2, AQuaternion& result);
		static AQuaternion Concatenate(const AQuaternion& q1, const AQuaternion& q2);

		// Constants
		static const AQuaternion Identity;
	};

	// Binary operators
	AQuaternion operator+ (const AQuaternion& Q1, const AQuaternion& Q2);
	AQuaternion operator- (const AQuaternion& Q1, const AQuaternion& Q2);
	AQuaternion operator* (const AQuaternion& Q1, const AQuaternion& Q2);
	AQuaternion operator* (const AQuaternion& Q, float S);
	AQuaternion operator/ (const AQuaternion& Q1, const AQuaternion& Q2);
	AQuaternion operator* (float S, const AQuaternion& Q);

	//------------------------------------------------------------------------------
	// AColor
	struct AColor : public XMFLOAT4
	{
		AColor() noexcept : XMFLOAT4(0, 0, 0, 1.f) {}
		XM_CONSTEXPR AColor(float _r, float _g, float _b) : XMFLOAT4(_r, _g, _b, 1.f) {}
		XM_CONSTEXPR AColor(float _r, float _g, float _b, float _a) : XMFLOAT4(_r, _g, _b, _a) {}
		explicit AColor(const AVector3& clr) : XMFLOAT4(clr.x, clr.y, clr.z, 1.f) {}
		explicit AColor(const AVector4& clr) : XMFLOAT4(clr.x, clr.y, clr.z, clr.w) {}
		explicit AColor(_In_reads_(4) const float *pArray) : XMFLOAT4(pArray) {}
		AColor(XMFLOAT3 V) { x = V.x; y = V.y; z = V.z; }
		AColor(const XMFLOAT4& c) { this->x = c.x; this->y = c.y; this->z = c.z; this->w = c.w; }
		explicit AColor(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		explicit AColor(const DirectX::PackedVector::XMCOLOR& Packed);
		// BGRA Direct3D 9 D3DCOLOR packed color

		explicit AColor(const DirectX::PackedVector::XMUBYTEN4& Packed);
		// RGBA XNA Game Studio packed color

		AColor(const AColor&) = default;
		AColor& operator=(const AColor&) = default;

		AColor(AColor&&) = default;
		AColor& operator=(AColor&&) = default;

		operator XMVECTOR() const { return XMLoadFloat4(this); }
		operator const float*() const { return reinterpret_cast<const float*>(this); }

		// Comparison operators
		bool operator == (const AColor& c) const;
		bool operator != (const AColor& c) const;

		// Assignment operators
		AColor& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
		AColor& operator= (const DirectX::PackedVector::XMCOLOR& Packed);
		AColor& operator= (const DirectX::PackedVector::XMUBYTEN4& Packed);
		AColor& operator+= (const AColor& c);
		AColor& operator-= (const AColor& c);
		AColor& operator*= (const AColor& c);
		AColor& operator*= (float S);
		AColor& operator/= (const AColor& c);

		// Unary operators
		AColor operator+ () const { return *this; }
		AColor operator- () const;

		// Properties
		float R() const { return x; }
		void R(float r) { x = r; }

		float G() const { return y; }
		void G(float g) { y = g; }

		float B() const { return z; }
		void B(float b) { z = b; }

		float A() const { return w; }
		void A(float a) { w = a; }

		// AColor operations
		DirectX::PackedVector::XMCOLOR BGRA() const;
		DirectX::PackedVector::XMUBYTEN4 RGBA() const;

		AVector3 ToVector3() const;
		AVector4 ToVector4() const;

		void Negate();
		void Negate(AColor& result) const;

		void Saturate();
		void Saturate(AColor& result) const;

		void Premultiply();
		void Premultiply(AColor& result) const;

		void AdjustSaturation(float sat);
		void AdjustSaturation(float sat, AColor& result) const;

		void AdjustContrast(float contrast);
		void AdjustContrast(float contrast, AColor& result) const;

		// Static functions
		static void Modulate(const AColor& c1, const AColor& c2, AColor& result);
		static AColor Modulate(const AColor& c1, const AColor& c2);

		static void Lerp(const AColor& c1, const AColor& c2, float t, AColor& result);
		static AColor Lerp(const AColor& c1, const AColor& c2, float t);
	};

	// Binary operators
	AColor operator+ (const AColor& C1, const AColor& C2);
	AColor operator- (const AColor& C1, const AColor& C2);
	AColor operator* (const AColor& C1, const AColor& C2);
	AColor operator* (const AColor& C, float S);
	AColor operator/ (const AColor& C1, const AColor& C2);
	AColor operator* (float S, const AColor& C);

	//------------------------------------------------------------------------------
	// ARay
	class ARay
	{
	public:
		AVector3 position;
		AVector3 direction;

		ARay() noexcept : position(0, 0, 0), direction(0, 0, 1) {}
		ARay(const AVector3& pos, const AVector3& dir) : position(pos), direction(dir) {}

		ARay(const ARay&) = default;
		ARay& operator=(const ARay&) = default;

		ARay(ARay&&) = default;
		ARay& operator=(ARay&&) = default;

		// Comparison operators
		bool operator == (const ARay& r) const;
		bool operator != (const ARay& r) const;

		// ARay operations
		bool Intersects(const BoundingSphere& sphere, _Out_ float& Dist) const;
		bool Intersects(const BoundingBox& box, _Out_ float& Dist) const;
		bool Intersects(const AVector3& tri0, const AVector3& tri1, const AVector3& tri2, _Out_ float& Dist) const;
		bool Intersects(const APlane& plane, _Out_ float& Dist) const;
	};

	//------------------------------------------------------------------------------
	// AViewport
	class AViewport
	{
	public:
		float x;
		float y;
		float width;
		float height;
		float minDepth;
		float maxDepth;

		AViewport() noexcept :
			x(0.f), y(0.f), width(0.f), height(0.f), minDepth(0.f), maxDepth(1.f) {}
		XM_CONSTEXPR AViewport(float ix, float iy, float iw, float ih, float iminz = 0.f, float imaxz = 1.f) :
			x(ix), y(iy), width(iw), height(ih), minDepth(iminz), maxDepth(imaxz) {}
		explicit AViewport(const RECT& rct) :
			x(float(rct.left)), y(float(rct.top)),
			width(float(rct.right - rct.left)),
			height(float(rct.bottom - rct.top)),
			minDepth(0.f), maxDepth(1.f) {}

#if defined(__d3d11_h__) || defined(__d3d11_x_h__)
		// Direct3D 11 interop
		explicit AViewport(const D3D11_VIEWPORT& vp) :
			x(vp.TopLeftX), y(vp.TopLeftY),
			width(vp.Width), height(vp.Height),
			minDepth(vp.MinDepth), maxDepth(vp.MaxDepth) {}

		operator D3D11_VIEWPORT() { return *reinterpret_cast<const D3D11_VIEWPORT*>(this); }
		const D3D11_VIEWPORT* Get11() const { return reinterpret_cast<const D3D11_VIEWPORT*>(this); }
		AViewport& operator= (const D3D11_VIEWPORT& vp);
#endif

#if defined(__d3d12_h__) || defined(__d3d12_x_h__)
		// Direct3D 12 interop
		explicit AViewport(const D3D12_VIEWPORT& vp) :
			x(vp.TopLeftX), y(vp.TopLeftY),
			width(vp.Width), height(vp.Height),
			minDepth(vp.MinDepth), maxDepth(vp.MaxDepth) {}

		operator D3D12_VIEWPORT() { return *reinterpret_cast<const D3D12_VIEWPORT*>(this); }
		const D3D12_VIEWPORT* Get12() const { return reinterpret_cast<const D3D12_VIEWPORT*>(this); }
		AViewport& operator= (const D3D12_VIEWPORT& vp);
#endif

		AViewport(const AViewport&) = default;
		AViewport& operator=(const AViewport&) = default;

		AViewport(AViewport&&) = default;
		AViewport& operator=(AViewport&&) = default;

		// Comparison operators
		bool operator == (const AViewport& vp) const;
		bool operator != (const AViewport& vp) const;

		// Assignment operators
		AViewport& operator= (const RECT& rct);

		// AViewport operations
		float AspectRatio() const;

		AVector3 Project(const AVector3& p, const AMatrix& proj, const AMatrix& view, const AMatrix& world) const;
		void Project(const AVector3& p, const AMatrix& proj, const AMatrix& view, const AMatrix& world, AVector3& result) const;

		AVector3 Unproject(const AVector3& p, const AMatrix& proj, const AMatrix& view, const AMatrix& world) const;
		void Unproject(const AVector3& p, const AMatrix& proj, const AMatrix& view, const AMatrix& world, AVector3& result) const;

		// Static methods
		static RECT __cdecl ComputeDisplayArea(DXGI_SCALING scaling, UINT backBufferWidth, UINT backBufferHeight, int outputWidth, int outputHeight);
		static RECT __cdecl ComputeTitleSafeArea(UINT backBufferWidth, UINT backBufferHeight);
	};

	
	///////////////////////////////////////// static ///////////////////////////////////////////
	//https://docs.microsoft.com/en-us/windows/win32/dxmath/pg-xnamath-migration-d3dx
	//--------------------------
	// 2D Vector
	//--------------------------

	static float D3DXVec2Length(CONST AVector2 *pV)
	{
		return pV->Length();
	}

	static float D3DXVec2LengthSq(CONST AVector2 *pV)
	{
		return 0.0f;
	}

	static float D3DXVec2Dot(CONST AVector2 *pV1, CONST AVector2 *pV2)
	{
		return 0.0f;
	}

	// Z component of ((x1,y1,0) cross (x2,y2,0))
	static float D3DXVec2CCW(CONST AVector2 *pV1, CONST AVector2 *pV2)
	{
		return 0.0f;
	}

	static AVector2* D3DXVec2Add(AVector2 *pOut, CONST AVector2 *pV1, CONST AVector2 *pV2)
	{
		return pOut;
	}

	static AVector2* D3DXVec2Subtract(AVector2 *pOut, CONST AVector2 *pV1, CONST AVector2 *pV2)
	{
		return pOut;
	}

	// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
	static AVector2* D3DXVec2Minimize(AVector2 *pOut, CONST AVector2 *pV1, CONST AVector2 *pV2)
	{
		return pOut;
	}

	// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
	static AVector2* D3DXVec2Maximize(AVector2 *pOut, CONST AVector2 *pV1, CONST AVector2 *pV2)
	{
		return pOut;
	}

	static AVector2* D3DXVec2Scale(AVector2 *pOut, CONST AVector2 *pV, float s)
	{
		return pOut;
	}

	// Linear interpolation. V1 + s(V2-V1)
	static AVector2* D3DXVec2Lerp(AVector2 *pOut, CONST AVector2 *pV1, CONST AVector2 *pV2,
		float s)
	{
		*pOut = AVector2::Lerp(*pV1, *pV2, s);
		return pOut;
	}
	static AVector2* D3DXVec2Normalize(AVector2 *pOut, CONST AVector2 *pV)
	{
		return pOut;
	}

	// Hermite interpolation between position V1, tangent T1 (when s == 0)
	// and position V2, tangent T2 (when s == 1).
	static AVector2* D3DXVec2Hermite(AVector2 *pOut, CONST AVector2 *pV1, CONST AVector2 *pT1,
		CONST AVector2 *pV2, CONST AVector2 *pT2, float s)
	{
		return pOut;
	}

	// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
	static AVector2* D3DXVec2CatmullRom(AVector2 *pOut, CONST AVector2 *pV0, CONST AVector2 *pV1,
		CONST AVector2 *pV2, CONST AVector2 *pV3, float s)
	{
		return pOut;
	}

	// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
	static AVector2* D3DXVec2BaryCentric(AVector2 *pOut, CONST AVector2 *pV1, CONST AVector2 *pV2,
		CONST AVector2 *pV3, float f, float g)
	{
		return pOut;
	}

	// Transform (x, y, 0, 1) by matrix.
	static AVector4* D3DXVec2Transform(AVector4 *pOut, CONST AVector2 *pV, CONST AMatrix *pM)
	{
		return pOut;
	}

	// Transform (x, y, 0, 1) by matrix, project result back into w=1.
	static AVector2* D3DXVec2TransformCoord(AVector2 *pOut, CONST AVector2 *pV, CONST AMatrix *pM)
	{
		return pOut;
	}

	// Transform (x, y, 0, 0) by matrix.
	static AVector2* D3DXVec2TransformNormal(AVector2 *pOut, CONST AVector2 *pV, CONST AMatrix *pM)
	{
		return pOut;
	}

	// Transform Array (x, y, 0, 1) by matrix.
	static AVector4* D3DXVec2TransformArray(AVector4 *pOut, UINT OutStride, CONST AVector2 *pV, UINT VStride, CONST AMatrix *pM, UINT n)
	{
		return pOut;
	}

	// Transform Array (x, y, 0, 1) by matrix, project result back into w=1.
	static AVector2* D3DXVec2TransformCoordArray(AVector2 *pOut, UINT OutStride, CONST AVector2 *pV, UINT VStride, CONST AMatrix *pM, UINT n)
	{
		return pOut;
	}

	// Transform Array (x, y, 0, 0) by matrix.
	static AVector2* D3DXVec2TransformNormalArray(AVector2 *pOut, UINT OutStride, CONST AVector2 *pV, UINT VStride, CONST AMatrix *pM, UINT n)
	{
		return pOut;
	}
	//--------------------------
	// 3D Vector
	//--------------------------

	static  float D3DXVec3Dot(CONST AVector3 *pV1, CONST AVector3 *pV2)
	{
		return pV1->Dot(*pV2);
	}
	static AVector3* D3DXVec3Cross(AVector3 *pOut, CONST AVector3 *pV1, CONST AVector3 *pV2)
	{
		*pOut = pV1->Cross(*pV2);
		return pOut;
	}
	static AVector3* D3DXVec3Normalize(AVector3 *pOut, CONST AVector3 *pV)
	{
		pV->Normalize(*pOut);
		return pOut;
	}
	static AVector3* D3DXVec3TransformCoord(AVector3 *pOut, CONST AVector3 *pV, CONST AMatrix *pM)
	{
		*pOut = AVector3::Transform(*pV, *pM);
		return pOut;
	}
	static float D3DXVec3Length(CONST AVector3 *pV)
	{
		return pV->Length();
	}



	static float D3DXVec3LengthSq(CONST AVector3 *pV)
	{
		return pV->LengthSquared();
	}


	static AVector3* D3DXVec3Add(AVector3 *pOut, CONST AVector3 *pV1, CONST AVector3 *pV2)
	{
		*pOut = *pV1 + *pV2;
		return pOut;
	}

	static AVector3* D3DXVec3Subtract(AVector3 *pOut, CONST AVector3 *pV1, CONST AVector3 *pV2)
	{
		*pOut = *pV1 - *pV2;
		return pOut;
	}

	// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
	static AVector3* D3DXVec3Minimize(AVector3 *pOut, CONST AVector3 *pV1, CONST AVector3 *pV2) {
	}

	// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
	static AVector3* D3DXVec3Maximize(AVector3 *pOut, CONST AVector3 *pV1, CONST AVector3 *pV2)
	{
		return pOut;
	}

	static AVector3* D3DXVec3Scale(AVector3 *pOut, CONST AVector3 *pV, float s)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(pV);
		XMVECTOR X = XMVectorScale(v1, s);
		AVector3 R;
		XMStoreFloat3(&R, X);
		*pOut = R;
		return pOut;
	}

	// Linear interpolation. V1 + s(V2-V1)
	static AVector3* D3DXVec3Lerp(AVector3 *pOut, CONST AVector3 *pV1, CONST AVector3 *pV2, float s)
	{		
		*pOut = AVector3::Lerp(*pV1, *pV2, s);
		return pOut;
	}


	// Hermite interpolation between position V1, tangent T1 (when s == 0)
	// and position V2, tangent T2 (when s == 1).
	static AVector3* D3DXVec3Hermite(AVector3 *pOut, CONST AVector3 *pV1, CONST AVector3 *pT1,
		CONST AVector3 *pV2, CONST AVector3 *pT2, float s)
	{
		*pOut = AVector3::Hermite(*pV1, *pT1, *pV2, *pT2, s);
		return pOut;
	}

	// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
	static AVector3* D3DXVec3CatmullRom(AVector3 *pOut, CONST AVector3 *pV0, CONST AVector3 *pV1,
		CONST AVector3 *pV2, CONST AVector3 *pV3, float s)
	{
		*pOut = AVector3::CatmullRom(*pV0, *pV1, *pV2, *pV3, s);
		return pOut;
	}

	// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
	static AVector3* D3DXVec3BaryCentric(AVector3 *pOut, CONST AVector3 *pV1, CONST AVector3 *pV2,
		CONST AVector3 *pV3, float f, float g)
	{
		*pOut = AVector3::Barycentric(*pV1, *pV2, *pV3, f, g);
		return pOut;
	}

	// Transform (x, y, z, 1) by matrix.
	static AVector4* D3DXVec3Transform(AVector4 *pOut, CONST AVector3 *pV, CONST AMatrix *pM)
	{
		return pOut;
	}

	// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
	// non-affine matrix, the matrix you pass to this function should be the 
	// transpose of the inverse of the matrix you would use to transform a coord.
	static AVector3* D3DXVec3TransformNormal(AVector3 *pOut, CONST AVector3 *pV, CONST AMatrix *pM)
	{
		*pOut = AVector3::TransformNormal(*pV, *pM);
		return pOut;
	}


	// Transform Array (x, y, z, 1) by matrix. 
	static AVector4* D3DXVec3TransformArray(AVector4 *pOut, UINT OutStride, CONST AVector3 *pV, UINT VStride, CONST AMatrix *pM, UINT n)
	{
		return pOut;
	}

	// Transform Array (x, y, z, 1) by matrix, project result back into w=1.
	static AVector3* D3DXVec3TransformCoordArray(AVector3 *pOut, UINT OutStride, CONST AVector3 *pV, UINT VStride, CONST AMatrix *pM, UINT n)
	{
		return pOut;
	}

	// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
	// non-affine matrix, the matrix you pass to this function should be the 
	// transpose of the inverse of the matrix you would use to transform a coord.
	static AVector3* D3DXVec3TransformNormalArray(AVector3 *pOut, UINT OutStride, CONST AVector3 *pV, UINT VStride, CONST AMatrix *pM, UINT n)
	{
		return pOut;
	}

	// Project vector from object space into screen space
	static AVector3* D3DXVec3Project(AVector3 *pOut, CONST AVector3 *pV, CONST D3D10_VIEWPORT *pViewport,
		CONST AMatrix *pProjection, CONST AMatrix *pView, CONST AMatrix *pWorld)
	{
		//*pOut = AViewporA::Project();
		return pOut;
	}

	// Project vector from screen space into object space
	static AVector3* D3DXVec3Unproject(AVector3 *pOut, CONST AVector3 *pV, CONST D3D10_VIEWPORT *pViewport,
		CONST AMatrix *pProjection, CONST AMatrix *pView, CONST AMatrix *pWorld)
	{
		//*pOut = AViewporA::Unproject();
		return pOut;
	}

	// Project vector Array from object space into screen space
	static AVector3* D3DXVec3ProjectArray(AVector3 *pOut, UINT OutStride, CONST AVector3 *pV, UINT VStride, CONST D3D10_VIEWPORT *pViewport,
		CONST AMatrix *pProjection, CONST AMatrix *pView, CONST AMatrix *pWorld, UINT n)
	{
		return pOut;
	}

	// Project vector Array from screen space into object space
	static AVector3* D3DXVec3UnprojectArray(AVector3 *pOut, UINT OutStride, CONST AVector3 *pV, UINT VStride, CONST D3D10_VIEWPORT *pViewport,
		CONST AMatrix *pProjection, CONST AMatrix *pView, CONST AMatrix *pWorld, UINT n)
	{
		return pOut;
	}

	//--------------------------
	// 4D Vector
	//--------------------------

	static float D3DXVec4Length(CONST AVector4 *pV)
	{
		return pV->Length();
	}


	static float D3DXVec4LengthSq(CONST AVector4 *pV)
	{
		return 0.0f;
	}

	static float D3DXVec4Dot(CONST AVector4 *pV1, CONST AVector4 *pV2)
	{
		return 0.0f;
	}
	static AVector4* D3DXVec4Add(AVector4 *pOut, CONST AVector4 *pV1, CONST AVector4 *pV2)
	{
		return pOut;
	}

	static AVector4* D3DXVec4Subtract(AVector4 *pOut, CONST AVector4 *pV1, CONST AVector4 *pV2)
	{
		return pOut;
	}

	// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
	static AVector4* D3DXVec4Minimize(AVector4 *pOut, CONST AVector4 *pV1, CONST AVector4 *pV2)
	{
		return pOut;
	}

	// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
	static AVector4* D3DXVec4Maximize(AVector4 *pOut, CONST AVector4 *pV1, CONST AVector4 *pV2)
	{
		return pOut;
	}
	static AVector4* D3DXVec4Scale(AVector4 *pOut, CONST AVector4 *pV, float s) {
		return pOut;
	}

	// Linear interpolation. V1 + s(V2-V1)
	static AVector4* D3DXVec4Lerp(AVector4 *pOut, CONST AVector4 *pV1, CONST AVector4 *pV2, float s)
	{
		*pOut = AVector4::Lerp(*pV1, *pV2, s);
		return pOut;
	}

	// Cross-product in 4 dimensions.
	static AVector4* D3DXVec4Cross(AVector4 *pOut, CONST AVector4 *pV1, CONST AVector4 *pV2,
		CONST AVector4 *pV3)
	{
		return pOut;
	}

	static AVector4* D3DXVec4Normalize(AVector4 *pOut, CONST AVector4 *pV)
	{
		return pOut;
	}

	// Hermite interpolation between position V1, tangent T1 (when s == 0)
	// and position V2, tangent T2 (when s == 1).
	static AVector4* D3DXVec4Hermite(AVector4 *pOut, CONST AVector4 *pV1, CONST AVector4 *pT1,
		CONST AVector4 *pV2, CONST AVector4 *pT2, float s)
	{
		return pOut;
	}

	// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
	static AVector4* D3DXVec4CatmullRom(AVector4 *pOut, CONST AVector4 *pV0, CONST AVector4 *pV1,
		CONST AVector4 *pV2, CONST AVector4 *pV3, float s)
	{
		return pOut;
	}

	// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
	static AVector4* D3DXVec4BaryCentric(AVector4 *pOut, CONST AVector4 *pV1, CONST AVector4 *pV2,
		CONST AVector4 *pV3, float f, float g)
	{
		return pOut;
	}

	// Transform vector by matrix.
	static AVector4* D3DXVec4Transform(AVector4 *pOut, CONST AVector4 *pV, CONST AMatrix *pM)
	{
		return pOut;
	}

	// Transform vector array by matrix.
	static AVector4* D3DXVec4TransformArray(AVector4 *pOut, UINT OutStride, CONST AVector4 *pV, UINT VStride, CONST AMatrix *pM, UINT n)
	{
		return pOut;
	}


	static AMatrix* D3DXMatrixIdentity(AMatrix *pOut)
	{
		XMStoreFloat4x4(pOut, XMMatrixIdentity());
		return pOut;
	}
	static AMatrix* D3DXMatrixRotationQuaternion(AMatrix *pOut, CONST AQuaternion *pQ)
	{
		*pOut = AMatrix::CreateFromQuaternion(*pQ);
		return pOut;
	}
	static AQuaternion* D3DXQuaternionRotationMatrix(AQuaternion *pOut, CONST AMatrix *pM)
	{
		*pOut = AQuaternion::CreateFromRotationMatrix(*pM);
		return pOut;
	}

	static float D3DXMatrixDeterminant(CONST AMatrix *pM) {
		return pM->Determinant();
	}

	static HRESULT D3DXMatrixDecompose(AVector3 *pOutScale, AQuaternion *pOutRotation,
		AVector3 *pOutTranslation, AMatrix *pM)
	{
		if (pM->Decompose(*pOutScale, *pOutRotation, *pOutTranslation) == false)
		{
			return S_FALSE;
		}
		return S_OK;
	}

	static AMatrix* D3DXMatrixTranspose(AMatrix *pOut, CONST AMatrix *pM) {

		*pOut = pM->Transpose();
		return pOut;
	}

	// Matrix multiplication.  The result represents the transformation M2
	// followed by the transformation M1.  (Out = M1 * M2)
	static AMatrix*  D3DXMatrixMultiply(AMatrix *pOut, CONST AMatrix *pM1, CONST AMatrix *pM2) {
		*pOut = (*pM1) * (*pM2);
		return pOut;
	}

	// Matrix multiplication, followed by a transpose. (Out = T(M1 * M2))
	static AMatrix*  D3DXMatrixMultiplyTranspose(AMatrix *pOut, CONST AMatrix *pM1, CONST AMatrix *pM2) {

		*pOut = (*pM1) * (*pM2);
		pOut->Transpose();
		return pOut;
	}

	// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
	// be returned.  The determinant of pM is also returned it pfDeterminant
	// is non-NULL.
	static AMatrix*  D3DXMatrixInverse(AMatrix *pOut, float *pDeterminant, CONST AMatrix *pM) {
		pM->Invert(*pOut);
		if (pDeterminant != nullptr)
		{
			*pDeterminant = pM->Determinant();
		}
		return pOut;
	}

	// Build a matrix which scales by (sx, sy, sz)
	static AMatrix*  D3DXMatrixScaling(AMatrix *pOut, float sx, float sy, float sz) {
		*pOut = AMatrix::CreateScale(sx, sy, sz);
		return pOut;
	}

	// Build a matrix which translates by (x, y, z)
	static AMatrix*  D3DXMatrixTranslation(AMatrix *pOut, float x, float y, float z) {
		*pOut = AMatrix::CreateTranslation(x, y, z);
		return pOut;
	}

	// Build a matrix which rotates around the X axis
	static AMatrix*  D3DXMatrixRotationX(AMatrix *pOut, float Angle) {
		*pOut = AMatrix::CreateRotationX(Angle);
		return pOut;
	}

	// Build a matrix which rotates around the Y axis
	static AMatrix*  D3DXMatrixRotationY(AMatrix *pOut, float Angle) {
		*pOut = AMatrix::CreateRotationY(Angle);
		return pOut;
	}

	// Build a matrix which rotates around the Z axis
	static AMatrix*  D3DXMatrixRotationZ(AMatrix *pOut, float Angle) {
		*pOut = AMatrix::CreateRotationZ(Angle);
		return pOut;
	}

	// Build a matrix which rotates around an arbitrary axis
	static AMatrix*  D3DXMatrixRotationAxis(AMatrix *pOut, CONST AVector3 *pV, float Angle) {
		*pOut = AMatrix::CreateFromAxisAngle(*pV, Angle);
		return pOut;
	}

	// Yaw around the Y axis, a pitch around the X axis,
	// and a roll around the Z axis.
	static AMatrix*  D3DXMatrixRotationYawPitchRoll(AMatrix *pOut, float Yaw, float Pitch, float Roll) {
		*pOut = AMatrix::CreateFromYawPitchRoll(Yaw, Pitch, Roll);
		return pOut;
	}

	// Build transformation matrix.  NULL arguments are treated as identity.
	// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
	static AMatrix*  D3DXMatrixTransformation(AMatrix *pOut, CONST AVector3 *pScalingCenter,
		CONST AQuaternion *pScalingRotation, CONST AVector3 *pScaling,
		CONST AVector3 *pRotationCenter, CONST AQuaternion *pRotation,
		CONST AVector3 *pTranslation)
	{
		return pOut;
	}

	// Build 2D transformation matrix in XY plane.  NULL arguments are treated as identity.
	// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
	static AMatrix*  D3DXMatrixTransformation2D(AMatrix *pOut, CONST AVector2* pScalingCenter,
		float ScalingRotation, CONST AVector2* pScaling,
		CONST AVector2* pRotationCenter, float Rotation,
		CONST AVector2* pTranslation) {
		return pOut;
	}

	// Build affine transformation matrix.  NULL arguments are treated as identity.
	// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
	static AMatrix*  D3DXMatrixAffineTransformation(AMatrix *pOut, float Scaling, CONST AVector3 *pRotationCenter,
		CONST AQuaternion *pRotation, CONST AVector3 *pTranslation) 
	{
		XMVECTOR S = XMVectorReplicate(Scaling);//XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		XMVECTOR O = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		if (pRotationCenter != NULL)
		{
			O = DirectX::XMLoadFloat3(pRotationCenter);
		}		
		XMVECTOR P = DirectX::XMLoadFloat3(pTranslation);
		XMVECTOR Q = DirectX::XMLoadFloat4(pRotation);
		*pOut = DirectX::XMMatrixAffineTransformation(S, O, Q, P);
		return pOut;
	}

	// Build 2D affine transformation matrix in XY plane.  NULL arguments are treated as identity.
	// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
	static AMatrix*  D3DXMatrixAffineTransformation2D(AMatrix *pOut, float Scaling, CONST AVector2* pRotationCenter,
		float Rotation, CONST AVector2* pTranslation) {
		return pOut;
	}

	// Build a lookat matrix. (right-handed)
	static AMatrix*  D3DXMatrixLookAtRH(AMatrix *pOut, CONST AVector3 *pEye, CONST AVector3 *pAt, CONST AVector3 *pUp) {
		return pOut;
	}

	// Build a lookat matrix. (left-handed)
	static AMatrix*  D3DXMatrixLookAtLH(AMatrix *pOut, CONST AVector3 *pEye, CONST AVector3 *pAt, CONST AVector3 *pUp) {
		*pOut = AMatrix::CreateLookAt(*pEye, *pAt, *pUp);
		return pOut;
	}

	// Build a perspective projection matrix. (right-handed)
	static AMatrix*  D3DXMatrixPerspectiveRH(AMatrix *pOut, float w, float h, float zn, float zf) {
		return pOut;
	}

	// Build a perspective projection matrix. (left-handed)
	static AMatrix*  D3DXMatrixPerspectiveLH(AMatrix *pOut, float w, float h, float zn, float zf) {
		*pOut = AMatrix::CreatePerspective(w, h, zn, zf);
		return pOut;
	}

	// Build a perspective projection matrix. (right-handed)
	static AMatrix*  D3DXMatrixPerspectiveFovRH(AMatrix *pOut, float fovy, float Aspect, float zn, float zf) 
	{
		using namespace DirectX;		
		XMStoreFloat4x4(pOut, XMMatrixPerspectiveFovRH(fovy, Aspect, zn, zf));
		return pOut;
	}

	// Build a perspective projection matrix. (left-handed)
	static AMatrix*  D3DXMatrixPerspectiveFovLH(AMatrix *pOut, float fovy, float Aspect, float zn, float zf) 
	{
		using namespace DirectX;
		*pOut = AMatrix::CreatePerspectiveFieldOfView(fovy, Aspect, zn, zf);
		return pOut;
	}

	// Build a perspective projection matrix. (right-handed)
	static AMatrix*  D3DXMatrixPerspectiveOffCenterRH(AMatrix *pOut, float l, float r, float b, float t, float zn, float zf) {		
		return pOut;
	}

	// Build a perspective projection matrix. (left-handed)
	static AMatrix*  D3DXMatrixPerspectiveOffCenterLH(AMatrix *pOut, float l, float r, float b, float t, float zn, float zf) {
		*pOut = AMatrix::CreatePerspectiveOffCenter(l, r, b, t, zn, zf);
		return pOut;
	}

	// Build an ortho projection matrix. (right-handed)
	static AMatrix*  D3DXMatrixOrthoRH(AMatrix *pOut, float w, float h, float zn, float zf) {
		return pOut;
	}

	// Build an ortho projection matrix. (left-handed)
	static AMatrix*  D3DXMatrixOrthoLH(AMatrix *pOut, float w, float h, float zn, float zf) {
		*pOut = AMatrix::CreateOrthographic(w, h, zn, zf);
		return pOut;
	}

	// Build an ortho projection matrix. (right-handed)
	static AMatrix*  D3DXMatrixOrthoOffCenterRH(AMatrix *pOut, float l, float r, float b, float t, float zn, float zf) {
		return pOut;
	}

	// Build an ortho projection matrix. (left-handed)
	static AMatrix*  D3DXMatrixOrthoOffCenterLH(AMatrix *pOut, float l, float r, float b, float t, float zn, float zf) {
		*pOut = AMatrix::CreateOrthographicOffCenter(l, r, b, t, zn, zf);
		return pOut;
	}

	// Build a matrix which flattens geometry into a plane, as if casting
	// a shadow from a light.
	static AMatrix*  D3DXMatrixShadow(AMatrix *pOut, CONST AVector4 *pLight, CONST APlane *pPlane) 
	{
		CONST AVector3 pLightLight = AVector3(pLight->x, pLight->y, pLight->z);
		*pOut = AMatrix::CreateShadow(pLightLight, *pPlane);
		return pOut;
	}

	// Build a matrix which reflects the coordinate system about a plane
	static AMatrix*  D3DXMatrixReflect(AMatrix *pOut, CONST APlane *pPlane) {
		*pOut = AMatrix::CreateReflection(*pPlane);
		return pOut;
	}

	//--------------------------
	// Quaternion
	//--------------------------

	// inline

	static float D3DXQuaternionLength(CONST AQuaternion *pQ)
	{
		return pQ->Length();
	};

	// Length squared, or "norm"
	static float D3DXQuaternionLengthSq(CONST AQuaternion *pQ) 
	{
		return pQ->LengthSquared();
	};

	static float D3DXQuaternionDot(CONST AQuaternion *pQ1, CONST AQuaternion *pQ2) 
	{		
		return pQ1->Dot(*pQ2);;
	};

	// (0, 0, 0, 1)
	static AQuaternion* D3DXQuaternionIdentity(AQuaternion *pOut) {
		//*pOut = AQuaternion::Identity;
		XMStoreFloat4(pOut, XMQuaternionIdentity());
		return pOut;
	};

	static BOOL D3DXQuaternionIsIdentity(CONST AQuaternion *pQ) {
		return TRUE;
	};

	// (-x, -y, -z, w)
	static AQuaternion* D3DXQuaternionConjugate(AQuaternion *pOut, CONST AQuaternion *pQ) {
		return pOut;
	};


	// Compute a quaternin's axis and angle of rotation. Expects unit quaternions.
	static void D3DXQuaternionToAxisAngle(CONST AQuaternion *pQ, AVector3 *pAxis, float *pAngle) 
	{
		
	};

	static AQuaternion* D3DXQuaternionRotationAxis(AQuaternion *pOut, CONST AVector3 *pV, FLOAT Angle)
	{
		*pOut = AQuaternion::CreateFromAxisAngle(*pV, Angle);
		return pOut;
	}

	// Yaw around the Y axis, a pitch around the X axis,
	// and a roll around the Z axis.
	static AQuaternion* D3DXQuaternionRotationYawPitchRoll(AQuaternion *pOut, float Yaw, float Pitch, float Roll) 
	{
		*pOut = AQuaternion::CreateFromYawPitchRoll(Yaw,Pitch,Roll);
		return pOut;
	};

	// Quaternion multiplication.  The result represents the rotation Q2
	// followed by the rotation Q1.  (Out = Q2 * Q1)
	static AQuaternion* D3DXQuaternionMultiply(AQuaternion *pOut, CONST AQuaternion *pQ1,
		CONST AQuaternion *pQ2) 
	{
		*pOut = *pQ1 * *pQ2;
		return pOut;
	};

	static AQuaternion* D3DXQuaternionNormalize(AQuaternion *pOut, CONST AQuaternion *pQ)
	{
		*pOut = *pQ;
		pOut->Normalize();
		return pOut;
	};

	// Conjugate and re-norm
	static AQuaternion* D3DXQuaternionInverse(AQuaternion *pOut, CONST AQuaternion *pQ) 
	{
		AQuaternion qRet = *pQ;
		pQ->Inverse(qRet);
		*pOut = qRet;
		return pOut;
	};

	// Expects unit quaternions.
	// if q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
	static AQuaternion* D3DXQuaternionLn(AQuaternion *pOut, CONST AQuaternion *pQ) {
		return pOut;
	};

	// Expects pure quaternions. (w == 0)  w is ignored in calculation.
	// if q = (0, theta * v); exp(q) = (cos(theta), sin(theta) * v)
	static AQuaternion* D3DXQuaternionExp(AQuaternion *pOut, CONST AQuaternion *pQ) {
		return pOut;
	};

	// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
	// Expects unit quaternions.
	static AQuaternion* D3DXQuaternionSlerp(AQuaternion *pOut, CONST AQuaternion *pQ1,	CONST AQuaternion *pQ2, float t) 
	{
		*pOut = AQuaternion::Slerp(*pQ1, *pQ2, t);
		return pOut;
	};

	// Spherical quadrangle interpolation.
	// Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
	static AQuaternion* D3DXQuaternionSquad(AQuaternion *pOut, CONST AQuaternion *pQ1,
		CONST AQuaternion *pA, CONST AQuaternion *pB,
		CONST AQuaternion *pC, float t) {
		return pOut;
	};

	// Setup control points for spherical quadrangle interpolation
	// from Q1 to Q2.  The control points are chosen in such a way 
	// to ensure the continuity of tangents with adjacent segments.
	static void D3DXQuaternionSquadSetup(AQuaternion *pAOut, AQuaternion *pBOut, AQuaternion *pCOut,
		CONST AQuaternion *pQ0, CONST AQuaternion *pQ1,
		CONST AQuaternion *pQ2, CONST AQuaternion *pQ3) {
	};

	// Barycentric interpolation.
	// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
	static AQuaternion* D3DXQuaternionBaryCentric(AQuaternion *pOut, CONST AQuaternion *pQ1,
		CONST AQuaternion *pQ2, CONST AQuaternion *pQ3,
		float f, float g) {
		return pOut;
	};


	//--------------------------
	// Plane
	//--------------------------

	// inline

	// ax + by + cz + dw
	static float D3DXPlaneDot(CONST APlane *pP, CONST AVector4 *pV) {
		return 0.0f;
	};
	// ax + by + cz + d
	static float D3DXPlaneDotCoord(CONST APlane *pP, CONST AVector3 *pV) {
		return 0.0f;
	};
	// ax + by + cz
	static float D3DXPlaneDotNormal(CONST APlane *pP, CONST AVector3 *pV) {
		return 0.0f;
	};
	static APlane* D3DXPlaneScale(APlane *pOut, CONST APlane *pP, float s) {
		return pOut;
	};


	// Normalize plane (so that |a,b,c| == 1)
	static APlane* D3DXPlaneNormalize(APlane *pOut, CONST APlane *pP) {
		return pOut;
	};

	// Find the intersection between a plane and a line.  If the line is
	// parallel to the plane, NULL is returned.
	static AVector3* D3DXPlaneIntersectLine(AVector3 *pOut, CONST APlane *pP, CONST AVector3 *pV1,
		CONST AVector3 *pV2) {
		return pOut;
	};

	// Construct a plane from a point and a normal
	static APlane* D3DXPlaneFromPointNormal(APlane *pOut, CONST AVector3 *pPoint, CONST AVector3 *pNormal) {
		return pOut;
	};

	// Construct a plane from 3 points
	static APlane* D3DXPlaneFromPoints(APlane *pOut, CONST AVector3 *pV1, CONST AVector3 *pV2,
		CONST AVector3 *pV3) {
		return pOut;
	};

	// Transform a plane by a matrix.  The vector (a,b,c) must be normal.
	// M should be the inverse transpose of the transformation desired.
	static APlane* D3DXPlaneTransform(APlane *pOut, CONST APlane *pP, CONST AMatrix *pM) {
		return pOut;
	};
	// Transform an array of planes by a matrix.  The vectors (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
	static APlane* D3DXPlaneTransformArray(APlane *pOut, UINT OutStride, CONST APlane *pP, UINT PStride, CONST AMatrix *pM, UINT n) {
		return pOut;
	};



	//--------------------------
	// Color
	//--------------------------

	// inline

	// (1-r, 1-g, 1-b, a)
	static AColor* D3DXColorNegative(AColor *pOut, CONST AColor *pC) {
		return pOut;
	};

	static AColor* D3DXColorAdd(AColor *pOut, CONST AColor *pC1, CONST AColor *pC2) {
		return pOut;
	};

	static AColor* D3DXColorSubtract(AColor *pOut, CONST AColor *pC1, CONST AColor *pC2) {
		return pOut;
	};

	static AColor* D3DXColorScale(AColor *pOut, CONST AColor *pC, float s) {
		return pOut;
	};

	// (r1*r2, g1*g2, b1*b2, a1*a2)
	static AColor* D3DXColorModulate(AColor *pOut, CONST AColor *pC1, CONST AColor *pC2) {
		return pOut;
	};

	// Linear interpolation of r,g,b, and a. C1 + s(C2-C1)
	static AColor* D3DXColorLerp(AColor *pOut, CONST AColor *pC1, CONST AColor *pC2, float s) {
		return pOut;
	};


	// Interpolate r,g,b between desaturated color and color.
	// DesaturatedColor + s(Color - DesaturatedColor)
	static AColor* D3DXColorAdjustSaturation(AColor *pOut, CONST AColor *pC, float s) {
		return pOut;
	};
	// Interpolate r,g,b between 50% grey and color.  Grey + s(Color - Grey)
	static AColor* D3DXColorAdjustContrast(AColor *pOut, CONST AColor *pC, float c) {
		return pOut;
	};





	//--------------------------
	// Misc
	//--------------------------
		// Calculate Fresnel term given the cosine of theta (likely obtained by
		// taking the dot of two normals), and the refraction index of the material.
	static float D3DXFresnelTerm(float CosTheta, float RefractionIndex)
	{
		return 0.0f;
	};
}

//  ------------------------------------------------------------------------------
// Support for TMath and Standard C++ Library containers
namespace std
{
	template<> struct less<A::ARectangle>
	{
		bool operator()(const A::ARectangle& r1, const A::ARectangle& r2) const
		{
			return ((r1.x < r2.x)
				|| ((r1.x == r2.x) && (r1.y < r2.y))
				|| ((r1.x == r2.x) && (r1.y == r2.y) && (r1.width < r2.width))
				|| ((r1.x == r2.x) && (r1.y == r2.y) && (r1.width == r2.width) && (r1.height < r2.height)));
		}
	};

	template<> struct less<A::AVector2>
	{
		bool operator()(const A::AVector2& V1, const A::AVector2& V2) const
		{
			return ((V1.x < V2.x) || ((V1.x == V2.x) && (V1.y < V2.y)));
		}
	};

	template<> struct less<A::AVector3>
	{
		bool operator()(const A::AVector3& V1, const A::AVector3& V2) const
		{
			return ((V1.x < V2.x)
				|| ((V1.x == V2.x) && (V1.y < V2.y))
				|| ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z < V2.z)));
		}
	};

	template<> struct less<A::AVector4>
	{
		bool operator()(const A::AVector4& V1, const A::AVector4& V2) const
		{
			return ((V1.x < V2.x)
				|| ((V1.x == V2.x) && (V1.y < V2.y))
				|| ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z < V2.z))
				|| ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z == V2.z) && (V1.w < V2.w)));
		}
	};

	template<> struct less<A::AMatrix>
	{
		bool operator()(const A::AMatrix& M1, const A::AMatrix& M2) const
		{
			if (M1._11 != M2._11) return M1._11 < M2._11;
			if (M1._12 != M2._12) return M1._12 < M2._12;
			if (M1._13 != M2._13) return M1._13 < M2._13;
			if (M1._14 != M2._14) return M1._14 < M2._14;
			if (M1._21 != M2._21) return M1._21 < M2._21;
			if (M1._22 != M2._22) return M1._22 < M2._22;
			if (M1._23 != M2._23) return M1._23 < M2._23;
			if (M1._24 != M2._24) return M1._24 < M2._24;
			if (M1._31 != M2._31) return M1._31 < M2._31;
			if (M1._32 != M2._32) return M1._32 < M2._32;
			if (M1._33 != M2._33) return M1._33 < M2._33;
			if (M1._34 != M2._34) return M1._34 < M2._34;
			if (M1._41 != M2._41) return M1._41 < M2._41;
			if (M1._42 != M2._42) return M1._42 < M2._42;
			if (M1._43 != M2._43) return M1._43 < M2._43;
			if (M1._44 != M2._44) return M1._44 < M2._44;

			return false;
		}
	};

	template<> struct less<A::APlane>
	{
		bool operator()(const A::APlane& P1, const A::APlane& P2) const
		{
			return ((P1.x < P2.x)
				|| ((P1.x == P2.x) && (P1.y < P2.y))
				|| ((P1.x == P2.x) && (P1.y == P2.y) && (P1.z < P2.z))
				|| ((P1.x == P2.x) && (P1.y == P2.y) && (P1.z == P2.z) && (P1.w < P2.w)));
		}
	};

	template<> struct less<A::AQuaternion>
	{
		bool operator()(const A::AQuaternion& Q1, const A::AQuaternion& Q2) const
		{
			return ((Q1.x < Q2.x)
				|| ((Q1.x == Q2.x) && (Q1.y < Q2.y))
				|| ((Q1.x == Q2.x) && (Q1.y == Q2.y) && (Q1.z < Q2.z))
				|| ((Q1.x == Q2.x) && (Q1.y == Q2.y) && (Q1.z == Q2.z) && (Q1.w < Q2.w)));
		}
	};

	template<> struct less<A::AColor>
	{
		bool operator()(const A::AColor& C1, const A::AColor& C2) const
		{
			return ((C1.x < C2.x)
				|| ((C1.x == C2.x) && (C1.y < C2.y))
				|| ((C1.x == C2.x) && (C1.y == C2.y) && (C1.z < C2.z))
				|| ((C1.x == C2.x) && (C1.y == C2.y) && (C1.z == C2.z) && (C1.w < C2.w)));
		}
	};

	template<> struct less<A::ARay>
	{
		bool operator()(const A::ARay& R1, const A::ARay& R2) const
		{
			if (R1.position.x != R2.position.x) return R1.position.x < R2.position.x;
			if (R1.position.y != R2.position.y) return R1.position.y < R2.position.y;
			if (R1.position.z != R2.position.z) return R1.position.z < R2.position.z;

			if (R1.direction.x != R2.direction.x) return R1.direction.x < R2.direction.x;
			if (R1.direction.y != R2.direction.y) return R1.direction.y < R2.direction.y;
			if (R1.direction.z != R2.direction.z) return R1.direction.z < R2.direction.z;

			return false;
		}
	};

	template<> struct less<A::AViewport>
	{
		bool operator()(const A::AViewport& vp1, const A::AViewport& vp2) const
		{
			if (vp1.x != vp2.x) return (vp1.x < vp2.x);
			if (vp1.y != vp2.y) return (vp1.y < vp2.y);

			if (vp1.width != vp2.width) return (vp1.width < vp2.width);
			if (vp1.height != vp2.height) return (vp1.height < vp2.height);

			if (vp1.minDepth != vp2.minDepth) return (vp1.minDepth < vp2.minDepth);
			if (vp1.maxDepth != vp2.maxDepth) return (vp1.maxDepth < vp2.maxDepth);

			return false;
		}
	};


};
using namespace A;
