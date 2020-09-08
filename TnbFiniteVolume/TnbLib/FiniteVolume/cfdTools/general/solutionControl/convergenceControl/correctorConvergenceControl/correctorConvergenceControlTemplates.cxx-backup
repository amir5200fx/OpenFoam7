#include <correctorConvergenceControl.hxx>

#include <Residuals.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::correctorConvergenceControl::getNTypeSolves
(
	const fvMesh& mesh,
	const word& fieldName,
	label& n
)
{
	typedef GeometricField<Type, fvPatchField, volMesh> fieldType;

	if (mesh.foundObject<fieldType>(fieldName))
	{
		const DynamicList<SolverPerformance<Type>>& sp
		(
			Residuals<Type>::field(mesh, fieldName)
		);

		n = sp.size();
	}
}


// ************************************************************************* //