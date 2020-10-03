#include <yPlus.hxx>

#include <turbulenceModel.hxx>
#include <nutWallFunctionFvPatchScalarField.hxx>
#include <wallFvPatch.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(yPlus, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			yPlus,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::yPlus::writeFileHeader(const label i)
{
	writeHeader(file(), "y+ ()");

	writeCommented(file(), "Time");
	writeTabbed(file(), "patch");
	writeTabbed(file(), "min");
	writeTabbed(file(), "max");
	writeTabbed(file(), "average");
	file() << endl;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::functionObjects::yPlus::calcYPlus
(
	const turbulenceModel& turbModel
)
{
	tmp<volScalarField> tyPlus
	(
		volScalarField::New
		(
			type(),
			mesh_,
			dimensionedScalar(dimless, 0)
		)
	);

	volScalarField::Boundary& yPlusBf = tyPlus.ref().boundaryFieldRef();

	volScalarField::Boundary d = nearWallDist(mesh_).y();

	const volScalarField::Boundary nutBf =
		turbModel.nut()().boundaryField();

	const volScalarField::Boundary nuEffBf =
		turbModel.nuEff()().boundaryField();

	const volScalarField::Boundary nuBf =
		turbModel.nu()().boundaryField();

	const fvPatchList& patches = mesh_.boundary();

	forAll(patches, patchi)
	{
		const fvPatch& patch = patches[patchi];

		if (isA<nutWallFunctionFvPatchScalarField>(nutBf[patchi]))
		{
			const nutWallFunctionFvPatchScalarField& nutPf =
				dynamic_cast<const nutWallFunctionFvPatchScalarField&>
				(
					nutBf[patchi]
					);

			yPlusBf[patchi] = nutPf.yPlus();
		}
		else if (isA<wallFvPatch>(patch))
		{
			yPlusBf[patchi] =
				d[patchi]
				* sqrt
				(
					nuEffBf[patchi]
					* mag(turbModel.U().boundaryField()[patchi].snGrad())
				) / nuBf[patchi];
		}
	}

	return tyPlus;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::yPlus::yPlus
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	logFiles(obr_, name),
	writeLocalObjects(obr_, log)
{
	read(dict);
	resetName(typeName);
	resetLocalObjectName(typeName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::yPlus::~yPlus()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::yPlus::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);
	writeLocalObjects::read(dict);

	return true;
}


bool tnbLib::functionObjects::yPlus::execute()
{
	if (mesh_.foundObject<turbulenceModel>(turbulenceModel::propertiesName))
	{
		const turbulenceModel& model = mesh_.lookupObject<turbulenceModel>
			(
				turbulenceModel::propertiesName
				);

		word name(type());

		return store(name, calcYPlus(model));
	}
	else
	{
		FatalErrorInFunction
			<< "Unable to find turbulence model in the "
			<< "database" << exit(FatalError);
	}

	return true;
}


bool tnbLib::functionObjects::yPlus::write()
{
	TnbLog << type() << " " << name() << " write:" << nl;

	writeLocalObjects::write();

	logFiles::write();

	const volScalarField& yPlus =
		mesh_.lookupObject<volScalarField>(type());

	const volScalarField::Boundary& yPlusBf = yPlus.boundaryField();
	const fvPatchList& patches = mesh_.boundary();

	forAll(patches, patchi)
	{
		const fvPatch& patch = patches[patchi];

		if (isA<wallFvPatch>(patch))
		{
			const scalarField& yPlusp = yPlusBf[patchi];

			const scalar minYplus = gMin(yPlusp);
			const scalar maxYplus = gMax(yPlusp);
			const scalar avgYplus = gAverage(yPlusp);

			if (Pstream::master())
			{
				TnbLog << "    patch " << patch.name()
					<< " y+ : min = " << minYplus << ", max = " << maxYplus
					<< ", average = " << avgYplus << nl;

				writeTime(file());
				file()
					<< tab << patch.name()
					<< tab << minYplus
					<< tab << maxYplus
					<< tab << avgYplus
					<< endl;
			}
		}
	}

	TnbLog << endl;

	return true;
}


// ************************************************************************* //