#pragma once
#ifndef _streamLineParticleCloud_Header
#define _streamLineParticleCloud_Header

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
	tnbLib::streamLineParticleCloud

Description
	A Cloud of streamLine particles

SourceFiles
	streamLineCloud.C

\*---------------------------------------------------------------------------*/

#include <CloudTemplate.hxx>
#include <streamLineParticle.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class streamLineCloud Declaration
	\*---------------------------------------------------------------------------*/

	class streamLineParticleCloud
		:
		public Cloud<streamLineParticle>
	{
	public:

		//- Type of parcel the cloud was instantiated for
		typedef streamLineParticle parcelType;

		// Constructors

			//- Construct given mesh
		streamLineParticleCloud
		(
			const polyMesh&,
			const word& cloudName = "defaultCloud",
			bool readFields = true
		);

		//- Construct from mesh, cloud name, and a list of particles
		streamLineParticleCloud
		(
			const polyMesh& mesh,
			const word& cloudName,
			const IDLList<streamLineParticle>& particles
		);

		//- Disallow default bitwise copy construction
		streamLineParticleCloud(const streamLineParticleCloud&) = delete;


		// Member Operators

			//- Disallow default bitwise assignment
		void operator=(const streamLineParticleCloud&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_streamLineParticleCloud_Header
