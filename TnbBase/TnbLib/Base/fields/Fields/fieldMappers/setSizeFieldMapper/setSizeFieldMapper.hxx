#pragma once
#ifndef _setSizeFieldMapper_Header
#define _setSizeFieldMapper_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2019 OpenFOAM Foundation
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
	tnbLib::setSizeFieldMapper

Description
	Field sizing mapper which sets the field size and does not map values.

\*---------------------------------------------------------------------------*/

#include <fieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class setSizeFieldMapper Declaration
	\*---------------------------------------------------------------------------*/

	class setSizeFieldMapper
		:
		virtual public fieldMapper
	{
		// Private member data

			//- The size the mapper will set the fields to have
		label size_;


		// Private Member Functions

		template<class Type>
		void setSize(Field<Type>& f) const;

		template<class Type>
		tmp<Field<Type>> setSize() const;


	public:

		// Constructors

			//- Construct given size
		FoamBase_EXPORT setSizeFieldMapper(const label size);


		//- Destructor
		virtual ~setSizeFieldMapper()
		{}


		// Member Functions

			//- All values are unmapped
		virtual bool hasUnmapped() const
		{
			return true;
		}


		// Member Operators

		FoamBase_EXPORT virtual void operator()
			(
				Field<scalar>& f,
				const Field<scalar>& mapF
				) const;

		FoamBase_EXPORT virtual void operator()
			(
				Field<vector>& f,
				const Field<vector>& mapF
				) const;

		FoamBase_EXPORT virtual void operator()
			(
				Field<sphericalTensor>& f,
				const Field<sphericalTensor>& mapF
				) const;

		FoamBase_EXPORT virtual void operator()
			(
				Field<symmTensor>& f,
				const Field<symmTensor>& mapF
				) const;

		FoamBase_EXPORT virtual void operator()
			(
				Field<tensor>& f,
				const Field<tensor>& mapF
				) const;


		FoamBase_EXPORT virtual tmp<Field<scalar>> operator()
			(
				const Field<scalar>& mapF
				) const;

		FoamBase_EXPORT virtual tmp<Field<vector>> operator()
			(
				const Field<vector>& mapF
				) const;

		FoamBase_EXPORT virtual tmp<Field<sphericalTensor>> operator()
			(
				const Field<sphericalTensor>& mapF
				) const;

		FoamBase_EXPORT virtual tmp<Field<symmTensor>> operator()
			(
				const Field<symmTensor>& mapF
				) const;

		FoamBase_EXPORT virtual tmp<Field<tensor>> operator()
			(
				const Field<tensor>& mapF
				) const;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <setSizeFieldMapperI.hxx>

//#ifdef NoRepository
//#include <setSizeFieldMapperTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_setSizeFieldMapper_Header
