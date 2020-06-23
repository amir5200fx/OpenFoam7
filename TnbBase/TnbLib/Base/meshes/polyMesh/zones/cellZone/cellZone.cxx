#include <cellZone.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <cellZoneMesh.hxx>
#include <polyMesh.hxx>
#include <primitiveMesh.hxx>
#include <IOstream.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(cellZone, 0);
	defineRunTimeSelectionTable(cellZone, dictionary);
	addToRunTimeSelectionTable(cellZone, cellZone, dictionary);
}

const char * const tnbLib::cellZone::labelsName = "cellLabels";

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::cellZone::cellZone
(
	const word& name,
	const labelUList& addr,
	const label index,
	const cellZoneMesh& zm
)
	:
	zone(name, addr, index),
	zoneMesh_(zm)
{}


tnbLib::cellZone::cellZone
(
	const word& name,
	labelList&& addr,
	const label index,
	const cellZoneMesh& zm
)
	:
	zone(name, move(addr), index),
	zoneMesh_(zm)
{}


tnbLib::cellZone::cellZone
(
	const word& name,
	const dictionary& dict,
	const label index,
	const cellZoneMesh& zm
)
	:
	zone(name, dict, this->labelsName, index),
	zoneMesh_(zm)
{}


tnbLib::cellZone::cellZone
(
	const cellZone& cz,
	const labelUList& addr,
	const label index,
	const cellZoneMesh& zm
)
	:
	zone(cz, addr, index),
	zoneMesh_(zm)
{}


tnbLib::cellZone::cellZone
(
	const cellZone& cz,
	labelList&& addr,
	const label index,
	const cellZoneMesh& zm
)
	:
	zone(cz, move(addr), index),
	zoneMesh_(zm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::cellZone::~cellZone()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::cellZone::whichCell(const label globalCellID) const
{
	return zone::localID(globalCellID);
}


const tnbLib::cellZoneMesh& tnbLib::cellZone::zoneMesh() const
{
	return zoneMesh_;
}


bool tnbLib::cellZone::checkDefinition(const bool report) const
{
	return zone::checkDefinition(zoneMesh_.mesh().nCells(), report);
}


void tnbLib::cellZone::writeDict(Ostream& os) const
{
	os << nl << name() << nl << token::BEGIN_BLOCK << nl
		<< "    type " << type() << token::END_STATEMENT << nl;

	writeEntry(os, this->labelsName, *this);

	os << token::END_BLOCK << endl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::cellZone::operator=(const cellZone& zn)
{
	clearAddressing();
	zone::operator=(zn);
}


void tnbLib::cellZone::operator=(cellZone&& zn)
{
	clearAddressing();
	zone::operator=(move(zn));
}


void tnbLib::cellZone::operator=(const labelUList& addr)
{
	clearAddressing();
	zone::operator=(addr);
}


void tnbLib::cellZone::operator=(labelList&& addr)
{
	clearAddressing();
	zone::operator=(move(addr));
}


// ************************************************************************* //