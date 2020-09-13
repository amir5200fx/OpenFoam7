#include <correlationFunction.hxx>

#include <IOstreams.hxx>

template<class Type>
bool tnbLib::correlationFunction<Type>::writeAveraged(Ostream& os) const
{
	Field<scalar> averageCF(averaged());

	forAll(averageCF, v)
	{
		os << v * sampleInterval()
			<< token::SPACE
			<< averageCF[v]
			<< nl;
	}

	return os.good();
}


template<class Type>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const correlationFunction<Type>& cF
	)
{
	os << cF.duration()
		<< nl << cF.sampleInterval()
		<< nl << cF.averagingInterval()
		<< nl << cF.sampleSteps()
		<< nl << cF.tZeroBuffers()
		<< nl << static_cast<const bufferedAccumulator<scalar>&>(cF);

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<"
		"(Ostream&, const correlationFunction<Type>&)"
	);

	return os;
}


// ************************************************************************* //