#include <rawGraph.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(rawGraph, 0);
	const word rawGraph::ext_("xy");

	typedef graph::writer graphWriter;
	addToRunTimeSelectionTable(graphWriter, rawGraph, word);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::rawGraph::write(const graph& g, Ostream& os) const
{
	g.writeTable(os);
}


// ************************************************************************* //