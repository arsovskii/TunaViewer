#include "MainPage.h"

#include "../Window.h"
#include "imgui/imgui.h"

#include <portable-file-dialogs.h>

MainPage::MainPage(Window* window)
{
	mWindow = window;
}

MainPage::~MainPage()
{
}

void MainPage::draw()
{
	ImGui::Begin("Hello, world!");

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Create"))
			{
			}
			if (ImGui::MenuItem("Open", "Ctrl+O"))
			{
				openFileDialog();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
			}
			if (ImGui::MenuItem("Save as.."))
			{
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}


	static int counter = 0;

	if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / mWindow->getIO().Framerate,
	            mWindow->getIO().Framerate);
	ImGui::End();
	ImGui::Render();
}

void MainPage::openFileDialog()
{
	auto f = pfd::open_file("Choose files to read", pfd::path::home(),
	                        {
		                        "Image Files", "*.jpg, *.jpeg, *.png",
		                        "All Files", "*"
	                        },
	                        pfd::opt::none
	);

	std::cout << "Selected files:";
	for (auto const& name : f.result())
		std::cout << " " + name;
	std::cout << "\n";

	mWindow->changeImage(f.result().at(0));
	

}
