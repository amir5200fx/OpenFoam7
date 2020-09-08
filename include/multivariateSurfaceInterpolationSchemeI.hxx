#pragma once
#include <fv.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::multivariateSurfaceInterpolationScheme<Type>::
multivariateSurfaceInterpolationScheme
(
	const fvMesh& mesh,
	const multivariateSurfaceInterpolationScheme<Type>::fieldTable& vtfs,
	const surfaceScalarField&,
	Istream&
)
	:
	mesh_(mesh),
	fields_(vtfs)
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::multivariateSurfaceInterpolationScheme<Type>>
tnbLib::multivariateSurfaceInterpolationScheme<Type>::New
(
	const fvMesh& mesh,
	const multivariateSurfaceInterpolationScheme<Type>::fieldTable& vtfs,
	const surfaceScalarField& faceFlux,
	Istream& schemeData
)
{
	if (fv::debug)
	{
		InfoInFunction
			<< "Constructing surfaceInterpolationScheme<Type>" << endl;
	}

	const word schemeName(schemeData);

	typename IstreamConstructorTable::iterator constructorIter =
		IstreamConstructorTablePtr_->find(schemeName);

	if (constructorIter == IstreamConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			schemeData
		) << "Unknown discretisation scheme " << schemeName << nl << nl
			<< "Valid schemes are :" << endl
			<< IstreamConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return constructorIter()(mesh, vtfs, faceFlux, schemeData);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::multivariateSurfaceInterpolationScheme<Type>::
~multivariateSurfaceInterpolationScheme()
{}


// ************************************************************************* //