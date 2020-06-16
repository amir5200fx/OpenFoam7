#include <intersection.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::intersection::planarTol_ = 0.2;

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::intersection::direction,
		2
		>::names[] =
	{
		"vector",
		"contactSphere"
	};

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::intersection::algorithm,
		3
		>::names[] =
	{
		"fullRay",
		"halfRay",
		"visible"
	};
}

const tnbLib::NamedEnum<tnbLib::intersection::direction, 2>
tnbLib::intersection::directionNames_;

const tnbLib::NamedEnum<tnbLib::intersection::algorithm, 3>
tnbLib::intersection::algorithmNames_;


// ************************************************************************* //