#pragma once
#ifndef _generalFieldMapper_Header
#define _generalFieldMapper_Header

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
	tnbLib::generalFieldMapper

Description
	General field mapper supporting both direct and weighted mapping.

\*---------------------------------------------------------------------------*/

#include <fieldMapper.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
							   Class generalFieldMapper Declaration
	\*---------------------------------------------------------------------------*/

	//- this class is modified by amir
	class generalFieldMapper
		:
		virtual public fieldMapper
	{
		// Private Member Functions

		template<class Type>
		void map(Field<Type>& f, const Field<Type>& mapF) const;

		template<class Type>
		tmp<Field<Type>> map(const Field<Type>& f) const;


	public:

		// Constructors

			//- Null constructor
		generalFieldMapper()
		{}


		//- Destructor
		virtual ~generalFieldMapper()
		{}


		// Member Functions

		FoamBase_EXPORT virtual bool direct() const = 0;

		//- Are there unmapped values? I.e. do all size() elements get
		//  get value
		//FoamBase_EXPORT virtual bool hasUnmapped() const = 0;  modified by amir: this function is already been defined in the fieldMapper!

		FoamBase_EXPORT virtual const labelUList& directAddressing() const;

		FoamBase_EXPORT virtual const labelListList& addressing() const;

		FoamBase_EXPORT virtual const scalarListList& weights() const;


		// Member Operators

		FoamBase_EXPORT /*virtual*/ void operator()
			(
				Field<scalar>& f,
				const Field<scalar>& mapF
				) const override;

		FoamBase_EXPORT /*virtual*/ void operator()
			(
				Field<vector>& f,
				const Field<vector>& mapF
				) const override;

		FoamBase_EXPORT /*virtual*/ void operator()
			(
				Field<sphericalTensor>& f,
				const Field<sphericalTensor>& mapF
				) const override;

		FoamBase_EXPORT /*virtual*/ void operator()
			(
				Field<symmTensor>& f,
				const Field<symmTensor>& mapF
				) const override;

		FoamBase_EXPORT /*virtual*/ void operator()
			(
				Field<tensor>& f,
				const Field<tensor>& mapF
				) const override;


		FoamBase_EXPORT /*virtual*/ tmp<Field<scalar>> operator()
			(
				const Field<scalar>& mapF
				) const override;

		FoamBase_EXPORT /*virtual*/ tmp<Field<vector>> operator()
			(
				const Field<vector>& mapF
				) const override;

		FoamBase_EXPORT /*virtual*/ tmp<Field<sphericalTensor>> operator()
			(
				const Field<sphericalTensor>& mapF
				) const override;

		FoamBase_EXPORT /*virtual*/ tmp<Field<symmTensor>> operator()
			(
				const Field<symmTensor>& mapF
				) const override;

		FoamBase_EXPORT /*virtual*/ tmp<Field<tensor>> operator()
			(
				const Field<tensor>& mapF
				) const override;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <generalFieldMapperI.hxx>

//#ifdef NoRepository
//#include <generalFieldMapperTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_generalFieldMapper_Header
