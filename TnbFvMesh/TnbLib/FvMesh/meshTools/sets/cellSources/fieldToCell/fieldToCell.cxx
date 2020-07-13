#include <fieldToCell.hxx>

#include <polyMesh.hxx>
#include <cellSet.hxx>
#include <Time.hxx>
#include <IFstream.hxx>
#include <fieldDictionary.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(fieldToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, fieldToCell, word);
	addToRunTimeSelectionTable(topoSetSource, fieldToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::fieldToCell::usage_
(
	fieldToCell::typeName,
	"\n    Usage: fieldToCell field min max\n\n"
	"    Select all cells with field value >= min and <= max\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::fieldToCell::applyToSet
(
	const topoSetSource::setAction action,
	const scalarField& field,
	topoSet& set
) const
{
	Info << "    Field min:" << min(field)
		<< " max:" << max(field) << endl;

	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all cells with value of field " << fieldName_
			<< " within range " << min_ << ".." << max_ << endl;

		forAll(field, celli)
		{
			if (field[celli] >= min_ && field[celli] <= max_)
			{
				set.insert(celli);
			}
		}
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all cells with value of field " << fieldName_
			<< " within range " << min_ << ".." << max_ << endl;

		forAll(field, celli)
		{
			if (field[celli] >= min_ && field[celli] <= max_)
			{
				set.erase(celli);
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fieldToCell::fieldToCell
(
	const polyMesh& mesh,
	const word& fieldName,
	const scalar min,
	const scalar max
)
	:
	topoSetSource(mesh),
	fieldName_(fieldName),
	min_(min),
	max_(max)
{}


tnbLib::fieldToCell::fieldToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	fieldName_(dict.lookup("field")),
	min_(readScalar(dict.lookup("min"))),
	max_(readScalar(dict.lookup("max")))
{}


tnbLib::fieldToCell::fieldToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	fieldName_(checkIs(is)),
	min_(readScalar(checkIs(is))),
	max_(readScalar(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fieldToCell::~fieldToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fieldToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	// Try to load field
	IOobject fieldObject
	(
		fieldName_,
		mesh().time().timeName(),
		mesh(),
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE,
		false
	);

	// Note: should check for volScalarField but that introduces depencendy
	//       on volMesh so just use another type with processor-local scope
	if (!fieldObject.typeHeaderOk<labelIOList>(false))
	{
		WarningInFunction
			<< "Cannot read field " << fieldName_
			<< " from time " << mesh().time().timeName() << endl;
	}
	else if (fieldObject.headerClassName() == "volScalarField")
	{
		IFstream str(typeFilePath<labelIOList>(fieldObject));

		// Read dictionary
		fieldDictionary fieldDict(fieldObject, fieldObject.headerClassName());

		scalarField internalVals("internalField", fieldDict, mesh().nCells());

		applyToSet(action, internalVals, set);
	}
	else if (fieldObject.headerClassName() == "volVectorField")
	{
		IFstream str(typeFilePath<labelIOList>(fieldObject));

		// Read dictionary
		fieldDictionary fieldDict(fieldObject, fieldObject.headerClassName());

		vectorField internalVals("internalField", fieldDict, mesh().nCells());

		applyToSet(action, mag(internalVals), set);
	}
	else
	{
		WarningInFunction
			<< "Cannot handle fields of type " << fieldObject.headerClassName()
			<< endl;
	}
}


// ************************************************************************* //