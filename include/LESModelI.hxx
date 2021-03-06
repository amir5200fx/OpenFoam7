#pragma once
#include <surfaceMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir

#include <Time.hxx>  // added by amir
#include <fvsPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class BasicTurbulenceModel>
void tnbLib::LESModel<BasicTurbulenceModel>::printCoeffs(const word& type)
{
	if (printCoeffs_)
	{
		Info << coeffDict_.dictName() << coeffDict_ << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::LESModel<BasicTurbulenceModel>::LESModel
(
	const word& type,
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
		type,
		alpha,
		rho,
		U,
		alphaRhoPhi,
		phi,
		transport,
		propertiesName
	),

	LESDict_(this->subOrEmptyDict("LES")),
	turbulence_(LESDict_.lookup("turbulence")),
	printCoeffs_(LESDict_.lookupOrDefault<Switch>("printCoeffs", false)),
	coeffDict_(LESDict_.optionalSubDict(type + "Coeffs")),

	kMin_
	(
		dimensioned<scalar>::lookupOrAddToDict
		(
			"kMin",
			LESDict_,
			sqr(dimVelocity),
			small
		)
	),

	epsilonMin_
	(
		dimensioned<scalar>::lookupOrAddToDict
		(
			"epsilonMin",
			LESDict_,
			kMin_.dimensions() / dimTime,
			small
		)
	),

	omegaMin_
	(
		dimensioned<scalar>::lookupOrAddToDict
		(
			"omegaMin",
			LESDict_,
			dimless / dimTime,
			small
		)
	),

	delta_
	(
		LESdelta::New
		(
			IOobject::groupName("delta", alphaRhoPhi.group()),
			*this,
			LESDict_
		)
	)
{
	// Force the construction of the mesh deltaCoeffs which may be needed
	// for the construction of the derived models and BCs
	this->mesh_.deltaCoeffs();
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::autoPtr<tnbLib::LESModel<BasicTurbulenceModel>>
tnbLib::LESModel<BasicTurbulenceModel>::New
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
		).subDict("LES").lookup("LESModel")
	);

	Info << "Selecting LES turbulence model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown LESModel type "
			<< modelType << nl << nl
			<< "Valid LESModel types:" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<LESModel>
		(
			cstrIter()(alpha, rho, U, alphaRhoPhi, phi, transport, propertiesName)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
bool tnbLib::LESModel<BasicTurbulenceModel>::read()
{
	if (BasicTurbulenceModel::read())
	{
		LESDict_ <<= this->subDict("LES");
		LESDict_.lookup("turbulence") >> turbulence_;

		coeffDict_ <<= LESDict_.optionalSubDict(type() + "Coeffs");

		delta_().read(LESDict_);

		kMin_.readIfPresent(LESDict_);

		return true;
	}
	else
	{
		return false;
	}
}


template<class BasicTurbulenceModel>
void tnbLib::LESModel<BasicTurbulenceModel>::correct()
{
	delta_().correct();
	BasicTurbulenceModel::correct();
}


// ************************************************************************* //