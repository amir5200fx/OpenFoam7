#include <xmgrGraph.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(xmgrGraph, 0);
	const word xmgrGraph::ext_("agr");

	typedef graph::writer graphWriter;
	addToRunTimeSelectionTable(graphWriter, xmgrGraph, word);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::xmgrGraph::write(const graph& g, Ostream& os) const
{
	os << "@title " << g.title() << nl
		<< "@xaxis label " << g.xName() << nl
		<< "@yaxis label " << g.yName() << endl;

	label fieldi = 0;

	forAllConstIter(graph, g, iter)
	{
		os << "@s" << fieldi << " legend "
			<< iter()->name() << nl
			<< "@target G0.S" << fieldi << nl
			<< "@type xy" << endl;

		writeXY(g.x(), *iter(), os);

		os << endl;

		fieldi++;
	}
}


// ************************************************************************* //