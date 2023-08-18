#include <Novice.h>
#include "LineRaySegment.h"
#include "Sphere.h"
#include "Matrix4x4.h"
#include "AffineMatrixFunctions.h"
#include "MatrixFunctions.h"
#include "RenderingPipelineFunctions.h"
#include "VectorFanctions.h"
#include "DrawSphereAndGrid.h"
#include "LineToPointCollision.h"
#include "imgui.h"
#include "SphereCollision.h"
#include "stdint.h"
#include "Plane.h"
#include "DrawPlane.h"
#include "PlaneCollision.h"
#include "LineToPlaneCollision.h"
#include "Triangle.h"
#include "TriangleToLineCollosion.h"
#include "AABB.h"
#include "AABBToAABBCollision.h"
#include "AABBToSphereCollision.h"

AffineMatrixFunctions amf_;
MatrixFunctions mf_;
RenderingPipelineFunctions rpf_;
VectorFanctions vf_;
DrawSphereAndGrid dsag_;
LineToPointCollision ltpc_;
SphereCollision sc_;
DrawPlane dp_;
PlaneCollision pc_;
LineToPlaneCollision lpc_;
TriangleToLineCollosion ttc_;
AABBToAABBCollision atac_;
AABBToSphereCollision atsc_;

const char kWindowTitle[] = "LD2A";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Segment segment{ {-0.01f,0.8f,-2.0f},{0.01f,0.5f,2.0f} };
	Vector3 point{ -0.0f,0.0f,0.0f };
	Vector3 closestPoint{ 0,0,0 };


	AABB aabb1{ .min{-0.5,-0.5,-0.5,},.Max{0.0f,0.0f,0.0f} };
	AABB aabb2{ .min{-0.5,-0.5,-0.5,},.Max{0.0f,0.0f,0.0f} };

	Sphere Sphere1{ point,0.5f };
	Sphere Sphere2{ closestPoint,0.8f };
	Plane plane{ {1.0f,0.1f,0.0f},0.4f };
	Triangle triangle{};
	triangle.vertices[0] = { -1.0f,0.01f,0.01f };
	triangle.vertices[1] = { 0.01f,1.0f,0.01f };
	triangle.vertices[2] = { 1.0f,0.01f,0.01f };

	uint32_t color = 0xFFFFFFFF;
	Vector3 CameraPosition = { 0.0f,1.9f,-6.49f };
	Vector3 CameraRotate = { 0.26f,0.0f,0.0f };
	Vector3 Scale_ = { 1.0f,1.0f,1.0f };
	Vector3 Rotate_ = {};
	Vector3 Translate_ = {};
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		if (atsc_.IsCollision(aabb1, Sphere1)) {
			color = 0xFF0000FF;
		}
		else {
			color = 0xFFFFFFFF;
		}
		ImGui::Begin("Window");
		ImGui::DragFloat3("AABB.min", &aabb1.min.x, 0.01f);
		ImGui::DragFloat3("AABB.Min", &aabb1.Max.x, 0.01f);
		ImGui::DragFloat3("Sphere.Center", &Sphere1.center.x, 0.01f);
		ImGui::DragFloat("Sphere.Rad", &Sphere1.radius, 0.01f);
		ImGui::End();

		Matrix4x4 worldMatrix = amf_.MakeAffinMatrix(amf_.MakeScaleMatrix(Scale_), amf_.MakeRotateMatrix(Rotate_), amf_.MakeTranslateMatrix(Translate_));
		Matrix4x4 cameraMatrix = amf_.MakeAffinMatrix(amf_.MakeScaleMatrix({ 1.0f,1.0f,1.0f }), amf_.MakeRotateMatrix(CameraRotate), amf_.MakeTranslateMatrix(CameraPosition));
		Matrix4x4 viewMatrix = mf_.Inverse(cameraMatrix);
		Matrix4x4 ProjectionMatrix = rpf_.MakePerspectiveFovMatrix(0.45f, 1280.0f / 720.0f, 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = mf_.Multiply(worldMatrix, mf_.Multiply(viewMatrix, ProjectionMatrix));
		Matrix4x4 viewPortMatrix = rpf_.MakeViewportMatrix(0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 0.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		dsag_.DrawGrid(worldViewProjectionMatrix, viewPortMatrix);
		dsag_.DrwaSphere(Sphere1, worldViewProjectionMatrix, viewPortMatrix,WHITE);
		atac_.Draw(aabb1, worldViewProjectionMatrix, viewPortMatrix, color);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
