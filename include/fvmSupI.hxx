#pragma once
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvMatrix.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::fvMatrix<Type>>
tnbLib::fvm::Su
(
	const DimensionedField<Type, volMesh>& su,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	const fvMesh& mesh = vf.mesh();

	tmp<fvMatrix<Type>> tfvm
	(
		new fvMatrix<Type>
		(
			vf,
			dimVol*su.dimensions()
			)
	);
	fvMatrix<Type>& fvm = tfvm.ref();

	fvm.source() -= mesh.V()*su.field();

	return tfvm;
}


template<class Type>
tnbLib::tmp<tnbLib::fvMatrix<Type>>
tnbLib::fvm::Su
(
	const tmp<DimensionedField<Type, volMesh>>& tsu,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	tmp<fvMatrix<Type>> tfvm = fvm::Su(tsu(), vf);
	tsu.clear();
	return tfvm;
}


template<class Type>
tnbLib::tmp<tnbLib::fvMatrix<Type>>
tnbLib::fvm::Su
(
	const tmp<GeometricField<Type, fvPatchField, volMesh>>& tsu,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	tmp<fvMatrix<Type>> tfvm = fvm::Su(tsu(), vf);
	tsu.clear();
	return tfvm;
}


template<class Type>
tnbLib::zeroField
tnbLib::fvm::Su
(
	const zero&,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	return zeroField();
}


template<class Type>
tnbLib::tmp<tnbLib::fvMatrix<Type>>
tnbLib::fvm::Sp
(
	const volScalarField::Internal& sp,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	const fvMesh& mesh = vf.mesh();

	tmp<fvMatrix<Type>> tfvm
	(
		new fvMatrix<Type>
		(
			vf,
			dimVol*sp.dimensions()*vf.dimensions()
			)
	);
	fvMatrix<Type>& fvm = tfvm.ref();

	fvm.diag() += mesh.V()*sp.field();

	return tfvm;
}


template<class Type>
tnbLib::tmp<tnbLib::fvMatrix<Type>>
tnbLib::fvm::Sp
(
	const tmp<volScalarField::Internal>& tsp,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	tmp<fvMatrix<Type>> tfvm = fvm::Sp(tsp(), vf);
	tsp.clear();
	return tfvm;
}


template<class Type>
tnbLib::tmp<tnbLib::fvMatrix<Type>>
tnbLib::fvm::Sp
(
	const tmp<volScalarField>& tsp,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	tmp<fvMatrix<Type>> tfvm = fvm::Sp(tsp(), vf);
	tsp.clear();
	return tfvm;
}


template<class Type>
tnbLib::tmp<tnbLib::fvMatrix<Type>>
tnbLib::fvm::Sp
(
	const dimensionedScalar& sp,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	const fvMesh& mesh = vf.mesh();

	tmp<fvMatrix<Type>> tfvm
	(
		new fvMatrix<Type>
		(
			vf,
			dimVol*sp.dimensions()*vf.dimensions()
			)
	);
	fvMatrix<Type>& fvm = tfvm.ref();

	fvm.diag() += mesh.V()*sp.value();

	return tfvm;
}


template<class Type>
tnbLib::zeroField
tnbLib::fvm::Sp
(
	const zero&,
	const GeometricField<Type, fvPatchField, volMesh>&
)
{
	return zeroField();
}


template<class Type>
tnbLib::tmp<tnbLib::fvMatrix<Type>>
tnbLib::fvm::SuSp
(
	const volScalarField::Internal& susp,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	const fvMesh& mesh = vf.mesh();

	tmp<fvMatrix<Type>> tfvm
	(
		new fvMatrix<Type>
		(
			vf,
			dimVol*susp.dimensions()*vf.dimensions()
			)
	);
	fvMatrix<Type>& fvm = tfvm.ref();

	fvm.diag() += mesh.V()*max(susp.field(), scalar(0));

	fvm.source() -= mesh.V()*min(susp.field(), scalar(0))
		*vf.primitiveField();

	return tfvm;
}


template<class Type>
tnbLib::tmp<tnbLib::fvMatrix<Type>>
tnbLib::fvm::SuSp
(
	const tmp<volScalarField::Internal>& tsusp,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	tmp<fvMatrix<Type>> tfvm = fvm::SuSp(tsusp(), vf);
	tsusp.clear();
	return tfvm;
}


template<class Type>
tnbLib::tmp<tnbLib::fvMatrix<Type>>
tnbLib::fvm::SuSp
(
	const tmp<volScalarField>& tsusp,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	tmp<fvMatrix<Type>> tfvm = fvm::SuSp(tsusp(), vf);
	tsusp.clear();
	return tfvm;
}


template<class Type>
tnbLib::zeroField
tnbLib::fvm::SuSp
(
	const zero&,
	const GeometricField<Type, fvPatchField, volMesh>& vf
)
{
	return zeroField();
}


// ************************************************************************* //