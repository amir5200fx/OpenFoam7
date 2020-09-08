#pragma once
#include <extrapolatedCalculatedFvPatchField.hxx>

#include <surfaceMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp
<
	tnbLib::GeometricField
	<
	typename tnbLib::outerProduct<tnbLib::vector, Type>::type,
	tnbLib::fvPatchField,
	tnbLib::volMesh
	>
>
tnbLib::fv::gaussGrad<Type>::gradf
(
	const GeometricField<Type, fvsPatchField, surfaceMesh>& ssf,
	const word& name
)
{
	typedef typename outerProduct<vector, Type>::type GradType;

	const fvMesh& mesh = ssf.mesh();

	tmp<GeometricField<GradType, fvPatchField, volMesh>> tgGrad
	(
		new GeometricField<GradType, fvPatchField, volMesh>
		(
			IOobject
			(
				name,
				ssf.instance(),
				mesh,
				IOobject::NO_READ,
				IOobject::NO_WRITE
			),
			mesh,
			dimensioned<GradType>
			(
				"0",
				ssf.dimensions() / dimLength,
				Zero
				),
			extrapolatedCalculatedFvPatchField<GradType>::typeName
			)
	);
	GeometricField<GradType, fvPatchField, volMesh>& gGrad = tgGrad.ref();

	const labelUList& owner = mesh.owner();
	const labelUList& neighbour = mesh.neighbour();
	const vectorField& Sf = mesh.Sf();

	Field<GradType>& igGrad = gGrad;
	const Field<Type>& issf = ssf;

	forAll(owner, facei)
	{
		GradType Sfssf = Sf[facei] * issf[facei];

		igGrad[owner[facei]] += Sfssf;
		igGrad[neighbour[facei]] -= Sfssf;
	}

	forAll(mesh.boundary(), patchi)
	{
		const labelUList& pFaceCells =
			mesh.boundary()[patchi].faceCells();

		const vectorField& pSf = mesh.Sf().boundaryField()[patchi];

		const fvsPatchField<Type>& pssf = ssf.boundaryField()[patchi];

		forAll(mesh.boundary()[patchi], facei)
		{
			igGrad[pFaceCells[facei]] += pSf[facei] * pssf[facei];
		}
	}

	igGrad /= mesh.V();

	gGrad.correctBoundaryConditions();

	return tgGrad;
}


template<class Type>
tnbLib::tmp
<
	tnbLib::GeometricField
	<
	typename tnbLib::outerProduct<tnbLib::vector, Type>::type,
	tnbLib::fvPatchField,
	tnbLib::volMesh
	>
>
tnbLib::fv::gaussGrad<Type>::calcGrad
(
	const GeometricField<Type, fvPatchField, volMesh>& vsf,
	const word& name
) const
{
	typedef typename outerProduct<vector, Type>::type GradType;

	tmp<GeometricField<GradType, fvPatchField, volMesh>> tgGrad
	(
		gradf(tinterpScheme_().interpolate(vsf), name)
	);
	GeometricField<GradType, fvPatchField, volMesh>& gGrad = tgGrad.ref();

	correctBoundaryConditions(vsf, gGrad);

	return tgGrad;
}


template<class Type>
void tnbLib::fv::gaussGrad<Type>::correctBoundaryConditions
(
	const GeometricField<Type, fvPatchField, volMesh>& vsf,
	GeometricField
	<
	typename outerProduct<vector, Type>::type, fvPatchField, volMesh
	>& gGrad
)
{
	typename GeometricField
		<
		typename outerProduct<vector, Type>::type, fvPatchField, volMesh
		>::Boundary& gGradbf = gGrad.boundaryFieldRef();

	forAll(vsf.boundaryField(), patchi)
	{
		if (!vsf.boundaryField()[patchi].coupled())
		{
			const vectorField n
			(
				vsf.mesh().Sf().boundaryField()[patchi]
				/ vsf.mesh().magSf().boundaryField()[patchi]
			);

			gGradbf[patchi] += n *
				(
					vsf.boundaryField()[patchi].snGrad()
					- (n & gGradbf[patchi])
					);
		}
	}
}


// ************************************************************************* //