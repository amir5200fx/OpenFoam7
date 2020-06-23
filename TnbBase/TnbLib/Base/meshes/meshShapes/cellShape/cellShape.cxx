#include <cellShape.hxx>

#include <degenerateMatcher.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::cellShape::collapse()
{
	operator=(degenerateMatcher::match(*this));
}


// ************************************************************************* //