#include "stdafx.h"
#include "CameraWindow.h"

void ResetCam()
{
	wiRenderer::getCamera()->Clear();
	wiRenderer::getCamera()->Translate(XMFLOAT3(0, 2, -10));
}

CameraWindow::CameraWindow(wiGUI* gui) :GUI(gui)
{
	assert(GUI && "Invalid GUI!");

	float screenW = (float)wiRenderer::GetDevice()->GetScreenWidth();
	float screenH = (float)wiRenderer::GetDevice()->GetScreenHeight();


	cameraWindow = new wiWindow(GUI, "Camera Window");
	cameraWindow->SetSize(XMFLOAT2(400, 300));
	GUI->AddWidget(cameraWindow);

	float x = 200;
	float y = 0;
	float inc = 35;

	farPlaneSlider = new wiSlider(1, 5000, 1000, 100000, "Far Plane: ");
	farPlaneSlider->SetSize(XMFLOAT2(100, 30));
	farPlaneSlider->SetPos(XMFLOAT2(x, y += inc));
	farPlaneSlider->OnSlide([&](wiEventArgs args) {
		wiRenderer::getCamera()->zFarP = args.fValue;
		wiRenderer::getCamera()->UpdateProjection();
	});
	cameraWindow->AddWidget(farPlaneSlider);

	nearPlaneSlider = new wiSlider(0.01f, 10, 0.1f, 10000, "Near Plane: ");
	nearPlaneSlider->SetSize(XMFLOAT2(100, 30));
	nearPlaneSlider->SetPos(XMFLOAT2(x, y += inc));
	nearPlaneSlider->OnSlide([&](wiEventArgs args) {
		wiRenderer::getCamera()->zNearP = args.fValue;
		wiRenderer::getCamera()->UpdateProjection();
	});
	cameraWindow->AddWidget(nearPlaneSlider);

	fovSlider = new wiSlider(1, 179, 60, 10000, "FOV: ");
	fovSlider->SetSize(XMFLOAT2(100, 30));
	fovSlider->SetPos(XMFLOAT2(x, y += inc));
	fovSlider->OnSlide([&](wiEventArgs args) {
		wiRenderer::getCamera()->fov = args.fValue / 180.f * XM_PI;
		wiRenderer::getCamera()->UpdateProjection();
	});
	cameraWindow->AddWidget(fovSlider);

	resetButton = new wiButton("Reset Pos");
	fovSlider->SetSize(XMFLOAT2(80, 30));
	resetButton->SetPos(XMFLOAT2(x, y += inc));
	resetButton->OnClick([&](wiEventArgs args) {
		ResetCam();
	});
	cameraWindow->AddWidget(resetButton);



	cameraWindow->Translate(XMFLOAT3(30, 30, 0));
	cameraWindow->SetVisible(false);

	ResetCam();
}


CameraWindow::~CameraWindow()
{
	SAFE_DELETE(cameraWindow);
	SAFE_DELETE(farPlaneSlider);
	SAFE_DELETE(nearPlaneSlider);
	SAFE_DELETE(fovSlider);
}
