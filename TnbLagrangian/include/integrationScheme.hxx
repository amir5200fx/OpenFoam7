#pragma once
#ifndef _integrationScheme_Header
#define _integrationScheme_Header

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
	tnbLib::integrationScheme

Description
	Base for a set of schemes which integrate simple ODEs which arise from
	semi-implcit rate expressions.

		\f[
			\frac{d \phi}{d t} = A - B \phi
		\f]

	The methods are defined in terms of the effective time-step \f$\Delta
	t_e\f$ by which the explicit rate is multiplied. The effective time-step is
	a function of the actual time step and the implicit coefficient, which must
	be implemented in each derived scheme.

		\f[
			\Delta t_e = f(\Delta t, B)
		\f]
		\f[
			\Delta \phi = (A - B \phi^n) \Delta t_e
		\f]

	This class also facilitates integration in stages. If the explicit and
	implicit coefficients, \f$A\f$ and \f$B\f$, are a summation of differing
	contributions, \f$\sum \alpha_i\f$ and \f$\sum \beta_i\f$, then the
	integration can be split up to determine the effect of each contribution.

		\f[
			\frac{d \phi_i}{d t} = \alpha_i - \beta_i \phi
		\f]
		\f[
			\Delta \phi_i = \alpha_i \Delta t -
			\beta_i \int_0^{\Delta t} \phi d t
		\f]
		\f[
			\Delta \phi_i = (\alpha_i - \beta_i \phi^n) \Delta t -
			\beta_i (A - B \phi^n) \int_0^{\Delta t} t_e dt
		\f]

	These partial calculations are defined in terms of the integral of the
	effective time-step, \f$\int_0^{\Delta t} t_e dt\f$, which is also
	implemented in every derivation.

SourceFiles
	integrationScheme.C

\*---------------------------------------------------------------------------*/

#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						 Class integrationScheme Declaration
	\*---------------------------------------------------------------------------*/

	class integrationScheme
	{
	public:

		//- Runtime type information
		//TypeName("integrationScheme");
		static const char* typeName_() { return "integrationScheme"; }
		static FoamLagrangian_EXPORT const ::tnbLib::word typeName;
		static FoamLagrangian_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		//- Declare runtime constructor selection table

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			integrationScheme,
			word,
			(),
			()
		);*/

		typedef autoPtr<integrationScheme> (*wordConstructorPtr)();
		typedef HashTable<wordConstructorPtr, word, string::hash> wordConstructorTable;
		static FoamLagrangian_EXPORT wordConstructorTable* wordConstructorTablePtr_;
		static FoamLagrangian_EXPORT void constructwordConstructorTables();
		static FoamLagrangian_EXPORT void destroywordConstructorTables();

		template <class integrationSchemeType>
		class addwordConstructorToTable
		{
		public:
			static autoPtr<integrationScheme> New() { return autoPtr<integrationScheme>(new integrationSchemeType()); }

			addwordConstructorToTable(const word& lookup = integrationSchemeType::typeName)
			{
				constructwordConstructorTables();
				if (!wordConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "integrationScheme"
						<< std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addwordConstructorToTable() { destroywordConstructorTables(); }
		};

		template <class integrationSchemeType>
		class addRemovablewordConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<integrationScheme> New() { return autoPtr<integrationScheme>(new integrationSchemeType()); }

			addRemovablewordConstructorToTable(const word& lookup = integrationSchemeType::typeName) : lookup_(lookup)
			{
				constructwordConstructorTables();
				wordConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablewordConstructorToTable()
			{
				if (wordConstructorTablePtr_) { wordConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Constructors

			//- Construct
		FoamLagrangian_EXPORT integrationScheme();

		//- Construct and return clone
		FoamLagrangian_EXPORT virtual autoPtr<integrationScheme> clone() const = 0;


		// Selectors

			//- Select an integration scheme
		static FoamLagrangian_EXPORT autoPtr<integrationScheme> New
		(
			const word& phiName,
			const dictionary& dict
		);


		//- Destructor
		FoamLagrangian_EXPORT virtual ~integrationScheme();


		// Member Functions

			//- Perform the integration explicitly
		template<class Type>
		static Type explicitDelta
		(
			const Type& phi,
			const scalar dtEff,
			const Type& Alpha,
			const scalar Beta
		);

		//- Perform the integration
		template<class Type>
		Type delta
		(
			const Type& phi,
			const scalar dt,
			const Type& Alpha,
			const scalar Beta
		) const;

		//- Perform a part of the integration
		template<class Type>
		Type partialDelta
		(
			const Type& phi,
			const scalar dt,
			const Type& Alpha,
			const scalar Beta,
			const Type& alphai,
			const scalar betai
		) const;

		//- Return the integration effective time step
		FoamLagrangian_EXPORT virtual scalar dtEff(const scalar dt, const scalar Beta) const = 0;

		//- Return the integral of the effective time step
		FoamLagrangian_EXPORT virtual scalar sumDtEff(const scalar dt, const scalar Beta) const = 0;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <integrationSchemeI.hxx>

//#ifdef NoRepository
//#include <integrationSchemeTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_integrationScheme_Header
