#pragma once
// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

template<class Type>
Type tnbLib::interpolatePointToCell
(
	const GeometricField<Type, pointPatchField, pointMesh>& ptf,
	const label celli
)
{
	const primitiveMesh& mesh = ptf.mesh()();

	const cell& cFaces = mesh.cells()[celli];

	labelHashSet pointHad(10 * cFaces.size());

	Type sum = Zero;

	forAll(cFaces, i)
	{
		const face& f = mesh.faces()[cFaces[i]];

		forAll(f, fp)
		{
			label v = f[fp];

			if (pointHad.insert(v))
			{
				sum += ptf[v];
			}
		}
	}

	return sum / pointHad.size();
}


// ************************************************************************* //