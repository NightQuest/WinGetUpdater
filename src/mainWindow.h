#pragma once

class mainWindow : public Window
{
public:
	mainWindow() = delete;
	mainWindow(const std::wstring& className);
	~mainWindow() override;

	// Event overrides
	LRESULT onCreate(LPCREATESTRUCT lpCreate) override;
	LRESULT onDestroy() override;
	LRESULT onClose() override;

	// Implimentation of pure virtuals
	bool create(const std::wstring& title, uint32_t width, uint32_t height) override;

private:
	std::wstring className;
	uint32_t windowWidth;
	uint32_t windowHeight;
};
