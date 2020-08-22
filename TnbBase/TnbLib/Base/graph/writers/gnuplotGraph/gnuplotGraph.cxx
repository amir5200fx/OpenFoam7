#include <gnuplotGraph.hxx>

#include <addToRunTimeSelectionTable.hxx>


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(gnuplotGraph, 0);
	const word gnuplotGraph::ext_("gplt");

	typedef graph::writer graphWriter;
	addToRunTimeSelectionTable(graphWriter, gnuplotGraph, word);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::gnuplotGraph::write(const graph& g, Ostream& os) const
{
	os << "#set term postscript color" << endl
		<< "set output \"" << word(g.title()) << ".ps\"" << endl
		<< "set title " << g.title() << " 0,0" << endl << "show title" << endl
		<< "set xlabel " << g.xName() << " 0,0" << endl << "show xlabel" << endl
		<< "set ylabel " << g.yName() << " 0,0" << endl << "show ylabel" << endl
		<< "plot";

	bool firstField = true;

	forAllConstIter(graph, g, iter)
	{
		if (!firstField)
		{
			os << ',';
		}
		firstField = false;

		os << "'-' title " << iter()->name() << " with lines";
	}
	os << "; pause -1" << endl;


	forAllConstIter(graph, g, iter)
	{
		os << endl;
		writeXY(g.x(), *iter(), os);
	}
}


// ************************************************************************* //