#include <gnuplotSetWriter.hxx>

#include <coordSet.hxx>
#include <fileName.hxx>
#include <OFstream.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::gnuplotSetWriter<Type>::gnuplotSetWriter()
	:
	writer<Type>()
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::gnuplotSetWriter<Type>::~gnuplotSetWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::fileName tnbLib::gnuplotSetWriter<Type>::getFileName
(
	const coordSet& points,
	const wordList& valueSetNames
) const
{
	return this->getBaseName(points, valueSetNames) + ".gplt";
}


template<class Type>
void tnbLib::gnuplotSetWriter<Type>::write
(
	const coordSet& points,
	const wordList& valueSetNames,
	const List<const Field<Type>*>& valueSets,
	Ostream& os
) const
{
	os << "set term postscript color" << nl
		<< "set output \"" << points.name() << ".ps\"" << nl
		<< "plot";

	forAll(valueSets, i)
	{
		if (i != 0)
		{
			os << ',';
		}

		os << " \"-\" title \"" << valueSetNames[i] << "\" with lines";
	}
	os << nl;


	forAll(valueSets, i)
	{
		this->writeTable(points, *valueSets[i], os);
		os << "e" << nl;
	}
}


template<class Type>
void tnbLib::gnuplotSetWriter<Type>::write
(
	const bool writeTracks,
	const PtrList<coordSet>& trackPoints,
	const wordList& valueSetNames,
	const List<List<Field<Type>>>& valueSets,
	Ostream& os
) const
{
	if (valueSets.size() != valueSetNames.size())
	{
		FatalErrorInFunction
			<< "Number of variables:" << valueSetNames.size() << endl
			<< "Number of valueSets:" << valueSets.size()
			<< exit(FatalError);
	}
	if (trackPoints.size() > 0)
	{
		os << "set term postscript color" << nl
			<< "set output \"" << trackPoints[0].name() << ".ps\"" << nl;

		forAll(trackPoints, trackI)
		{
			os << "plot";

			forAll(valueSets, i)
			{
				if (i != 0)
				{
					os << ',';
				}

				os << " \"-\" title \"" << valueSetNames[i] << "\" with lines";
			}
			os << nl;

			forAll(valueSets, i)
			{
				this->writeTable(trackPoints[trackI], valueSets[i][trackI], os);
				os << "e" << nl;
			}
		}
	}
}


// ************************************************************************* //