#include "pch_client.h"
#include "CViewUI.h"

CViewUI::CViewUI()
	: Super("ViewUI", "##ViewUI")
{
}

CViewUI::~CViewUI()
{
}

void CViewUI::SetWindowOption()
{
}

void CViewUI::Render_Update()
{
	// Guizmo
	ImGuizmo::SetOrthographic(true);

	// View
	Ptr<CTexture> pViewTex = M_RENDER->GetPostProcessTex();
	ID3D11ShaderResourceView* pSRV = pViewTex->GetSRV().Get();
	Vec2 v2Resolution = GRAPHICS->GetResolution();
	ImGui::Image(pSRV, ImVec2(v2Resolution.x, v2Resolution.y));


	static const float identityMatrix[16] =
	{ 1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f };

	ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	//ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::ROTATE;
	//ImGuizmo::OPERATION mCurrentGizmoOperation = ImGuizmo::SCALE;

	ImGuizmo::MODE mCurrentGizmoMode = ImGuizmo::LOCAL;
	//ImGuizmo::MODE mCurrentGizmoMode = ImGuizmo::WORLD;

	CLevel* pCurLevel = M_LEVEL->GetCurrentLevel();

	CGameObject* pCamObj = pCurLevel->FindObjectByName(L"MainCamera");
	CCamera* pCamComp = pCamObj->Camera();
	Matrix cameraView = pCamComp->GetViewMatrix();
	Matrix cameraProjection = pCamComp->GetProjMatrix();

	CGameObject* pPlayerObj = pCurLevel->FindObjectByName(L"PlayerObj");
	CTransform* pTransform = pPlayerObj->Transform();
	Matrix matrix = pTransform->GetLocalMatrix();
	
	bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };
	static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	static bool boundSizing = false;
	static bool boundSizingSnap = false;


	ImGuizmo::SetDrawlist();
	float windowWidth = (float)ImGui::GetWindowWidth();
	float windowHeight = (float)ImGui::GetWindowHeight();
	ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
	ImGuizmo::DrawGrid(&cameraView._11, &cameraProjection._11, identityMatrix, 100.f);
	ImGuizmo::Manipulate(&cameraView._11,
		&cameraProjection._11,
		mCurrentGizmoOperation,
		mCurrentGizmoMode,
		&matrix._11,
		NULL,
		useSnap ? &snap[0] : NULL,
		boundSizing ? bounds : NULL,
		boundSizingSnap ? boundsSnap : NULL);

	float matrixTranslation[3] = {};
	float matrixRotation[3] = {};
	float matrixScale[3] = {};
	ImGuizmo::DecomposeMatrixToComponents(&matrix._11, matrixTranslation, matrixRotation, matrixScale);

	pTransform->SetLocalScale(Vec3(matrixScale[0], matrixScale[1], matrixScale[2]));
	pTransform->SetLocalRotation(Vec3(matrixRotation[0], matrixRotation[1], matrixRotation[2]));
	pTransform->SetLocalPos(Vec3(matrixTranslation[0], matrixTranslation[1], matrixTranslation[2]));
}
