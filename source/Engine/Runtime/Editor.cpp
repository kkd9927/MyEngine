#include "Engine/Runtime/Editor.h"

#include "Engine/Render/Renderer.h"
#include "Engine/Camera/Camera.h"

void Editor::run()
{
	Engine::Renderer& renderer = Engine::Renderer::GetInstance(); // 렌더러 생성과 동시에 OpenGL 초기화
	Engine::Camera mainCamera(0.f, 0.f, 0.f);
	renderer.SetCurrentCamera(mainCamera);
	
	while (!renderer.ShouldAPIClose())
	{
		renderer.DrawCall();
	}

	renderer.Close();
}