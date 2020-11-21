#pragma once
#ifndef _sigQuit_Header
#define _sigQuit_Header

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
	tnbLib::sigQuit

Description
	Signal handler for QUIT interupt.

	The standard interupt handler is overridden to ensure that the
	runningJob file is removed.

See Also
	tnbLib::JobInfo

SourceFiles
	sigQuit.C

\*---------------------------------------------------------------------------*/

#include <OSspecific.hxx>

#include <signal.h>

typedef	void(*__p_sig_fn_t)(int);

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class sigQuit Declaration
\*---------------------------------------------------------------------------*/

	class sigQuit
	{
		// Private data

			//- Saved old signal trapping setting
		static FoamBase_EXPORT __p_sig_fn_t oldAction_;


		// Private Member Functions

		static FoamBase_EXPORT void sigQuitHandler(int);


	public:

		// Constructors

		FoamBase_EXPORT sigQuit();


		// Destructor

		FoamBase_EXPORT ~sigQuit();


		// Member functions

		FoamBase_EXPORT void set(const bool verbose);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
}

#endif // !_sigQuit_Header
