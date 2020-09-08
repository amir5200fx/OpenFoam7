#pragma once
#include <Residuals.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class ResidualData>
tnbLib::label tnbLib::convergenceControl::residualControlIndex
(
	const word& fieldName,
	const List<ResidualData>& residualControl,
	const bool useRegEx
)
{
	forAll(residualControl, i)
	{
		if (useRegEx && residualControl[i].name.match(fieldName))
		{
			return i;
		}
		else if (residualControl[i].name == fieldName)
		{
			return i;
		}
	}

	return -1;
}


template<class Type>
void tnbLib::convergenceControl::getFieldTypeNames
(
	const fvMesh& mesh,
	DynamicList<word>& fieldNames
)
{
	fieldNames.append(Residuals<Type>::fieldNames(mesh));
}


template<class Type>
void tnbLib::convergenceControl::getInitialTypeResiduals
(
	const fvMesh& mesh,
	const word& fieldName,
	const label solvei,
	scalar& r0,
	scalar& r
)
{
	typedef GeometricField<Type, fvPatchField, volMesh> fieldType;

	if (mesh.foundObject<fieldType>(fieldName))
	{
		const DynamicList<SolverPerformance<Type>>& sp
		(
			Residuals<Type>::field(mesh, fieldName)
		);

		r0 = cmptMax(sp[0].initialResidual());
		r = cmptMax(sp[solvei].initialResidual());
	}
}


// ************************************************************************* //