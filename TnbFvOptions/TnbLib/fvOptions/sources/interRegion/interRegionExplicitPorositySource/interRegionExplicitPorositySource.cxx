#include <interRegionExplicitPorositySource.hxx>

#include <fvMesh.hxx>
#include <fvMatrices.hxx>
#include <porosityModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(interRegionExplicitPorositySource, 0);
		addToRunTimeSelectionTable
		(
			option,
			interRegionExplicitPorositySource,
			dictionary
		);
	}
}

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::fv::interRegionExplicitPorositySource::initialise()
{
	if (!firstIter_)
	{
		return;
	}

	const word zoneName(name_ + ":porous");

	const fvMesh& nbrMesh = mesh_.time().lookupObject<fvMesh>(nbrRegionName_);
	const cellZoneMesh& cellZones = nbrMesh.cellZones();
	label zoneID = cellZones.findZoneID(zoneName);

	if (zoneID == -1)
	{
		cellZoneMesh& cz = const_cast<cellZoneMesh&>(cellZones);

		zoneID = cz.size();

		cz.setSize(zoneID + 1);

		cz.set
		(
			zoneID,
			new cellZone
			(
				zoneName,
				nbrMesh.faceNeighbour(), // Neighbour internal cells
				zoneID,
				cellZones
			)
		);

		cz.clearAddressing();
	}
	else
	{
		FatalErrorInFunction
			<< "Unable to create porous cellZone " << zoneName
			<< ": zone already exists"
			<< abort(FatalError);
	}

	porosityPtr_.reset
	(
		porosityModel::New
		(
			name_,
			nbrMesh,
			coeffs_,
			zoneName
		).ptr()
	),

		firstIter_ = false;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::interRegionExplicitPorositySource::interRegionExplicitPorositySource
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	interRegionOption(name, modelType, dict, mesh),
	porosityPtr_(nullptr),
	firstIter_(true),
	UName_(coeffs_.lookupOrDefault<word>("U", "U")),
	muName_(coeffs_.lookupOrDefault<word>("mu", "thermo:mu"))
{
	if (active_)
	{
		fieldNames_.setSize(1, UName_);
		applied_.setSize(1, false);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::interRegionExplicitPorositySource::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	initialise();

	const fvMesh& nbrMesh = mesh_.time().lookupObject<fvMesh>(nbrRegionName_);

	const volVectorField& U = eqn.psi();

	volVectorField UNbr
	(
		IOobject
		(
			name_ + ":UNbr",
			nbrMesh.time().timeName(),
			nbrMesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		nbrMesh,
		dimensionedVector(U.dimensions(), Zero)
	);

	// Map local velocity onto neighbour region
	meshInterp().mapSrcToTgt
	(
		U.primitiveField(),
		plusEqOp<vector>(),
		UNbr.primitiveFieldRef()
	);

	fvMatrix<vector> nbrEqn(UNbr, eqn.dimensions());

	porosityPtr_->addResistance(nbrEqn);

	// Convert source from neighbour to local region
	fvMatrix<vector> porosityEqn(U, eqn.dimensions());
	scalarField& Udiag = porosityEqn.diag();
	vectorField& Usource = porosityEqn.source();

	Udiag.setSize(eqn.diag().size(), 0.0);
	Usource.setSize(eqn.source().size(), Zero);

	meshInterp().mapTgtToSrc(nbrEqn.diag(), plusEqOp<scalar>(), Udiag);
	meshInterp().mapTgtToSrc(nbrEqn.source(), plusEqOp<vector>(), Usource);

	eqn -= porosityEqn;
}


void tnbLib::fv::interRegionExplicitPorositySource::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	initialise();

	const fvMesh& nbrMesh = mesh_.time().lookupObject<fvMesh>(nbrRegionName_);

	const volVectorField& U = eqn.psi();

	volVectorField UNbr
	(
		IOobject
		(
			name_ + ":UNbr",
			nbrMesh.time().timeName(),
			nbrMesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		nbrMesh,
		dimensionedVector(U.dimensions(), Zero)
	);

	// Map local velocity onto neighbour region
	meshInterp().mapSrcToTgt
	(
		U.primitiveField(),
		plusEqOp<vector>(),
		UNbr.primitiveFieldRef()
	);

	fvMatrix<vector> nbrEqn(UNbr, eqn.dimensions());

	volScalarField rhoNbr
	(
		IOobject
		(
			"rho:UNbr",
			nbrMesh.time().timeName(),
			nbrMesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		nbrMesh,
		dimensionedScalar(dimDensity, 0)
	);

	volScalarField muNbr
	(
		IOobject
		(
			"mu:UNbr",
			nbrMesh.time().timeName(),
			nbrMesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		nbrMesh,
		dimensionedScalar(dimViscosity, 0)
	);

	const volScalarField& mu =
		mesh_.lookupObject<volScalarField>(muName_);

	// Map local rho onto neighbour region
	meshInterp().mapSrcToTgt
	(
		rho.primitiveField(),
		plusEqOp<scalar>(),
		rhoNbr.primitiveFieldRef()
	);

	// Map local mu onto neighbour region
	meshInterp().mapSrcToTgt
	(
		mu.primitiveField(),
		plusEqOp<scalar>(),
		muNbr.primitiveFieldRef()
	);

	porosityPtr_->addResistance(nbrEqn, rhoNbr, muNbr);

	// Convert source from neighbour to local region
	fvMatrix<vector> porosityEqn(U, eqn.dimensions());
	scalarField& Udiag = porosityEqn.diag();
	vectorField& Usource = porosityEqn.source();

	Udiag.setSize(eqn.diag().size(), 0.0);
	Usource.setSize(eqn.source().size(), Zero);

	meshInterp().mapTgtToSrc(nbrEqn.diag(), plusEqOp<scalar>(), Udiag);
	meshInterp().mapTgtToSrc(nbrEqn.source(), plusEqOp<vector>(), Usource);

	eqn -= porosityEqn;
}


bool tnbLib::fv::interRegionExplicitPorositySource::read(const dictionary& dict)
{
	if (interRegionOption::read(dict))
	{
		coeffs_.readIfPresent("U", UName_);
		coeffs_.readIfPresent("mu", muName_);

		// Reset the porosity model?

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //