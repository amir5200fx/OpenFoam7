#include <wallPointData.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

	template<class Type>
	Ostream& operator<<
		(
			Ostream& os,
			const wallPointData<Type>& wDist
			)
	{
		return os
			<< static_cast<const wallPoint&>(wDist)
			<< token::SPACE
			<< wDist.data();
	}


	template<class Type>
	Istream& operator>>
		(
			Istream& is,
			wallPointData<Type>& wDist
			)
	{
		return is >> static_cast<wallPoint&>(wDist) >> wDist.data_;
	}


	// ************************************************************************* //

} // End namespace tnbLib

// ************************************************************************* //