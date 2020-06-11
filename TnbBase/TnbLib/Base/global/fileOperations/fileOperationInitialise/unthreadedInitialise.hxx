#pragma once
#ifndef _unthreadedInitialise_Header
#define _unthreadedInitialise_Header

#include <fileOperationInitialise.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fileOperations
	{

		/*---------------------------------------------------------------------------*\
							 Class unthreadedInitialise Declaration
		\*---------------------------------------------------------------------------*/

		class unthreadedInitialise
			:
			public fileOperationInitialise
		{
		public:

			// Constructors

				//- Construct from components
			unthreadedInitialise(int& argc, char**& argv)
				:
				fileOperationInitialise(argc, argv)
			{}


			//- Destructor
			virtual ~unthreadedInitialise()
			{}


			// Member Functions

				//- Needs threading
			virtual bool needsThreading() const
			{
				return false;
			}
		};


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace fileOperations
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_unthreadedInitialise_Header
