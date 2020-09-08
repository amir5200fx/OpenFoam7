#include <extendedCellToCellStencil.hxx>
#include <extendedCellToFaceStencil.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class WeightType>
tnbLib::tmp
<
	tnbLib::GeometricField
	<
	typename tnbLib::outerProduct<WeightType, Type>::type,
	tnbLib::fvPatchField,
	tnbLib::volMesh
	>
> tnbLib::extendedCellToCellStencil::weightedSum
(
	const mapDistribute& map,
	const labelListList& stencil,
	const GeometricField<Type, fvPatchField, volMesh>& fld,
	const List<List<WeightType>>& stencilWeights
)
{
	typedef typename outerProduct<WeightType, Type>::type WeightedType;
	typedef GeometricField<WeightedType, fvPatchField, volMesh>
		WeightedFieldType;

	const fvMesh& mesh = fld.mesh();

	// Collect internal and boundary values
	List<List<Type>> stencilFld;
	extendedCellToFaceStencil::collectData(map, stencil, fld, stencilFld);

	tmp<WeightedFieldType> twf
	(
		new WeightedFieldType
		(
			IOobject
			(
				fld.name(),
				mesh.time().timeName(),
				mesh
			),
			mesh,
			dimensioned<WeightedType>
			(
				fld.name(),
				fld.dimensions(),
				Zero
				)
		)
	);
	WeightedFieldType& wf = twf();

	forAll(wf, celli)
	{
		const List<Type>& stField = stencilFld[celli];
		const List<WeightType>& stWeight = stencilWeights[celli];

		forAll(stField, i)
		{
			wf[celli] += stWeight[i] * stField[i];
		}
	}

	// Boundaries values?

	return twf;
}


// ************************************************************************* //