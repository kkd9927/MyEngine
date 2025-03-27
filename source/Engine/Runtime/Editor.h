#pragma once

#include "Engine/Runtime/Interface/Application.h"

class Editor final : public Application
{
public:
	virtual void run() override;

	Editor() = default;
	~Editor() = default;
};