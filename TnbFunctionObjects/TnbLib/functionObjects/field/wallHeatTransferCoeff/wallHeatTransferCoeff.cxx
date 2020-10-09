#include <wallHeatTransferCoeff.hxx>

#include <turbulentTransportModel.hxx>
#include <wallPolyPatch.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(wallHeatTransferCoeff, 0);
		addToRunTimeSelectionTable
		(
			functionObject,
			wallHeatTransferCoeff,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::functionObjects::wallHeatTransferCoeff::writeFileHeader
(
	const label i
)
{
	// Add headers to output data
	writeHeader(file(), "Wall heat transfer coefficient");
	writeCommented(file(), "Time");
	writeTabbed(file(), "patch");
	writeTabbed(file(), "min");
	writeTabbed(file(), "max");
	writeTabbed(file(), "integral");
	file() << endl;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::functionObjects::wallHeatTransferCoeff::calcHeatTransferCoeff
(
	const volScalarField& nu,
	const volScalarField& nut
)
{
	tmp<volScalarField> twallHeatTransferCoeff
	(
		volScalarField::New
		(
			type(),
			mesh_,
			dimensionedScalar
			(
				dimMass / pow3(dimTime) / (dimTemperature / dimLength),
				0
			)
		)
	);

	volScalarField::Boundary& wallHeatTransferCoeffBf =
		twallHeatTransferCoeff.ref().boundaryFieldRef();

	const volScalarField::Boundary& nuBf = nu.boundaryField();
	const volScalarField::Boundary& nutBf = nut.boundaryField();

	forAll(wallHeatTransferCoeffBf, patchi)
	{
		if (!wallHeatTransferCoeffBf[patchi].coupled())
		{
			wallHeatTransferCoeffBf[patchi] =
				rho_ * Cp_*(nuBf[patchi] / Prl_ + nutBf[patchi] / Prt_);
		}
	}

	return twallHeatTransferCoeff;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::wallHeatTransferCoeff::wallHeatTransferCoeff
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	logFiles(obr_, name),
	writeLocalObjects(obr_, log),
	patchSet_()
{
	read(dict);
	resetName(typeName);
	resetLocalObjectName(typeName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::wallHeatTransferCoeff::~wallHeatTransferCoeff()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::wallHeatTransferCoeff::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);
	writeLocalObjects::read(dict);

	const polyBoundaryMesh& pbm = mesh_.boundaryMesh();

	patchSet_ =
		mesh_.boundaryMesh().patchSet
		(
			wordReList(dict.lookupOrDefault("patches", wordReList()))
		);

	Info << type() << " " << name() << ":" << nl;

	if (patchSet_.empty())
	{
		forAll(pbm, patchi)
		{
			if (isA<wallPolyPatch>(pbm[patchi]))
			{
				patchSet_.insert(patchi);
			}
		}

		Info << "    processing all wall patches" << nl << endl;
	}
	else
	{
		Info << "    processing wall patches: " << nl;
		labelHashSet filteredPatchSet;
		forAllConstIter(labelHashSet, patchSet_, iter)
		{
			label patchi = iter.key();
			if (isA<wallPolyPatch>(pbm[patchi]))
			{
				filteredPatchSet.insert(patchi);
				Info << "        " << pbm[patchi].name() << endl;
			}
			else
			{
				WarningInFunction
					<< "Requested wall heat-transferCoeff on non-wall boundary "
					<< "type patch: " << pbm[patchi].name() << endl;
			}
		}

		Info << endl;

		patchSet_ = filteredPatchSet;
	}

	dict.lookup("rho") >> rho_;
	dict.lookup("Cp") >> Cp_;
	dict.lookup("Prl") >> Prl_;
	dict.lookup("Prt") >> Prt_;

	return true;
}


bool tnbLib::functionObjects::wallHeatTransferCoeff::execute()
{
	word name(type());

	if
		(
			foundObject<incompressible::turbulenceModel>
			(
				turbulenceModel::propertiesName
				)
			)
	{
		const incompressible::turbulenceModel& turbModel =
			lookupObject<incompressible::turbulenceModel>
			(
				turbulenceModel::propertiesName
				);

		return store
		(
			name,
			calcHeatTransferCoeff(turbModel.nu(), turbModel.nut())
		);
	}
	else
	{
		FatalErrorInFunction
			<< "Unable to find incompressible turbulence model in the "
			<< "database" << exit(FatalError);

		return false;
	}
}


bool tnbLib::functionObjects::wallHeatTransferCoeff::write()
{
	TnbLog << type() << " " << name() << " write:" << nl;

	writeLocalObjects::write();

	logFiles::write();

	const volScalarField& wallHeatTransferCoeff =
		obr_.lookupObject<volScalarField>(type());

	const fvPatchList& patches = mesh_.boundary();

	const surfaceScalarField::Boundary& magSf =
		mesh_.magSf().boundaryField();

	forAllConstIter(labelHashSet, patchSet_, iter)
	{
		label patchi = iter.key();
		const fvPatch& pp = patches[patchi];

		const scalarField& hfp = wallHeatTransferCoeff.boundaryField()[patchi];

		const scalar minHtcp = gMin(hfp);
		const scalar maxHtcp = gMax(hfp);
		const scalar integralHtcp = gSum(magSf[patchi] * hfp);

		if (Pstream::master())
		{
			file()
				<< mesh_.time().value()
				<< tab << pp.name()
				<< tab << minHtcp
				<< tab << maxHtcp
				<< tab << integralHtcp
				<< endl;
		}

		TnbLog << "    min/max/integ(" << pp.name() << ") = "
			<< minHtcp << ", " << maxHtcp << ", " << integralHtcp << endl;
	}

	TnbLog << endl;

	return true;
}


// ************************************************************************* //