#include <joint.hxx>

#include <rigidBodyModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		defineTypeNameAndDebug(joint, 0);
		defineRunTimeSelectionTable(joint, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joint::New(joint* jointPtr)
{
	return autoPtr<joint>(jointPtr);
}


tnbLib::autoPtr<tnbLib::RBD::joint> tnbLib::RBD::joint::New
(
	const rigidBodyModel& model,
	const dictionary& dict
)
{
	const word bodyType(dict.lookup("type"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(bodyType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown joint type "
			<< bodyType << nl << nl
			<< "Valid joint types are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<joint>(cstrIter()(model, dict));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::joint::~joint()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::joint::write(Ostream& os) const
{
	writeEntry(os, "type", type());
}


// ************************************************************************* //