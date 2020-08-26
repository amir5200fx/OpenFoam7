#include <DarcyForchheimer.hxx>

#include <geometricOneField.hxx>
#include <fvMatrices.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace porosityModels
	{
		defineTypeNameAndDebug(DarcyForchheimer, 0);
		addToRunTimeSelectionTable(porosityModel, DarcyForchheimer, mesh);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::porosityModels::DarcyForchheimer::DarcyForchheimer
(
	const word& name,
	const word& modelType,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& cellZoneName
)
	:
	porosityModel(name, modelType, mesh, dict, cellZoneName),
	dXYZ_("d", dimless / sqr(dimLength), coeffs_),
	fXYZ_("f", dimless / dimLength, coeffs_),
	D_(cellZoneIDs_.size()),
	F_(cellZoneIDs_.size()),
	rhoName_(coeffs_.lookupOrDefault<word>("rho", "rho")),
	muName_(coeffs_.lookupOrDefault<word>("mu", "thermo:mu")),
	nuName_(coeffs_.lookupOrDefault<word>("nu", "nu"))
{
	adjustNegativeResistance(dXYZ_);
	adjustNegativeResistance(fXYZ_);

	calcTransformModelData();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::porosityModels::DarcyForchheimer::~DarcyForchheimer()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::porosityModels::DarcyForchheimer::calcTransformModelData()
{
	if (coordSys_.R().uniform())
	{
		forAll(cellZoneIDs_, zoneI)
		{
			D_[zoneI].setSize(1);
			F_[zoneI].setSize(1);

			D_[zoneI][0] = Zero;
			D_[zoneI][0].xx() = dXYZ_.value().x();
			D_[zoneI][0].yy() = dXYZ_.value().y();
			D_[zoneI][0].zz() = dXYZ_.value().z();

			D_[zoneI][0] = coordSys_.R().transformTensor(D_[zoneI][0]);

			// leading 0.5 is from 1/2*rho
			F_[zoneI][0] = Zero;
			F_[zoneI][0].xx() = 0.5*fXYZ_.value().x();
			F_[zoneI][0].yy() = 0.5*fXYZ_.value().y();
			F_[zoneI][0].zz() = 0.5*fXYZ_.value().z();

			F_[zoneI][0] = coordSys_.R().transformTensor(F_[zoneI][0]);
		}
	}
	else
	{
		forAll(cellZoneIDs_, zoneI)
		{
			const labelList& cells = mesh_.cellZones()[cellZoneIDs_[zoneI]];

			D_[zoneI].setSize(cells.size());
			F_[zoneI].setSize(cells.size());

			forAll(cells, i)
			{
				D_[zoneI][i] = Zero;
				D_[zoneI][i].xx() = dXYZ_.value().x();
				D_[zoneI][i].yy() = dXYZ_.value().y();
				D_[zoneI][i].zz() = dXYZ_.value().z();

				// leading 0.5 is from 1/2*rho
				F_[zoneI][i] = Zero;
				F_[zoneI][i].xx() = 0.5*fXYZ_.value().x();
				F_[zoneI][i].yy() = 0.5*fXYZ_.value().y();
				F_[zoneI][i].zz() = 0.5*fXYZ_.value().z();
			}

			const coordinateRotation& R = coordSys_.R(mesh_, cells);

			D_[zoneI] = R.transformTensor(D_[zoneI], cells);
			F_[zoneI] = R.transformTensor(F_[zoneI], cells);
		}
	}

	if (debug && mesh_.time().writeTime())
	{
		volTensorField Dout
		(
			IOobject
			(
				typeName + ":D",
				mesh_.time().timeName(),
				mesh_,
				IOobject::NO_READ,
				IOobject::NO_WRITE
			),
			mesh_,
			dimensionedTensor(dXYZ_.dimensions(), Zero)
		);
		volTensorField Fout
		(
			IOobject
			(
				typeName + ":F",
				mesh_.time().timeName(),
				mesh_,
				IOobject::NO_READ,
				IOobject::NO_WRITE
			),
			mesh_,
			dimensionedTensor(fXYZ_.dimensions(), Zero)
		);

		UIndirectList<tensor>(Dout, mesh_.cellZones()[cellZoneIDs_[0]]) = D_[0];
		UIndirectList<tensor>(Fout, mesh_.cellZones()[cellZoneIDs_[0]]) = F_[0];

		Dout.write();
		Fout.write();
	}
}


void tnbLib::porosityModels::DarcyForchheimer::calcForce
(
	const volVectorField& U,
	const volScalarField& rho,
	const volScalarField& mu,
	vectorField& force
) const
{
	scalarField Udiag(U.size(), 0.0);
	vectorField Usource(U.size(), Zero);
	const scalarField& V = mesh_.V();

	apply(Udiag, Usource, V, rho, mu, U);

	force = Udiag * U - Usource;
}


void tnbLib::porosityModels::DarcyForchheimer::correct
(
	fvVectorMatrix& UEqn
) const
{
	const volVectorField& U = UEqn.psi();
	const scalarField& V = mesh_.V();
	scalarField& Udiag = UEqn.diag();
	vectorField& Usource = UEqn.source();

	word rhoName(IOobject::groupName(rhoName_, U.group()));
	word muName(IOobject::groupName(muName_, U.group()));
	word nuName(IOobject::groupName(nuName_, U.group()));

	if (UEqn.dimensions() == dimForce)
	{
		const volScalarField& rho = mesh_.lookupObject<volScalarField>(rhoName);

		if (mesh_.foundObject<volScalarField>(muName))
		{
			const volScalarField& mu =
				mesh_.lookupObject<volScalarField>(muName);

			apply(Udiag, Usource, V, rho, mu, U);
		}
		else
		{
			const volScalarField& nu =
				mesh_.lookupObject<volScalarField>(nuName);

			apply(Udiag, Usource, V, rho, rho*nu, U);
		}
	}
	else
	{
		if (mesh_.foundObject<volScalarField>(nuName))
		{
			const volScalarField& nu =
				mesh_.lookupObject<volScalarField>(nuName);

			apply(Udiag, Usource, V, geometricOneField(), nu, U);
		}
		else
		{
			const volScalarField& rho =
				mesh_.lookupObject<volScalarField>(rhoName);
			const volScalarField& mu =
				mesh_.lookupObject<volScalarField>(muName);

			apply(Udiag, Usource, V, geometricOneField(), mu / rho, U);
		}
	}
}


void tnbLib::porosityModels::DarcyForchheimer::correct
(
	fvVectorMatrix& UEqn,
	const volScalarField& rho,
	const volScalarField& mu
) const
{
	const vectorField& U = UEqn.psi();
	const scalarField& V = mesh_.V();
	scalarField& Udiag = UEqn.diag();
	vectorField& Usource = UEqn.source();

	apply(Udiag, Usource, V, rho, mu, U);
}


void tnbLib::porosityModels::DarcyForchheimer::correct
(
	const fvVectorMatrix& UEqn,
	volTensorField& AU
) const
{
	const volVectorField& U = UEqn.psi();

	word rhoName(IOobject::groupName(rhoName_, U.group()));
	word muName(IOobject::groupName(muName_, U.group()));
	word nuName(IOobject::groupName(nuName_, U.group()));

	if (UEqn.dimensions() == dimForce)
	{
		const volScalarField& rho = mesh_.lookupObject<volScalarField>(rhoName);
		const volScalarField& mu = mesh_.lookupObject<volScalarField>(muName);

		apply(AU, rho, mu, U);
	}
	else
	{
		if (mesh_.foundObject<volScalarField>(nuName))
		{
			const volScalarField& nu =
				mesh_.lookupObject<volScalarField>(nuName);

			apply(AU, geometricOneField(), nu, U);
		}
		else
		{
			const volScalarField& rho =
				mesh_.lookupObject<volScalarField>(rhoName);
			const volScalarField& mu =
				mesh_.lookupObject<volScalarField>(muName);

			apply(AU, geometricOneField(), mu / rho, U);
		}
	}
}


bool tnbLib::porosityModels::DarcyForchheimer::writeData(Ostream& os) const
{
	os << indent << name_ << endl;
	dict_.write(os);

	return true;
}


// ************************************************************************* //