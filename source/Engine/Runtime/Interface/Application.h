#include "Engine/Runtime/Interface/IApplication.h"
#include "Engine/Runtime/DebugConsole.h"

class Application : public IApplication
{
protected:
	Engine::DebugConsole* console;

	Application() = default;
	virtual ~Application() = default;
};