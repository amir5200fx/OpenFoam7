#include <fvcCellReduce.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <extrapolatedCalculatedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class CombineOp>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
tnbLib::fvc::cellReduce
(
	const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf,
	const CombineOp& cop,
	const Type& nullValue
)
{
	typedef GeometricField<Type, fvPatchField, volMesh> volFieldType;

	const fvMesh& mesh = ssf.mesh();

	tmp<volFieldType> tresult
	(
		volFieldType::New
		(
			"cellReduce(" + ssf.name() + ')',
			mesh,
			dimensioned<Type>
			(
				ssf.dimensions(),
				nullValue
				),
			extrapolatedCalculatedFvPatchField<Type>::typeName
		)
	);

	volFieldType& result = tresult.ref();

	const labelUList& own = mesh.owner();
	const labelUList& nbr = mesh.neighbour();

	forAll(own, i)
	{
		label celli = own[i];
		cop(result[celli], ssf[i]);
	}
	forAll(nbr, i)
	{
		label celli = nbr[i];
		cop(result[celli], ssf[i]);
	}

	result.correctBoundaryConditions();

	return tresult;
}


template<class Type, class CombineOp>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
tnbLib::fvc::cellReduce
(
	const tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>& tssf,
	const CombineOp& cop,
	const Type& nullValue
)
{
	tmp<GeometricField<Type, fvPatchField, volMesh>> tvf
	(
		cellReduce
		(
			tssf,
			cop,
			nullValue
		)
	);

	tssf.clear();

	return tvf;
}


// ************************************************************************* //