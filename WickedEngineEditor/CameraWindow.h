#pragma once

struct Material;
class wiGUI;
class wiWindow;
class wiLabel;
class wiCheckBox;
class wiSlider;

class CameraWindow
{
public:
	CameraWindow(wiGUI* gui);
	~CameraWindow();

	wiGUI* GUI;

	wiWindow* cameraWindow;
	wiSlider* farPlaneSlider;
	wiSlider* nearPlaneSlider;
	wiSlider* fovSlider;
	wiButton* resetButton;
};

