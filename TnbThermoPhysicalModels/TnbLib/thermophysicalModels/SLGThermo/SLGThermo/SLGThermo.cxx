#include <SLGThermo.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(SLGThermo, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::SLGThermo::SLGThermo(const fvMesh& mesh, fluidThermo& thermo)
	:
	regIOobject
	(
		IOobject
		(
			SLGThermo::typeName,
			mesh.polyMesh::instance(),
			mesh
		)
	),
	thermo_(thermo),
	carrier_(nullptr),
	liquids_(nullptr),
	solids_(nullptr)
{
	Info << "Creating component thermo properties:" << endl;

	if (isA<basicSpecieMixture>(thermo))
	{
		basicSpecieMixture& mcThermo =
			dynamic_cast<basicSpecieMixture&>(thermo);
		carrier_ = &mcThermo;

		Info << "    multi-component carrier - " << mcThermo.species().size()
			<< " species" << endl;
	}
	else
	{
		Info << "    single component carrier" << endl;
	}

	if (thermo.found("liquids"))
	{
		liquids_ = liquidMixtureProperties::New(thermo.subDict("liquids"));
		Info << "    liquids - " << liquids_->components().size()
			<< " components" << endl;
	}
	else
	{
		Info << "    no liquid components" << endl;
	}

	if (thermo.found("solids"))
	{
		solids_ = solidMixtureProperties::New(thermo.subDict("solids"));
		Info << "    solids - " << solids_->components().size()
			<< " components" << endl;
	}
	else
	{
		Info << "    no solid components" << endl;
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::SLGThermo::~SLGThermo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::fluidThermo& tnbLib::SLGThermo::thermo() const
{
	return thermo_;
}


const tnbLib::basicSpecieMixture& tnbLib::SLGThermo::carrier() const
{
	if (carrier_ == nullptr)
	{
		FatalErrorInFunction
			<< "carrier requested, but object is not allocated"
			<< abort(FatalError);
	}

	return *carrier_;
}


const tnbLib::liquidMixtureProperties& tnbLib::SLGThermo::liquids() const
{
	if (!liquids_.valid())
	{
		FatalErrorInFunction
			<< "liquids requested, but object is not allocated"
			<< abort(FatalError);
	}

	return liquids_();
}


const tnbLib::solidMixtureProperties& tnbLib::SLGThermo::solids() const
{
	if (!solids_.valid())
	{
		FatalErrorInFunction
			<< "solids requested, but object is not allocated"
			<< abort(FatalError);
	}

	return solids_();
}


tnbLib::label tnbLib::SLGThermo::carrierId
(
	const word& cmptName,
	bool allowNotfound
) const
{
	forAll(carrier().species(), i)
	{
		if (cmptName == carrier_->species()[i])
		{
			return i;
		}
	}

	if (!allowNotfound)
	{
		FatalErrorInFunction
			<< "Unknown carrier component " << cmptName
			<< ". Valid carrier components are:" << nl
			<< carrier_->species() << exit(FatalError);
	}

	return -1;
}


tnbLib::label tnbLib::SLGThermo::liquidId
(
	const word& cmptName,
	bool allowNotfound
) const
{
	forAll(liquids().components(), i)
	{
		if (cmptName == liquids_->components()[i])
		{
			return i;
		}
	}

	if (!allowNotfound)
	{
		FatalErrorInFunction
			<< "Unknown liquid component " << cmptName << ". Valid liquids are:"
			<< nl << liquids_->components() << exit(FatalError);
	}

	return -1;
}


tnbLib::label tnbLib::SLGThermo::solidId
(
	const word& cmptName,
	bool allowNotfound
) const
{
	forAll(solids().components(), i)
	{
		if (cmptName == solids_->components()[i])
		{
			return i;
		}
	}

	if (!allowNotfound)
	{
		FatalErrorInFunction
			<< "Unknown solid component " << cmptName << ". Valid solids are:"
			<< nl << solids_->components() << exit(FatalError);
	}

	return -1;
}


bool tnbLib::SLGThermo::hasMultiComponentCarrier() const
{
	return (carrier_ != nullptr);
}


bool tnbLib::SLGThermo::hasLiquids() const
{
	return liquids_.valid();
}


bool tnbLib::SLGThermo::hasSolids() const
{
	return solids_.valid();
}


// ************************************************************************* //