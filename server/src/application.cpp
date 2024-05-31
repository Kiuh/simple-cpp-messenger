#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <iterator>
#include <algorithm>

namespace server
{
	class Application
	{
	public:
		void run()
		{
			using namespace boost::lambda;
			typedef std::istream_iterator<int> in;

			std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " ");
		}
	};
}