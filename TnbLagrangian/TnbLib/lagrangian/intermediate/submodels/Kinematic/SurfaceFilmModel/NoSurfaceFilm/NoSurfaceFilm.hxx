#pragma once
#ifndef _NoSurfaceFilm_Header
#define _NoSurfaceFilm_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
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
	tnbLib::NoSurfaceFilm

Description
	Place holder for 'none' option

SourceFiles
	NoSurfaceFilm.C

\*---------------------------------------------------------------------------*/

#include <SurfaceFilmModelTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						   Class NoSurfaceFilm Declaration
	\*---------------------------------------------------------------------------*/

	class polyPatch;  // added by amir

	template<class CloudType>
	class NoSurfaceFilm
		:
		public SurfaceFilmModel<CloudType>
	{
	protected:

		// Protected data

			//- Convenience typedef for parcel type
		typedef typename CloudType::parcelType parcelType;


	public:

		//- Runtime type information
		TypeName("none");


		// Constructors

			//- Construct from dictionary
		NoSurfaceFilm(const dictionary&, CloudType&);

		//- Construct copy
		NoSurfaceFilm(const NoSurfaceFilm<CloudType>& dm);

		//- Construct and return a clone
		virtual autoPtr<SurfaceFilmModel<CloudType>> clone() const
		{
			return autoPtr<SurfaceFilmModel<CloudType>>
				(
					new NoSurfaceFilm<CloudType>(*this)
					);
		}


		//- Destructor
		virtual ~NoSurfaceFilm();


		// Member Functions

			// Evaluation

				//- Flag to indicate whether model activates the surface film model
		virtual bool active() const;

		//- Transfer parcel from cloud to surface film
		//  Returns true if parcel is to be transferred
		virtual bool transferParcel
		(
			parcelType& p,
			const polyPatch& pp,
			bool& keepParticle
		);

		//- Set parcel properties
		virtual void setParcelProperties
		(
			parcelType& p,
			const label filmCelli
		) const;


		// I-O

			//- Write surface film info to stream
		virtual void info(Ostream& os);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <NoSurfaceFilmI.hxx>

//#ifdef NoRepository
//#include <NoSurfaceFilm.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_NoSurfaceFilm_Header
