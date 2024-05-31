#include "application.cpp"

using namespace server;

int main()
{
	Application *app = new Application();
	app->run();
	return 0;
}
