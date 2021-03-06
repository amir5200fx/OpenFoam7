#pragma once
#ifndef _indexedParticleCloud_Header
#define _indexedParticleCloud_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
	 \\/     M anipulation  |
-------------------------------------------------------------------------------
License
	This file is part of OpenFOAM.

	OpenFOAM is free software: you can redistribute it and/or modify it
	under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
	for more details.

	You should have received a copy of the GNU General Public License
	along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
	tnbLib::indexedParticleCloud

Description
	A Cloud of particles carrying an additional index.

SourceFiles
	indexedParticleCloud.C

\*---------------------------------------------------------------------------*/

#include <CloudTemplate.hxx>
#include <indexedParticle.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						Class indexedParticleCloud Declaration
	\*---------------------------------------------------------------------------*/

	class indexedParticleCloud
		:
		public Cloud<indexedParticle>
	{
	public:

		// Constructors

			//- Construct given mesh
		indexedParticleCloud
		(
			const polyMesh&,
			const word& cloudName = "defaultCloud",
			bool readFields = true
		);

		//- Disallow default bitwise copy construction
		indexedParticleCloud(const indexedParticleCloud&) = delete;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const indexedParticleCloud&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_indexedParticleCloud_Header
