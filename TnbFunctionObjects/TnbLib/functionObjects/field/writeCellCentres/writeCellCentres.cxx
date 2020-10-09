#include <writeCellCentres.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(writeCellCentres, 0);
		addToRunTimeSelectionTable(functionObject, writeCellCentres, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeCellCentres::writeCellCentres
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeCellCentres::~writeCellCentres()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::writeCellCentres::execute()
{
	return true;
}


bool tnbLib::functionObjects::writeCellCentres::write()
{
	volVectorField C
	(
		IOobject
		(
			"C",
			time_.timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		),
		mesh_.C(),
		calculatedFvPatchScalarField::typeName
	);

	TnbLog << "    Writing cell-centre field " << C.name()
		<< " to " << time_.timeName() << endl;

	C.write();

	for (direction i = 0; i < vector::nComponents; i++)
	{
		volScalarField Ci
		(
			IOobject
			(
				mesh_.C().name() + vector::componentNames[i],
				time_.timeName(),
				mesh_,
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			mesh_.C().component(i)
		);

		TnbLog << "    Writing the "
			<< vector::componentNames[i]
			<< " component field of the cell-centres " << Ci.name()
			<< " to " << time_.timeName() << endl;

		Ci.write();
	}

	return true;
}


// ************************************************************************* //