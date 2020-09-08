#pragma once
#include <fv.hxx>
#include <HashTable.hxx>
#include <linear.hxx>

#include <surfaceMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class Type>
		convectionScheme<Type>::convectionScheme(const convectionScheme& cs)
			:
			tmp<convectionScheme<Type>>::refCount(),
			mesh_(cs.mesh_)
		{}


		// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<convectionScheme<Type>> convectionScheme<Type>::New
		(
			const fvMesh& mesh,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		)
		{
			if (fv::debug)
			{
				InfoInFunction << "Constructing convectionScheme<Type>" << endl;
			}

			if (schemeData.eof())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Convection scheme not specified" << endl << endl
					<< "Valid convection schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			const word schemeName(schemeData);

			typename IstreamConstructorTable::iterator cstrIter =
				IstreamConstructorTablePtr_->find(schemeName);

			if (cstrIter == IstreamConstructorTablePtr_->end())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Unknown convection scheme " << schemeName << nl << nl
					<< "Valid convection schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			return cstrIter()(mesh, faceFlux, schemeData);
		}


		template<class Type>
		tmp<convectionScheme<Type>> convectionScheme<Type>::New
		(
			const fvMesh& mesh,
			const typename multivariateSurfaceInterpolationScheme<Type>::
			fieldTable& fields,
			const surfaceScalarField& faceFlux,
			Istream& schemeData
		)
		{
			if (fv::debug)
			{
				InfoInFunction << "Constructing convectionScheme<Type>" << endl;
			}

			if (schemeData.eof())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Convection scheme not specified" << endl << endl
					<< "Valid convection schemes are :" << endl
					<< MultivariateConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			const word schemeName(schemeData);

			typename MultivariateConstructorTable::iterator cstrIter =
				MultivariateConstructorTablePtr_->find(schemeName);

			if (cstrIter == MultivariateConstructorTablePtr_->end())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Unknown convection scheme " << schemeName << nl << nl
					<< "Valid convection schemes are :" << endl
					<< MultivariateConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			return cstrIter()(mesh, fields, faceFlux, schemeData);
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		convectionScheme<Type>::~convectionScheme()
		{}


		// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

		template<class Type>
		void convectionScheme<Type>::operator=(const convectionScheme<Type>& cs)
		{
			if (this == &cs)
			{
				FatalErrorInFunction
					<< "attempted assignment to self"
					<< abort(FatalError);
			}
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //