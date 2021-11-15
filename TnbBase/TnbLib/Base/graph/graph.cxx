#include <graph.hxx>

#include <OFstream.hxx>
#include <IOmanip.hxx>
#include <Pair.hxx>
#include <OSspecific.hxx>

#include <token.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	typedef graph::writer graphWriter;
	defineTypeNameAndDebug(graphWriter, 0);
	defineRunTimeSelectionTable(graphWriter, word);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::word tnbLib::graph::wordify(const tnbLib::string& sname)
{
	string wname = sname;
	wname.replace(' ', '_');
	wname.replace('(', '_');
	wname.replace(')', "");

	return word(wname);
}


void tnbLib::graph::readCurves(Istream& is)
{
	List<xy> xyData(is);

	x_.setSize(xyData.size());
	scalarField y(xyData.size());

	forAll(xyData, i)
	{
		x_[i] = xyData[i].x_;
		y[i] = xyData[i].y_;
	}

	insert
	(
		wordify(yName_),
		new curve(wordify(yName_), curve::curveStyle::CONTINUOUS, y)
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::graph::graph
(
	const string& title,
	const string& xName,
	const string& yName,
	const scalarField& x
)
	:
	title_(title),
	xName_(xName),
	yName_(yName),
	x_(x)
{}


tnbLib::graph::graph
(
	const string& title,
	const string& xName,
	const string& yName,
	const scalarField& x,
	const scalarField& y
)
	:
	title_(title),
	xName_(xName),
	yName_(yName),
	x_(x)
{
	insert(wordify(yName), new curve(yName, curve::curveStyle::CONTINUOUS, y));
}


tnbLib::graph::graph
(
	const string& title,
	const string& xName,
	const string& yName,
	Istream& is
)
	:
	title_(title),
	xName_(xName),
	yName_(yName)
{
	readCurves(is);
}


tnbLib::graph::graph(Istream& is)
	:
	title_(is),
	xName_(is),
	yName_(is)
{
	readCurves(is);
}


const tnbLib::scalarField& tnbLib::graph::y() const
{
	if (size() != 1)
	{
		FatalErrorInFunction
			<< "y field requested for graph containing " << size()
			<< "ys" << exit(FatalError);
	}

	return *begin()();
}


tnbLib::scalarField& tnbLib::graph::y()
{
	if (size() != 1)
	{
		FatalErrorInFunction
			<< "y field requested for graph containing " << size()
			<< "ys" << exit(FatalError);
	}

	return *begin()();
}


tnbLib::autoPtr<tnbLib::graph::writer> tnbLib::graph::writer::New
(
	const word& graphFormat
)
{
	if (!wordConstructorTablePtr_)
	{
		FatalErrorInFunction
			<< "Graph writer table is empty"
			<< exit(FatalError);
	}

	wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(graphFormat);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown graph format " << graphFormat
			<< endl << endl
			<< "Valid graph formats are : " << endl
			<< wordConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<graph::writer>(cstrIter()());
}


void tnbLib::graph::writer::writeXY
(
	const scalarField& x,
	const scalarField& y,
	Ostream& os
) const
{
	forAll(x, xi)
	{
		os << setw(10) << x[xi] << token::SPACE << setw(10) << y[xi] << endl;
	}
}


void tnbLib::graph::writeTable(Ostream& os) const
{
	forAll(x_, xi)
	{
		os << setw(10) << x_[xi];

		forAllConstIter(graph, *this, iter)
		{
			os << token::SPACE << setw(10) << (*iter())[xi];
		}
		os << endl;
	}
}


void tnbLib::graph::write(Ostream& os, const word& format) const
{
	writer::New(format)().write(*this, os);
}


void tnbLib::graph::write(const fileName& pName, const word& format) const
{
	autoPtr<writer> graphWriter(writer::New(format));

	OFstream graphFile(pName + '.' + graphWriter().ext());

	if (graphFile.good())
	{
		write(graphFile, format);
	}
	else
	{
		WarningInFunction
			<< "Could not open graph file " << graphFile.name()
			<< endl;
	}
}


void tnbLib::graph::write
(
	const fileName& path,
	const word& name,
	const word& format
) const
{
	mkDir(path);
	write(path / name, format);
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const graph& g)
{
	g.writeTable(os);
	os.check("Ostream& operator<<(Ostream&, const graph&)");
	return os;
}


// ************************************************************************* //