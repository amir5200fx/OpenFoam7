#include <RASModel.hxx>

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class BasicTurbulenceModel>
void tnbLib::RASModel<BasicTurbulenceModel>::printCoeffs(const word& type)
{
	if (printCoeffs_)
	{
		Info << coeffDict_.dictName() << coeffDict_ << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::RASModel<BasicTurbulenceModel>::RASModel
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

	RASDict_(this->subOrEmptyDict("RAS")),
	turbulence_(RASDict_.lookup("turbulence")),
	printCoeffs_(RASDict_.lookupOrDefault<Switch>("printCoeffs", false)),
	coeffDict_(RASDict_.optionalSubDict(type + "Coeffs")),

	kMin_
	(
		dimensioned<scalar>::lookupOrAddToDict
		(
			"kMin",
			RASDict_,
			sqr(dimVelocity),
			small
		)
	),

	epsilonMin_
	(
		dimensioned<scalar>::lookupOrAddToDict
		(
			"epsilonMin",
			RASDict_,
			kMin_.dimensions() / dimTime,
			small
		)
	),

	omegaMin_
	(
		dimensioned<scalar>::lookupOrAddToDict
		(
			"omegaMin",
			RASDict_,
			dimless / dimTime,
			small
		)
	)
{
	// Force the construction of the mesh deltaCoeffs which may be needed
	// for the construction of the derived models and BCs
	this->mesh_.deltaCoeffs();
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::autoPtr<tnbLib::RASModel<BasicTurbulenceModel>>
tnbLib::RASModel<BasicTurbulenceModel>::New
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
		).subDict("RAS").lookup("RASModel")
	);

	Info << "Selecting RAS turbulence model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown RASModel type "
			<< modelType << nl << nl
			<< "Valid RASModel types:" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<RASModel>
		(
			cstrIter()(alpha, rho, U, alphaRhoPhi, phi, transport, propertiesName)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
bool tnbLib::RASModel<BasicTurbulenceModel>::read()
{
	if (BasicTurbulenceModel::read())
	{
		RASDict_ <<= this->subDict("RAS");
		RASDict_.lookup("turbulence") >> turbulence_;

		coeffDict_ <<= RASDict_.optionalSubDict(type() + "Coeffs");

		kMin_.readIfPresent(RASDict_);
		epsilonMin_.readIfPresent(RASDict_);
		omegaMin_.readIfPresent(RASDict_);

		return true;
	}
	else
	{
		return false;
	}
}


template<class BasicTurbulenceModel>
void tnbLib::RASModel<BasicTurbulenceModel>::correct()
{
	BasicTurbulenceModel::correct();
}


// ************************************************************************* //