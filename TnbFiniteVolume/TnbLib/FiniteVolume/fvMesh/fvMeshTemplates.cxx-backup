#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
typename tnbLib::pTraits<Type>::labelType tnbLib::fvMesh::validComponents() const
{
	return pow
	(
		this->solutionD(),
		pTraits
		<
		typename powProduct<Vector<label>,
		pTraits<Type>::rank>::type
		>::zero
	);
}


// ************************************************************************* //