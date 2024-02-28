#include "MainPage.h"

#include "../Window.h"
#include "imgui/imgui.h"

MainPage::MainPage()
{
}

MainPage::~MainPage()
{
}

void MainPage::draw(Window* window)
{
	ImGui::Begin("Hello, world!");
	static int counter = 0;

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / window->getIO().Framerate, window->getIO().Framerate);
	ImGui::End();
	ImGui::Render();

}
