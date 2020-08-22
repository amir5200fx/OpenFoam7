#include <setUpdater.hxx>

#include <polyTopoChanger.hxx>
#include <polyTopoChange.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <mapPolyMesh.hxx>
#include <cellSet.hxx>
#include <faceSet.hxx>
#include <pointSet.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(setUpdater, 0);
	addToRunTimeSelectionTable
	(
		polyMeshModifier,
		setUpdater,
		dictionary
	);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //



// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from dictionary
tnbLib::setUpdater::setUpdater
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyTopoChanger& mme
)
	:
	polyMeshModifier(name, index, mme, Switch(dict.lookup("active")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::setUpdater::~setUpdater()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::setUpdater::changeTopology() const
{
	// I am never cause of changeTopo
	return false;
}


void tnbLib::setUpdater::setRefinement(polyTopoChange&) const
{}


void tnbLib::setUpdater::modifyMotionPoints(pointField&) const
{}


void tnbLib::setUpdater::updateMesh(const mapPolyMesh& morphMap)
{
	// Mesh has changed topologically. Update all sets.
	if (debug)
	{
		Pout << "setUpdater::updateMesh(const mapPolyMesh& morphMap)"
			<< endl;
	}

	updateSets<cellSet>(morphMap);
	updateSets<faceSet>(morphMap);
	updateSets<pointSet>(morphMap);
}


void tnbLib::setUpdater::write(Ostream& os) const
{
	os << nl << type() << nl;
}


void tnbLib::setUpdater::writeDict(Ostream& os) const
{
	os << nl << name() << nl << token::BEGIN_BLOCK << nl
		<< "    type " << type()
		<< token::END_STATEMENT << nl
		<< "    active " << active()
		<< token::END_STATEMENT << nl
		<< token::END_BLOCK << endl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


// ************************************************************************* //