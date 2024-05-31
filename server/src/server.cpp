#include "application.cpp"

using namespace server;

int main()
{
	auto app = new Application();
	app->run();
	return 0;
}
