#pragma once
#ifndef _vectorTensorTransform_Header
#define _vectorTensorTransform_Header

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
	tnbLib::vectorTensorTransform

Description
	Vector-tensor class used to perform translations and rotations in
	3D space.

SourceFiles
	vectorTensorTransformI.H
	vectorTensorTransform.C
	vectorTensorTransformTemplates.C

\*---------------------------------------------------------------------------*/

#include <tensor.hxx>
#include <word.hxx>
#include <contiguous.hxx>
#include <pointField.hxx>
#include <transformField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class vectorTensorTransform;
	FoamBase_EXPORT Istream& operator>>(Istream& is, vectorTensorTransform&);
	FoamBase_EXPORT Ostream& operator<<(Ostream& os, const vectorTensorTransform& C);


	/*---------------------------------------------------------------------------*\
						Class vectorTensorTransform Declaration
	\*---------------------------------------------------------------------------*/

	class vectorTensorTransform
	{
		// private data

			//- Translation vector
		vector t_;

		//- Rotation tensor
		tensor R_;

		//- Recording if the transform has non-identity transform to
		//  allow its calculation to be skipped, which is the majority
		//  of the expected cases
		bool hasR_;


	public:

		// Static Data Members

		static FoamBase_EXPORT const char* const typeName;

		static FoamBase_EXPORT const vectorTensorTransform zero;

		static FoamBase_EXPORT const vectorTensorTransform I;


		// Constructors

			//- Construct null
		inline vectorTensorTransform();

		//- Construct given a translation vector, rotation tensor and
		//  hasR bool
		inline vectorTensorTransform
		(
			const vector& t,
			const tensor& R,
			bool hasR = true
		);

		//- Construct a pure translation vectorTensorTransform given a
		//  translation vector
		inline explicit vectorTensorTransform(const vector& t);

		//- Construct a pure rotation vectorTensorTransform given a
		//  rotation tensor
		inline explicit vectorTensorTransform(const tensor& R);

		//- Construct from Istream
		vectorTensorTransform(Istream&);


		// Member Functions

			// Access

		inline const vector& t() const;

		inline const tensor& R() const;

		inline bool hasR() const;


		// Edit

		inline vector& t();

		inline tensor& R();


		// Transform

			//- Transform the given position
		inline vector transformPosition(const vector& v) const;

		//- Transform the given pointField
		inline pointField transformPosition(const pointField& pts) const;

		//- Inverse transform the given position
		inline vector invTransformPosition(const vector& v) const;

		//- Inverse transform the given pointField
		inline pointField invTransformPosition(const pointField& pts) const;

		//- Transform the given type
		template<class Type>
		Type transform(const Type&) const;

		//- Transform the given field
		template<class Type>
		tmp<Field<Type>> transform(const Field<Type>&) const;

		//- Inverse transform the given type
		template<class Type>
		Type invTransform(const Type&) const;

		//- Inverse transform the given field
		template<class Type>
		tmp<Field<Type>> invTransform(const Field<Type>&) const;


		// Member Operators

		inline void operator&=(const vectorTensorTransform&);

		inline void operator=(const vector&);
		inline void operator+=(const vector&);
		inline void operator-=(const vector&);

		inline void operator=(const tensor&);
		inline void operator&=(const tensor&);


		// IOstream Operators

		friend FoamBase_EXPORT Istream& operator>>(Istream& is, vectorTensorTransform&);

		friend FoamBase_EXPORT Ostream& operator<<(Ostream& os, const vectorTensorTransform&);
	};


	// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

	//- Return the inverse of the given vectorTensorTransform
	inline vectorTensorTransform inv(const vectorTensorTransform& tr);


	//- Return a string representation of a vectorTensorTransform
	FoamBase_EXPORT word name(const vectorTensorTransform&);


	//- Data associated with vectorTensorTransform type are contiguous
	template<>
	inline bool contiguous<vectorTensorTransform>() { return true; }

	//- Template specialisations
	template<>
	FoamBase_EXPORT tmp<Field<bool>> vectorTensorTransform::transform(const Field<bool>&) const;
	template<>
	FoamBase_EXPORT tmp<Field<label>> vectorTensorTransform::transform(const Field<label>&) const;
	template<>
	FoamBase_EXPORT tmp<Field<scalar>> vectorTensorTransform::transform(const Field<scalar>&)
		const;


	// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

	inline bool operator==
		(
			const vectorTensorTransform& tr1,
			const vectorTensorTransform& tr2
			);


	inline bool operator!=
		(
			const vectorTensorTransform& tr1,
			const vectorTensorTransform& tr2

			);


	inline vectorTensorTransform operator+
		(
			const vectorTensorTransform& tr,
			const vector& t
			);


	inline vectorTensorTransform operator+
		(
			const vector& t,
			const vectorTensorTransform& tr
			);


	inline vectorTensorTransform operator-
		(
			const vectorTensorTransform& tr,
			const vector& t
			);


	inline vectorTensorTransform operator&
		(
			const vectorTensorTransform& tr1,
			const vectorTensorTransform& tr2
			);


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <vectorTensorTransformI.hxx>
#include <vectorTensorTransformTemplatesI.hxx>

//#ifdef NoRepository
//#include <vectorTensorTransformTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_vectorTensorTransform_Header
