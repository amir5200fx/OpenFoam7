#pragma once
#ifndef _sigSegv_Header
#define _sigSegv_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     | Version:     4.0
	\\  /    A nd           | Web:         http://www.foam-extend.org
	 \\/     M anipulation  | For copyright notice see file Copyright
-------------------------------------------------------------------------------
License
	This file is part of foam-extend.

	foam-extend is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by the
	Free Software Foundation, either version 3 of the License, or (at your
	option) any later version.

	foam-extend is distributed in the hope that it will be useful, but
	WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::sigSegv

Description
	Signal handler for SEGV interupt.

	The standard interupt handler is overridden to ensure that the
	runningJob file is removed.

See Also
	tnbLib::JobInfo

SourceFiles
	sigSegv.C

\*---------------------------------------------------------------------------*/

#include <OSspecific.hxx>

#include <signal.h>

typedef	void(*__p_sig_fn_t)(int);

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class sigSegv Declaration
\*---------------------------------------------------------------------------*/

	class sigSegv
	{
		// Private data

			//- Saved old signal trapping setting
		static FoamBase_EXPORT __p_sig_fn_t oldAction_;


		// Private Member Functions

		static FoamBase_EXPORT void sigSegvHandler(int);


	public:

		// Constructors

		FoamBase_EXPORT sigSegv();


		// Destructor

		FoamBase_EXPORT ~sigSegv();


		// Member functions

		FoamBase_EXPORT void set(const bool verbose);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

}

#endif // !_sigSegv_Header
