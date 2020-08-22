#include <jplotGraph.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(jplotGraph, 0);
	const word jplotGraph::ext_("dat");

	typedef graph::writer graphWriter;
	addToRunTimeSelectionTable(graphWriter, jplotGraph, word);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::jplotGraph::write(const graph& g, Ostream& os) const
{
	os << "# JPlot file" << nl
		<< "# column 1: " << g.xName() << endl;

	label fieldi = 0;

	forAllConstIter(graph, g, iter)
	{
		os << "# column " << fieldi + 2 << ": " << (*iter()).name() << endl;
		fieldi++;
	}

	g.writeTable(os);
}


// ************************************************************************* //