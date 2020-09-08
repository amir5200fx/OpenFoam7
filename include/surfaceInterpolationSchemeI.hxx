#pragma once
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <geometricOneField.hxx>
#include <coupledFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::surfaceInterpolationScheme<Type>>
tnbLib::surfaceInterpolationScheme<Type>::New
(
	const fvMesh& mesh,
	Istream& schemeData
)
{
	if (schemeData.eof())
	{
		FatalIOErrorInFunction
		(
			schemeData
		) << "Discretisation scheme not specified"
			<< endl << endl
			<< "Valid schemes are :" << endl
			<< MeshConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	const word schemeName(schemeData);

	if (surfaceInterpolation::debug || surfaceInterpolationScheme<Type>::debug)
	{
		InfoInFunction << "Discretisation scheme = " << schemeName << endl;
	}

	typename MeshConstructorTable::iterator constructorIter =
		MeshConstructorTablePtr_->find(schemeName);

	if (constructorIter == MeshConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			schemeData
		) << "Unknown discretisation scheme "
			<< schemeName << nl << nl
			<< "Valid schemes are :" << endl
			<< MeshConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return constructorIter()(mesh, schemeData);
}


template<class Type>
tnbLib::tmp<tnbLib::surfaceInterpolationScheme<Type>>
tnbLib::surfaceInterpolationScheme<Type>::New
(
	const fvMesh& mesh,
	const surfaceScalarField& faceFlux,
	Istream& schemeData
)
{
	if (schemeData.eof())
	{
		FatalIOErrorInFunction
		(
			schemeData
		) << "Discretisation scheme not specified"
			<< endl << endl
			<< "Valid schemes are :" << endl
			<< MeshConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	const word schemeName(schemeData);

	if (surfaceInterpolation::debug || surfaceInterpolationScheme<Type>::debug)
	{
		InfoInFunction
			<< "Discretisation scheme = " << schemeName << endl;
	}

	typename MeshFluxConstructorTable::iterator constructorIter =
		MeshFluxConstructorTablePtr_->find(schemeName);

	if (constructorIter == MeshFluxConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			schemeData
		) << "Unknown discretisation scheme "
			<< schemeName << nl << nl
			<< "Valid schemes are :" << endl
			<< MeshFluxConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return constructorIter()(mesh, faceFlux, schemeData);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::surfaceInterpolationScheme<Type>::~surfaceInterpolationScheme()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::surfaceInterpolationScheme<Type>::interpolate
(
	const GeometricField<Type, fvPatchField, volMesh>& vf,
	const tmp<surfaceScalarField>& tlambdas,
	const tmp<surfaceScalarField>& tys
)
{
	if (surfaceInterpolation::debug)
	{
		InfoInFunction
			<< "Interpolating "
			<< vf.type() << " "
			<< vf.name()
			<< " from cells to faces "
			"without explicit correction"
			<< endl;
	}

	const surfaceScalarField& lambdas = tlambdas();
	const surfaceScalarField& ys = tys();

	const Field<Type>& vfi = vf;
	const scalarField& lambda = lambdas;
	const scalarField& y = ys;

	const fvMesh& mesh = vf.mesh();
	const labelUList& P = mesh.owner();
	const labelUList& N = mesh.neighbour();

	tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsf
	(
		new GeometricField<Type, fvsPatchField, surfaceMesh>
		(
			IOobject
			(
				"interpolate(" + vf.name() + ')',
				vf.instance(),
				vf.db()
			),
			mesh,
			vf.dimensions()
			)
	);
	GeometricField<Type, fvsPatchField, surfaceMesh>& sf = tsf.ref();

	Field<Type>& sfi = sf.primitiveFieldRef();

	for (label fi = 0; fi < P.size(); fi++)
	{
		sfi[fi] = lambda[fi] * vfi[P[fi]] + y[fi] * vfi[N[fi]];
	}


	// Interpolate across coupled patches using given lambdas and ys
	typename GeometricField<Type, fvsPatchField, surfaceMesh>::
		Boundary& sfbf = sf.boundaryFieldRef();

	forAll(lambdas.boundaryField(), pi)
	{
		const fvsPatchScalarField& pLambda = lambdas.boundaryField()[pi];
		const fvsPatchScalarField& pY = ys.boundaryField()[pi];

		if (vf.boundaryField()[pi].coupled())
		{
			sfbf[pi] =
				pLambda * vf.boundaryField()[pi].patchInternalField()
				+ pY * vf.boundaryField()[pi].patchNeighbourField();
		}
		else
		{
			sfbf[pi] = vf.boundaryField()[pi];
		}
	}

	tlambdas.clear();
	tys.clear();

	return tsf;
}


template<class Type>
template<class SFType>
tnbLib::tmp
<
	tnbLib::GeometricField
	<
	typename tnbLib::innerProduct<typename SFType::value_type, Type>::type,
	tnbLib::fvsPatchField,
	tnbLib::surfaceMesh
	>
>
tnbLib::surfaceInterpolationScheme<Type>::dotInterpolate
(
	const SFType& Sf,
	const GeometricField<Type, fvPatchField, volMesh>& vf,
	const tmp<surfaceScalarField>& tlambdas
)
{
	if (surfaceInterpolation::debug)
	{
		InfoInFunction
			<< "Interpolating "
			<< vf.type() << " "
			<< vf.name()
			<< " from cells to faces "
			"without explicit correction"
			<< endl;
	}

	typedef typename tnbLib::innerProduct<typename SFType::value_type, Type>::type
		RetType;

	const surfaceScalarField& lambdas = tlambdas();

	const Field<Type>& vfi = vf;
	const scalarField& lambda = lambdas;

	const fvMesh& mesh = vf.mesh();
	const labelUList& P = mesh.owner();
	const labelUList& N = mesh.neighbour();

	tmp<GeometricField<RetType, fvsPatchField, surfaceMesh>> tsf
	(
		new GeometricField<RetType, fvsPatchField, surfaceMesh>
		(
			IOobject
			(
				"interpolate(" + vf.name() + ')',
				vf.instance(),
				vf.db()
			),
			mesh,
			Sf.dimensions()*vf.dimensions()
			)
	);
	GeometricField<RetType, fvsPatchField, surfaceMesh>& sf = tsf.ref();

	Field<RetType>& sfi = sf.primitiveFieldRef();

	const typename SFType::Internal& Sfi = Sf();

	for (label fi = 0; fi < P.size(); fi++)
	{
		sfi[fi] = Sfi[fi] & (lambda[fi] * (vfi[P[fi]] - vfi[N[fi]]) + vfi[N[fi]]);
	}

	// Interpolate across coupled patches using given lambdas

	typename GeometricField<RetType, fvsPatchField, surfaceMesh>::
		Boundary& sfbf = sf.boundaryFieldRef();

	forAll(lambdas.boundaryField(), pi)
	{
		const fvsPatchScalarField& pLambda = lambdas.boundaryField()[pi];
		const typename SFType::Patch& pSf = Sf.boundaryField()[pi];
		fvsPatchField<RetType>& psf = sfbf[pi];

		if (vf.boundaryField()[pi].coupled())
		{
			psf =
				pSf
				& (
					pLambda*vf.boundaryField()[pi].patchInternalField()
					+ (1.0 - pLambda)*vf.boundaryField()[pi].patchNeighbourField()
					);
		}
		else
		{
			psf = pSf & vf.boundaryField()[pi];
		}
	}

	tlambdas.clear();

	return tsf;
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::surfaceInterpolationScheme<Type>::interpolate
(
	const GeometricField<Type, fvPatchField, volMesh>& vf,
	const tmp<surfaceScalarField>& tlambdas
)
{
	return dotInterpolate(geometricOneField(), vf, tlambdas);
}


template<class Type>
tnbLib::tmp
<
	tnbLib::GeometricField
	<
	typename tnbLib::innerProduct<tnbLib::vector, Type>::type,
	tnbLib::fvsPatchField,
	tnbLib::surfaceMesh
	>
>
tnbLib::surfaceInterpolationScheme<Type>::dotInterpolate
(
	const surfaceVectorField& Sf,
	const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
	if (surfaceInterpolation::debug)
	{
		InfoInFunction
			<< "Interpolating "
			<< vf.type() << " "
			<< vf.name()
			<< " from cells to faces"
			<< endl;
	}

	tmp
		<
		GeometricField
		<
		typename tnbLib::innerProduct<tnbLib::vector, Type>::type,
		fvsPatchField,
		surfaceMesh
		>
		> tsf = dotInterpolate(Sf, vf, weights(vf));

	if (corrected())
	{
		tsf.ref() += Sf & correction(vf);
	}

	return tsf;
}


template<class Type>
tnbLib::tmp
<
	tnbLib::GeometricField
	<
	typename tnbLib::innerProduct<tnbLib::vector, Type>::type,
	tnbLib::fvsPatchField,
	tnbLib::surfaceMesh
	>
>
tnbLib::surfaceInterpolationScheme<Type>::dotInterpolate
(
	const surfaceVectorField& Sf,
	const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
) const
{
	tmp
		<
		GeometricField
		<
		typename tnbLib::innerProduct<tnbLib::vector, Type>::type,
		fvsPatchField,
		surfaceMesh
		>
		> tSfDotinterpVf = dotInterpolate(Sf, tvf());
	tvf.clear();
	return tSfDotinterpVf;
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::surfaceInterpolationScheme<Type>::interpolate
(
	const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
	if (surfaceInterpolation::debug)
	{
		InfoInFunction
			<< "Interpolating "
			<< vf.type() << " "
			<< vf.name()
			<< " from cells to faces"
			<< endl;
	}

	tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsf
		= interpolate(vf, weights(vf));

	if (corrected())
	{
		tsf.ref() += correction(vf);
	}

	return tsf;
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::surfaceInterpolationScheme<Type>::interpolate
(
	const tmp<GeometricField<Type, fvPatchField, volMesh>>& tvf
) const
{
	tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tinterpVf
		= interpolate(tvf());
	tvf.clear();
	return tinterpVf;
}


// ************************************************************************* //