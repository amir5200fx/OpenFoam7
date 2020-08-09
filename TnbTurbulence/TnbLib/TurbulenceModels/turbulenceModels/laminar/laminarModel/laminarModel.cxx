#include <laminarModel.hxx>

#include <Stokes.hxx>

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class BasicTurbulenceModel>
void tnbLib::laminarModel<BasicTurbulenceModel>::printCoeffs(const word& type)
{
	if (printCoeffs_)
	{
		Info << coeffDict_.dictName() << coeffDict_ << endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::laminarModel<BasicTurbulenceModel>::laminarModel
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

	laminarDict_(this->subOrEmptyDict("laminar")),
	printCoeffs_(laminarDict_.lookupOrDefault<Switch>("printCoeffs", false)),
	coeffDict_(laminarDict_.optionalSubDict(type + "Coeffs"))
{
	// Force the construction of the mesh deltaCoeffs which may be needed
	// for the construction of the derived models and BCs
	this->mesh_.deltaCoeffs();
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::autoPtr<tnbLib::laminarModel<BasicTurbulenceModel>>
tnbLib::laminarModel<BasicTurbulenceModel>::New
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
	IOdictionary modelDict
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
	);

	if (modelDict.found("laminar"))
	{
		// get model name, but do not register the dictionary
		// otherwise it is registered in the database twice
		const word modelType
		(
			modelDict.subDict("laminar").lookup("laminarModel")
		);

		Info << "Selecting laminar stress model " << modelType << endl;

		typename dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->find(modelType);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown laminarModel type "
				<< modelType << nl << nl
				<< "Valid laminarModel types:" << endl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return autoPtr<laminarModel>
			(
				cstrIter()
				(
					alpha,
					rho,
					U,
					alphaRhoPhi,
					phi,
					transport, propertiesName)
				);
	}
	else
	{
		Info << "Selecting laminar stress model "
			<< laminarModels::Stokes<BasicTurbulenceModel>::typeName << endl;

		return autoPtr<laminarModel>
			(
				new laminarModels::Stokes<BasicTurbulenceModel>
				(
					alpha,
					rho,
					U,
					alphaRhoPhi,
					phi,
					transport,
					propertiesName
					)
				);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
bool tnbLib::laminarModel<BasicTurbulenceModel>::read()
{
	if (BasicTurbulenceModel::read())
	{
		laminarDict_ <<= this->subDict("laminar");

		coeffDict_ <<= laminarDict_.optionalSubDict(type() + "Coeffs");

		return true;
	}
	else
	{
		return false;
	}
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarModel<BasicTurbulenceModel>::nut() const
{
	return volScalarField::New
	(
		IOobject::groupName("nut", this->alphaRhoPhi_.group()),
		this->mesh_,
		dimensionedScalar(dimViscosity, 0)
	);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::laminarModel<BasicTurbulenceModel>::nut
(
	const label patchi
) const
{
	return tmp<scalarField>
		(
			new scalarField(this->mesh_.boundary()[patchi].size(), 0.0)
			);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarModel<BasicTurbulenceModel>::nuEff() const
{
	return volScalarField::New
	(
		IOobject::groupName("nuEff", this->alphaRhoPhi_.group()),
		this->nu()
	);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::laminarModel<BasicTurbulenceModel>::nuEff
(
	const label patchi
) const
{
	return this->nu(patchi);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarModel<BasicTurbulenceModel>::k() const
{
	return volScalarField::New
	(
		IOobject::groupName("k", this->alphaRhoPhi_.group()),
		this->mesh_,
		dimensionedScalar(sqr(this->U_.dimensions()), 0)
	);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarModel<BasicTurbulenceModel>::epsilon() const
{
	return volScalarField::New
	(
		IOobject::groupName("epsilon", this->alphaRhoPhi_.group()),
		this->mesh_,
		dimensionedScalar(sqr(this->U_.dimensions()) / dimTime, 0)
	);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::laminarModel<BasicTurbulenceModel>::R() const
{
	return volSymmTensorField::New
	(
		IOobject::groupName("R", this->alphaRhoPhi_.group()),
		this->mesh_,
		dimensionedSymmTensor(sqr(this->U_.dimensions()), Zero)
	);
}


template<class BasicTurbulenceModel>
void tnbLib::laminarModel<BasicTurbulenceModel>::correct()
{
	BasicTurbulenceModel::correct();
}


// ************************************************************************* //