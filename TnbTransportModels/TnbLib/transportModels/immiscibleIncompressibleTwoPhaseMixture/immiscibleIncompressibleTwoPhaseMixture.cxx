#include <immiscibleIncompressibleTwoPhaseMixture.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::immiscibleIncompressibleTwoPhaseMixture::
immiscibleIncompressibleTwoPhaseMixture
(
	const volVectorField& U,
	const surfaceScalarField& phi
)
	:
	incompressibleTwoPhaseMixture(U, phi),
	interfaceProperties(alpha1(), U, *this)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::immiscibleIncompressibleTwoPhaseMixture::read()
{
	return
		incompressibleTwoPhaseMixture::read()
		&& interfaceProperties::read();
}


// ************************************************************************* //