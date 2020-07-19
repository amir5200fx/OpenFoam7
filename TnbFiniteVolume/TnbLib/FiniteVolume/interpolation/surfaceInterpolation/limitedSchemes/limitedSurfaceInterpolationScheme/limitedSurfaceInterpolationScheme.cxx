#include <limitedSurfaceInterpolationScheme.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <coupledFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::limitedSurfaceInterpolationScheme<Type>>
tnbLib::limitedSurfaceInterpolationScheme<Type>::New
(
	const fvMesh& mesh,
	Istream& schemeData
)
{
	if (surfaceInterpolation::debug)
	{
		InfoInFunction
			<< "Constructing limitedSurfaceInterpolationScheme<Type>" << endl;
	}

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
tnbLib::tmp<tnbLib::limitedSurfaceInterpolationScheme<Type>>
tnbLib::limitedSurfaceInterpolationScheme<Type>::New
(
	const fvMesh& mesh,
	const surfaceScalarField& faceFlux,
	Istream& schemeData
)
{
	if (surfaceInterpolation::debug)
	{
		InfoInFunction
			<< "Constructing limitedSurfaceInterpolationScheme<Type>"
			<< endl;
	}

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
tnbLib::limitedSurfaceInterpolationScheme<Type>::
~limitedSurfaceInterpolationScheme()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::limitedSurfaceInterpolationScheme<Type>::weights
(
	const GeometricField<Type, fvPatchField, volMesh>& phi,
	const surfaceScalarField& CDweights,
	tmp<surfaceScalarField> tLimiter
) const
{
	// Note that here the weights field is initialised as the limiter
	// from which the weight is calculated using the limiter value
	surfaceScalarField& Weights = tLimiter.ref();

	scalarField& pWeights = Weights.primitiveFieldRef();

	forAll(pWeights, face)
	{
		pWeights[face] =
			pWeights[face] * CDweights[face]
			+ (1.0 - pWeights[face])*pos0(faceFlux_[face]);
	}

	surfaceScalarField::Boundary& bWeights =
		Weights.boundaryFieldRef();

	forAll(bWeights, patchi)
	{
		scalarField& pWeights = bWeights[patchi];

		const scalarField& pCDweights = CDweights.boundaryField()[patchi];
		const scalarField& pFaceFlux = faceFlux_.boundaryField()[patchi];

		forAll(pWeights, face)
		{
			pWeights[face] =
				pWeights[face] * pCDweights[face]
				+ (1.0 - pWeights[face])*pos0(pFaceFlux[face]);
		}
	}

	return tLimiter;
}

template<class Type>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::limitedSurfaceInterpolationScheme<Type>::weights
(
	const GeometricField<Type, fvPatchField, volMesh>& phi
) const
{
	return this->weights
	(
		phi,
		this->mesh().surfaceInterpolation::weights(),
		this->limiter(phi)
	);
}

template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::limitedSurfaceInterpolationScheme<Type>::flux
(
	const GeometricField<Type, fvPatchField, volMesh>& phi
) const
{
	return faceFlux_ * this->interpolate(phi);
}


// ************************************************************************* //