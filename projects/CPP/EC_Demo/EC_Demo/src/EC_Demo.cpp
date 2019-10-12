// internal code
#include "Application.hpp"

int main()
{
	std::unique_ptr<Application> app = std::make_unique<Application>();
	app->Run();
}

