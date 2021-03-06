#pragma once
#ifndef _passiveParticleCloud_Header
#define _passiveParticleCloud_Header

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
	tnbLib::passiveParticleCloud

Description
	A Cloud of passive particles

SourceFiles
	passiveParticleCloud.C

\*---------------------------------------------------------------------------*/

#include <CloudTemplate.hxx>
#include <passiveParticle.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
					   Class passiveParticleCloud Declaration
	\*---------------------------------------------------------------------------*/

	class passiveParticleCloud
		:
		public Cloud<passiveParticle>
	{
	public:

		// Constructors

			//- Construct given mesh
		FoamLagrangian_EXPORT passiveParticleCloud
		(
			const polyMesh&,
			const word& cloudName = "defaultCloud",
			bool readFields = true
		);

		//- Construct from mesh, cloud name, and a list of particles
		FoamLagrangian_EXPORT passiveParticleCloud
		(
			const polyMesh& mesh,
			const word& cloudName,
			const IDLList<passiveParticle>& particles
		);

		//- Disallow default bitwise copy construction
		FoamLagrangian_EXPORT passiveParticleCloud(const passiveParticleCloud&) = delete;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamLagrangian_EXPORT void operator=(const passiveParticleCloud&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_passiveParticleCloud_Header
