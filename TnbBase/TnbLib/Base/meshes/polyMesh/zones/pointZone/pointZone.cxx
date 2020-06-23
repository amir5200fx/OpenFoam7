#include <pointZone.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <pointZoneMesh.hxx>
#include <polyMesh.hxx>
#include <primitiveMesh.hxx>
#include <demandDrivenData.hxx>
#include <syncTools.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(pointZone, 0);
	defineRunTimeSelectionTable(pointZone, dictionary);
	addToRunTimeSelectionTable(pointZone, pointZone, dictionary);
}

const char* const tnbLib::pointZone::labelsName = "pointLabels";

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pointZone::pointZone
(
	const word& name,
	const labelUList& addr,
	const label index,
	const pointZoneMesh& zm
)
	:
	zone(name, addr, index),
	zoneMesh_(zm)
{}


tnbLib::pointZone::pointZone
(
	const word& name,
	labelList&& addr,
	const label index,
	const pointZoneMesh& zm
)
	:
	zone(name, move(addr), index),
	zoneMesh_(zm)
{}


tnbLib::pointZone::pointZone
(
	const word& name,
	const dictionary& dict,
	const label index,
	const pointZoneMesh& zm
)
	:
	zone(name, dict, this->labelsName, index),
	zoneMesh_(zm)
{}


tnbLib::pointZone::pointZone
(
	const pointZone& pz,
	const labelUList& addr,
	const label index,
	const pointZoneMesh& zm
)
	:
	zone(pz, addr, index),
	zoneMesh_(zm)
{}


tnbLib::pointZone::pointZone
(
	const pointZone& pz,
	labelList&& addr,
	const label index,
	const pointZoneMesh& zm
)
	:
	zone(pz, move(addr), index),
	zoneMesh_(zm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pointZone::~pointZone()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::pointZoneMesh& tnbLib::pointZone::zoneMesh() const
{
	return zoneMesh_;
}


tnbLib::label tnbLib::pointZone::whichPoint(const label globalPointID) const
{
	return zone::localID(globalPointID);
}


bool tnbLib::pointZone::checkDefinition(const bool report) const
{
	return zone::checkDefinition(zoneMesh_.mesh().points().size(), report);
}


bool tnbLib::pointZone::checkParallelSync(const bool report) const
{
	const polyMesh& mesh = zoneMesh().mesh();

	labelList maxZone(mesh.nPoints(), -1);
	labelList minZone(mesh.nPoints(), labelMax);
	forAll(*this, i)
	{
		label pointi = operator[](i);
		maxZone[pointi] = index();
		minZone[pointi] = index();
	}
	syncTools::syncPointList(mesh, maxZone, maxEqOp<label>(), label(-1));
	syncTools::syncPointList(mesh, minZone, minEqOp<label>(), labelMax);

	bool error = false;

	forAll(maxZone, pointi)
	{
		// Check point in same (or no) zone on all processors
		if
			(
			(
				maxZone[pointi] != -1
				|| minZone[pointi] != labelMax
				)
				&& (maxZone[pointi] != minZone[pointi])
				)
		{
			if (report && !error)
			{
				Info << " ***Problem with pointZone " << index()
					<< " named " << name()
					<< ". Point " << pointi
					<< " at " << mesh.points()[pointi]
					<< " is in zone "
					<< (minZone[pointi] == labelMax ? -1 : minZone[pointi])
					<< " on some processors and in zone "
					<< maxZone[pointi]
					<< " on some other processors." << nl
					<< "(suppressing further warnings)"
					<< endl;
			}
			error = true;
		}
	}

	return error;
}


void tnbLib::pointZone::writeDict(Ostream& os) const
{
	os << nl << name_ << nl << token::BEGIN_BLOCK << nl
		<< "    type " << type() << token::END_STATEMENT << nl;

	writeEntry(os, this->labelsName, *this);

	os << token::END_BLOCK << endl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::pointZone::operator=(const pointZone& zn)
{
	clearAddressing();
	zone::operator=(zn);
}


void tnbLib::pointZone::operator=(pointZone&& zn)
{
	clearAddressing();
	zone::operator=(move(zn));
}


void tnbLib::pointZone::operator=(const labelUList& addr)
{
	clearAddressing();
	zone::operator=(addr);
}


void tnbLib::pointZone::operator=(labelList&& addr)
{
	clearAddressing();
	zone::operator=(move(addr));
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const pointZone& zn)
{
	zn.write(os);
	os.check("Ostream& operator<<(Ostream&, const pointZone&");
	return os;
}


// ************************************************************************* //