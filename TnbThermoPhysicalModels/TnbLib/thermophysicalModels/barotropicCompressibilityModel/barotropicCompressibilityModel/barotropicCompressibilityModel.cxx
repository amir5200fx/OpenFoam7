#include <barotropicCompressibilityModel.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(barotropicCompressibilityModel, 0);
	defineRunTimeSelectionTable(barotropicCompressibilityModel, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::barotropicCompressibilityModel::barotropicCompressibilityModel
(
	const dictionary& compressibilityProperties,
	const volScalarField& gamma,
	const word& psiName
)
	:
	compressibilityProperties_(compressibilityProperties),
	psi_
	(
		IOobject
		(
			psiName,
			gamma.mesh().time().timeName(),
			gamma.mesh()
		),
		gamma.mesh(),
		dimensionedScalar(psiName, dimensionSet(0, -2, 2, 0, 0), 0)
	),
	gamma_(gamma)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::barotropicCompressibilityModel::read
(
	const dictionary& compressibilityProperties
)
{
	compressibilityProperties_ = compressibilityProperties;

	return true;
}


// ************************************************************************* //