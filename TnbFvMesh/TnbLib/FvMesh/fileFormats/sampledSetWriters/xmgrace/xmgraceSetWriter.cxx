#include <xmgraceSetWriter.hxx>

#include <coordSet.hxx>
#include <fileName.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::xmgraceSetWriter<Type>::xmgraceSetWriter()
	:
	writer<Type>()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::xmgraceSetWriter<Type>::~xmgraceSetWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::fileName tnbLib::xmgraceSetWriter<Type>::getFileName
(
	const coordSet& points,
	const wordList& valueSetNames
) const
{
	return this->getBaseName(points, valueSetNames) + ".agr";
}


template<class Type>
void tnbLib::xmgraceSetWriter<Type>::write
(
	const coordSet& points,
	const wordList& valueSetNames,
	const List<const Field<Type>*>& valueSets,
	Ostream& os
) const
{
	os << "@g0 on" << nl
		<< "@with g0" << nl
		<< "@    title \"" << points.name() << '"' << nl
		<< "@    xaxis label " << '"' << points.axis() << '"' << nl;

	forAll(valueSets, i)
	{
		os << "@    s" << i << " legend " << '"'
			<< valueSetNames[i] << '"' << nl
			<< "@target G0.S" << i << nl;

		this->writeTable(points, *valueSets[i], os);

		os << '&' << nl;
	}
}


template<class Type>
void tnbLib::xmgraceSetWriter<Type>::write
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
		os << "@g0 on" << nl
			<< "@with g0" << nl
			<< "@    title \"" << trackPoints[0].name() << '"' << nl
			<< "@    xaxis label " << '"' << trackPoints[0].axis() << '"' << nl;

		// Data index.
		label sI = 0;

		forAll(trackPoints, trackI)
		{
			forAll(valueSets, i)
			{
				os << "@    s" << sI << " legend " << '"'
					<< valueSetNames[i] << "_track" << i << '"' << nl
					<< "@target G0.S" << sI << nl;
				this->writeTable(trackPoints[trackI], valueSets[i][trackI], os);
				os << '&' << nl;

				sI++;
			}
		}
	}
}

// ************************************************************************* //