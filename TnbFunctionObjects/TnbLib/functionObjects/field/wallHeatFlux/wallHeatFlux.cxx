#include <wallHeatFlux.hxx>

#include <turbulentFluidThermoModel.hxx>
#include <solidThermo.hxx>
#include <surfaceInterpolate.hxx>
#include <fvcSnGrad.hxx>
#include <wallPolyPatch.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(wallHeatFlux, 0);
		addToRunTimeSelectionTable(functionObject, wallHeatFlux, dictionary);
	}
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::functionObjects::wallHeatFlux::writeFileHeader(const label i)
{
	// Add headers to output data
	writeHeader(file(), "Wall heat-flux");
	writeCommented(file(), "Time");
	writeTabbed(file(), "patch");
	writeTabbed(file(), "min");
	writeTabbed(file(), "max");
	writeTabbed(file(), "integral");
	file() << endl;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::functionObjects::wallHeatFlux::calcWallHeatFlux
(
	const volScalarField& alpha,
	const volScalarField& he
)
{
	tmp<volScalarField> twallHeatFlux
	(
		volScalarField::New
		(
			type(),
			mesh_,
			dimensionedScalar(dimMass / pow3(dimTime), 0)
		)
	);

	volScalarField::Boundary& wallHeatFluxBf =
		twallHeatFlux.ref().boundaryFieldRef();

	const volScalarField::Boundary& heBf =
		he.boundaryField();

	const volScalarField::Boundary& alphaBf =
		alpha.boundaryField();

	forAll(wallHeatFluxBf, patchi)
	{
		if (!wallHeatFluxBf[patchi].coupled())
		{
			wallHeatFluxBf[patchi] = alphaBf[patchi] * heBf[patchi].snGrad();
		}
	}

	if (foundObject<volScalarField>("qr"))
	{
		const volScalarField& qr = lookupObject<volScalarField>("qr");

		const volScalarField::Boundary& radHeatFluxBf =
			qr.boundaryField();

		forAll(wallHeatFluxBf, patchi)
		{
			if (!wallHeatFluxBf[patchi].coupled())
			{
				wallHeatFluxBf[patchi] -= radHeatFluxBf[patchi];
			}
		}
	}

	return twallHeatFlux;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::wallHeatFlux::wallHeatFlux
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

tnbLib::functionObjects::wallHeatFlux::~wallHeatFlux()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::wallHeatFlux::read(const dictionary& dict)
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
					<< "Requested wall heat-flux on non-wall boundary "
					<< "type patch: " << pbm[patchi].name() << endl;
			}
		}

		Info << endl;

		patchSet_ = filteredPatchSet;
	}

	return true;
}


bool tnbLib::functionObjects::wallHeatFlux::execute()
{
	word name(type());

	if
		(
			foundObject<compressible::turbulenceModel>
			(
				turbulenceModel::propertiesName
				)
			)
	{
		const compressible::turbulenceModel& turbModel =
			lookupObject<compressible::turbulenceModel>
			(
				turbulenceModel::propertiesName
				);

		return store
		(
			name,
			calcWallHeatFlux(turbModel.alphaEff(), turbModel.transport().he())
		);
	}
	else if (foundObject<solidThermo>(solidThermo::dictName))
	{
		const solidThermo& thermo =
			lookupObject<solidThermo>(solidThermo::dictName);

		return store(name, calcWallHeatFlux(thermo.alpha(), thermo.he()));
	}
	else
	{
		FatalErrorInFunction
			<< "Unable to find compressible turbulence model in the "
			<< "database" << exit(FatalError);
	}

	return true;
}


bool tnbLib::functionObjects::wallHeatFlux::write()
{
	TnbLog << type() << " " << name() << " write:" << nl;

	writeLocalObjects::write();

	logFiles::write();

	const volScalarField& wallHeatFlux =
		obr_.lookupObject<volScalarField>(type());

	const fvPatchList& patches = mesh_.boundary();

	const surfaceScalarField::Boundary& magSf =
		mesh_.magSf().boundaryField();

	forAllConstIter(labelHashSet, patchSet_, iter)
	{
		label patchi = iter.key();
		const fvPatch& pp = patches[patchi];

		const scalarField& hfp = wallHeatFlux.boundaryField()[patchi];

		const scalar minHfp = gMin(hfp);
		const scalar maxHfp = gMax(hfp);
		const scalar integralHfp = gSum(magSf[patchi] * hfp);

		if (Pstream::master())
		{
			file()
				<< mesh_.time().value()
				<< tab << pp.name()
				<< tab << minHfp
				<< tab << maxHfp
				<< tab << integralHfp
				<< endl;
		}

		TnbLog << "    min/max/integ(" << pp.name() << ") = "
			<< minHfp << ", " << maxHfp << ", " << integralHfp << endl;
	}

	TnbLog << endl;

	return true;
}


// ************************************************************************* //