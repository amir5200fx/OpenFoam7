#include <divScheme.hxx>

#include <fv.hxx>
#include <HashTable.hxx>
#include <linear.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	namespace fv
	{

		// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

		template<class Type>
		tmp<divScheme<Type>> divScheme<Type>::New
		(
			const fvMesh& mesh,
			Istream& schemeData
		)
		{
			if (fv::debug)
			{
				InfoInFunction << "Constructing divScheme<Type>" << endl;
			}

			if (schemeData.eof())
			{
				FatalIOErrorInFunction
				(
					schemeData
				) << "Div scheme not specified" << endl << endl
					<< "Valid div schemes are :" << endl
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
				) << "unknown div scheme "
					<< schemeName << nl << nl
					<< "Valid div schemes are :" << endl
					<< IstreamConstructorTablePtr_->sortedToc()
					<< exit(FatalIOError);
			}

			return cstrIter()(mesh, schemeData);
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class Type>
		divScheme<Type>::~divScheme()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fv

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //