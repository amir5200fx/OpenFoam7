#include <test.hxx>

#include <jobInfo.hxx>

using namespace tnbLib;

int main(int argc, char *argv[])
{
	jobInfo_.perform();

	tnbLib::Test_dimensionedType();

	return 0;
}