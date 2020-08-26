#include <porosityModel.hxx>

#include <volFields.hxx>
#include <PstreamReduceOps.hxx>  // added by amir
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(porosityModel, 0);
	defineRunTimeSelectionTable(porosityModel, mesh);
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::porosityModel::adjustNegativeResistance(dimensionedVector& resist)
{
	scalar maxCmpt = cmptMax(resist.value());

	if (maxCmpt < 0)
	{
		FatalErrorInFunction
			<< "Cannot have all resistances set to negative, resistance = "
			<< resist
			<< exit(FatalError);
	}
	else
	{
		maxCmpt = max(0, maxCmpt);
		vector& val = resist.value();
		for (label cmpt = 0; cmpt < vector::nComponents; cmpt++)
		{
			if (val[cmpt] < 0)
			{
				val[cmpt] *= -maxCmpt;
			}
		}
	}
}


tnbLib::label tnbLib::porosityModel::fieldIndex(const label i) const
{
	label index = 0;
	if (!coordSys_.R().uniform())
	{
		index = i;
	}
	return index;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::porosityModel::porosityModel
(
	const word& name,
	const word& modelType,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& cellZoneName
)
	:
	regIOobject
	(
		IOobject
		(
			name,
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		)
	),
	name_(name),
	mesh_(mesh),
	dict_(dict),
	coeffs_(dict.optionalSubDict(modelType + "Coeffs")),
	active_(true),
	zoneName_(cellZoneName),
	cellZoneIDs_(),
	coordSys_(coordinateSystem::New(mesh, coeffs_))
{
	if (zoneName_ == word::null)
	{
		dict.readIfPresent("active", active_);
		dict_.lookup("cellZone") >> zoneName_;
	}

	cellZoneIDs_ = mesh_.cellZones().findIndices(zoneName_);

	Info << "    creating porous zone: " << zoneName_ << endl;

	bool foundZone = !cellZoneIDs_.empty();
	reduce(foundZone, orOp<bool>());

	if (!foundZone && Pstream::master())
	{
		FatalErrorInFunction
			<< "cannot find porous cellZone " << zoneName_
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::porosityModel::~porosityModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::porosityModel::transformModelData()
{
	if (!mesh_.upToDatePoints(*this))
	{
		calcTransformModelData();

		// set model up-to-date wrt points
		mesh_.setUpToDatePoints(*this);
	}
}


tnbLib::tmp<tnbLib::vectorField> tnbLib::porosityModel::porosityModel::force
(
	const volVectorField& U,
	const volScalarField& rho,
	const volScalarField& mu
)
{
	transformModelData();

	tmp<vectorField> tforce(new vectorField(U.size(), Zero));

	if (!cellZoneIDs_.empty())
	{
		this->calcForce(U, rho, mu, tforce.ref());
	}

	return tforce;
}


void tnbLib::porosityModel::addResistance(fvVectorMatrix& UEqn)
{
	if (cellZoneIDs_.empty())
	{
		return;
	}

	transformModelData();
	this->correct(UEqn);
}


void tnbLib::porosityModel::addResistance
(
	fvVectorMatrix& UEqn,
	const volScalarField& rho,
	const volScalarField& mu
)
{
	if (cellZoneIDs_.empty())
	{
		return;
	}

	transformModelData();
	this->correct(UEqn, rho, mu);
}


void tnbLib::porosityModel::addResistance
(
	const fvVectorMatrix& UEqn,
	volTensorField& AU,
	bool correctAUprocBC
)
{
	if (cellZoneIDs_.empty())
	{
		return;
	}

	transformModelData();
	this->correct(UEqn, AU);

	if (correctAUprocBC)
	{
		// Correct the boundary conditions of the tensorial diagonal to ensure
		// processor boundaries are correctly handled when AU^-1 is interpolated
		// for the pressure equation.
		AU.correctBoundaryConditions();
	}
}


bool tnbLib::porosityModel::writeData(Ostream& os) const
{
	return true;
}


bool tnbLib::porosityModel::read(const dictionary& dict)
{
	dict.readIfPresent("active", active_);

	coeffs_ = dict.optionalSubDict(type() + "Coeffs");

	dict.lookup("cellZone") >> zoneName_;
	cellZoneIDs_ = mesh_.cellZones().findIndices(zoneName_);

	return true;
}


// ************************************************************************* //