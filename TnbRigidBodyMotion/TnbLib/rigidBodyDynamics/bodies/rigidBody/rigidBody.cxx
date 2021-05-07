#include <rigidBody.hxx>

#include <subBody.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		defineTypeNameAndDebug(rigidBody, 0);
		defineRunTimeSelectionTable(rigidBody, dictionary);

		addToRunTimeSelectionTable
		(
			rigidBody,
			rigidBody,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::rigidBody> tnbLib::RBD::rigidBody::clone() const
{
	return autoPtr<rigidBody>(new rigidBody(*this));
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::rigidBody> tnbLib::RBD::rigidBody::New
(
	const word& name,
	const scalar& m,
	const vector& c,
	const symmTensor& Ic
)
{
	return autoPtr<rigidBody>(new rigidBody(name, m, c, Ic));
}


tnbLib::autoPtr<tnbLib::RBD::rigidBody> tnbLib::RBD::rigidBody::New
(
	const word& name,
	const dictionary& dict
)
{
	const word bodyType(dict.lookup("type"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(bodyType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown rigidBody type "
			<< bodyType << nl << nl
			<< "Valid rigidBody types are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<rigidBody>(cstrIter()(name, dict));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBody::~rigidBody()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::RBD::rigidBody::massless() const
{
	return false;
}


void tnbLib::RBD::rigidBody::merge(const subBody& subBody)
{
	*this = rigidBody
	(
		name(),
		*this + transform(subBody.masterXT(), subBody.body())
	);
}


void tnbLib::RBD::rigidBody::write(Ostream& os) const
{
	writeEntry(os, "type", type());

	writeEntry(os, "mass", m());

	writeEntry(os, "centreOfMass", c());

	writeEntry(os, "inertia", Ic());
}


// ************************************************************************* //