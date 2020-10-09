#include <wallShearStress.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <turbulentTransportModel.hxx>
#include <turbulentFluidThermoModel.hxx>
#include <wallPolyPatch.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(wallShearStress, 0);
		addToRunTimeSelectionTable(functionObject, wallShearStress, dictionary);
	}
}


// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

void tnbLib::functionObjects::wallShearStress::writeFileHeader(const label i)
{
	// Add headers to output data
	writeHeader(file(), "Wall shear stress");
	writeCommented(file(), "Time");
	writeTabbed(file(), "patch");
	writeTabbed(file(), "min");
	writeTabbed(file(), "max");
	file() << endl;
}


tnbLib::tmp<tnbLib::volVectorField>
tnbLib::functionObjects::wallShearStress::calcShearStress
(
	const volSymmTensorField& Reff
)
{
	tmp<volVectorField> twallShearStress
	(
		volVectorField::New
		(
			type(),
			mesh_,
			dimensionedVector(Reff.dimensions(), Zero)
		)
	);

	volVectorField::Boundary& wallShearStressBf =
		twallShearStress.ref().boundaryFieldRef();

	forAllConstIter(labelHashSet, patchSet_, iter)
	{
		label patchi = iter.key();

		const vectorField& Sfp = mesh_.Sf().boundaryField()[patchi];
		const scalarField& magSfp = mesh_.magSf().boundaryField()[patchi];
		const symmTensorField& Reffp = Reff.boundaryField()[patchi];

		wallShearStressBf[patchi] = (-Sfp / magSfp) & Reffp;
	}

	return twallShearStress;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::wallShearStress::wallShearStress
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

tnbLib::functionObjects::wallShearStress::~wallShearStress()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::wallShearStress::read(const dictionary& dict)
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
					<< "Requested wall shear stress on non-wall boundary "
					<< "type patch: " << pbm[patchi].name() << endl;
			}
		}

		Info << endl;

		patchSet_ = filteredPatchSet;
	}

	return true;
}


bool tnbLib::functionObjects::wallShearStress::execute()
{
	typedef compressible::turbulenceModel cmpModel;
	typedef incompressible::turbulenceModel icoModel;

	tmp<volSymmTensorField> Reff;
	if (mesh_.foundObject<cmpModel>(turbulenceModel::propertiesName))
	{
		const cmpModel& model =
			mesh_.lookupObject<cmpModel>(turbulenceModel::propertiesName);

		Reff = model.devRhoReff();
	}
	else if (mesh_.foundObject<icoModel>(turbulenceModel::propertiesName))
	{
		const icoModel& model =
			mesh_.lookupObject<icoModel>(turbulenceModel::propertiesName);

		Reff = model.devReff();
	}
	else
	{
		FatalErrorInFunction
			<< "Unable to find turbulence model in the "
			<< "database" << exit(FatalError);
	}

	word name(type());

	return store(name, calcShearStress(Reff));
}


bool tnbLib::functionObjects::wallShearStress::write()
{
	TnbLog << type() << " " << name() << " write:" << nl;

	writeLocalObjects::write();

	logFiles::write();

	const volVectorField& wallShearStress =
		obr_.lookupObject<volVectorField>(type());

	const fvPatchList& patches = mesh_.boundary();

	forAllConstIter(labelHashSet, patchSet_, iter)
	{
		label patchi = iter.key();
		const fvPatch& pp = patches[patchi];

		const vectorField& ssp = wallShearStress.boundaryField()[patchi];

		vector minSsp = gMin(ssp);
		vector maxSsp = gMax(ssp);

		if (Pstream::master())
		{
			file() << mesh_.time().value()
				<< tab << pp.name()
				<< tab << minSsp
				<< tab << maxSsp
				<< endl;
		}

		TnbLog << "    min/max(" << pp.name() << ") = "
			<< minSsp << ", " << maxSsp << endl;
	}

	TnbLog << endl;

	return true;
}


// ************************************************************************* //