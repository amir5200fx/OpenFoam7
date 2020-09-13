#include <fvMotionSolver.hxx>

#include <fixedValuePointPatchFields.hxx>
#include <cellMotionFvPatchFields.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class Type>
tnbLib::wordList tnbLib::fvMotionSolver::cellMotionBoundaryTypes
(
	const typename GeometricField<Type, pointPatchField, pointMesh>::
	Boundary& pmUbf
) const
{
	wordList cmUbf = pmUbf.types();

	// Remove global patches from the end of the list
	cmUbf.setSize(fvMesh_.boundary().size());

	forAll(cmUbf, patchi)
	{
		if (isA<fixedValuePointPatchField<Type>>(pmUbf[patchi]))
		{
			cmUbf[patchi] = cellMotionFvPatchField<Type>::typeName;
		}

		if (debug)
		{
			Pout << "Patch:" << fvMesh_.boundary()[patchi].patch().name()
				<< " pointType:" << pmUbf.types()[patchi]
				<< " cellType:" << cmUbf[patchi] << endl;
		}
	}

	return cmUbf;
}


// ************************************************************************* //