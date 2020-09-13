#include <TurbulenceModelTemplate.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template
<
	class Alpha,
	class Rho,
	class BasicTurbulenceModel,
	class TransportModel
>
tnbLib::TurbulenceModel<Alpha, Rho, BasicTurbulenceModel, TransportModel>::
TurbulenceModel
(
	const alphaField& alpha,
	const rhoField& rho,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const transportModel& transport,
	const word& propertiesName
)
	:
	BasicTurbulenceModel
	(
		rho,
		U,
		alphaRhoPhi,
		phi,
		propertiesName
	),
	alpha_(alpha),
	transport_(transport)
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

template
<
	class Alpha,
	class Rho,
	class BasicTurbulenceModel,
	class TransportModel
>
tnbLib::autoPtr
<
	tnbLib::TurbulenceModel<Alpha, Rho, BasicTurbulenceModel, TransportModel>
>
tnbLib::TurbulenceModel<Alpha, Rho, BasicTurbulenceModel, TransportModel>::New
(
	const alphaField& alpha,
	const rhoField& rho,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const transportModel& transport,
	const word& propertiesName
)
{
	// get model name, but do not register the dictionary
	// otherwise it is registered in the database twice
	const word modelType
	(
		IOdictionary
		(
			IOobject
			(
				IOobject::groupName(propertiesName, alphaRhoPhi.group()),
				U.time().constant(),
				U.db(),
				IOobject::MUST_READ_IF_MODIFIED,
				IOobject::NO_WRITE,
				false
			)
		).lookup("simulationType")
	);

	Info << "Selecting turbulence model type " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown TurbulenceModel type "
			<< modelType << nl << nl
			<< "Valid TurbulenceModel types:" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<TurbulenceModel>
		(
			cstrIter()(alpha, rho, U, alphaRhoPhi, phi, transport, propertiesName)
			);
}


// ************************************************************************* //