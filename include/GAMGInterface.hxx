#pragma once
#ifndef _GAMGInterface_Header
#define _GAMGInterface_Header

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
	tnbLib::GAMGInterface

Description
	 Abstract base class for GAMG agglomerated interfaces.

SourceFiles
	GAMGInterface.C
	newAmgInterface.C

\*---------------------------------------------------------------------------*/

#include <autoPtr.hxx>
#include <lduInterfacePtrsList.hxx>
#include <GAMGAgglomeration.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	/*---------------------------------------------------------------------------*\
						  Class GAMGInterface Declaration
	\*---------------------------------------------------------------------------*/

	class GAMGInterface
		:
		public lduInterface
	{

	protected:

		// Protected data

			//- My index in coarseInterfaces
		const label index_;

		//- All interfaces
		const lduInterfacePtrsList& coarseInterfaces_;

		//- Face-cell addressing
		labelList faceCells_;

		//- Face restrict addressing
		labelList faceRestrictAddressing_;


	public:

		//- Runtime type information
		//TypeName("GAMGInterface");
		static const char* typeName_() { return "GAMGInterface"; }
		static FoamBase_EXPORT const ::tnbLib::word typeName;
		static FoamBase_EXPORT int debug;
		virtual const word& type() const { return typeName; };


		// Declare run-time constructor selection tables

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			GAMGInterface,
			lduInterface,
			(
				const label index,
				const lduInterfacePtrsList& coarseInterfaces,
				const lduInterface& fineInterface,
				const labelField& localRestrictAddressing,
				const labelField& neighbourRestrictAddressing,
				const label fineLevelIndex,
				const label coarseComm
				),
				(
					index,
					coarseInterfaces,
					fineInterface,
					localRestrictAddressing,
					neighbourRestrictAddressing,
					fineLevelIndex,
					coarseComm
					)
		);*/

		typedef autoPtr<GAMGInterface> (*lduInterfaceConstructorPtr)(const label index,
		                                                             const lduInterfacePtrsList& coarseInterfaces,
		                                                             const lduInterface& fineInterface,
		                                                             const labelField& localRestrictAddressing,
		                                                             const labelField& neighbourRestrictAddressing,
		                                                             const label fineLevelIndex, const label coarseComm);
		typedef HashTable<lduInterfaceConstructorPtr, word, string::hash> lduInterfaceConstructorTable;
		static FoamBase_EXPORT lduInterfaceConstructorTable* lduInterfaceConstructorTablePtr_;
		static FoamBase_EXPORT void constructlduInterfaceConstructorTables();
		static FoamBase_EXPORT void destroylduInterfaceConstructorTables();

		template <class GAMGInterfaceType>
		class addlduInterfaceConstructorToTable
		{
		public:
			static autoPtr<GAMGInterface> New(const label index, const lduInterfacePtrsList& coarseInterfaces,
			                                  const lduInterface& fineInterface, const labelField& localRestrictAddressing,
			                                  const labelField& neighbourRestrictAddressing, const label fineLevelIndex,
			                                  const label coarseComm)
			{
				return autoPtr<GAMGInterface>(new GAMGInterfaceType(index, coarseInterfaces, fineInterface, localRestrictAddressing,
				                                                    neighbourRestrictAddressing, fineLevelIndex, coarseComm));
			}

			addlduInterfaceConstructorToTable(const word& lookup = GAMGInterfaceType::typeName)
			{
				constructlduInterfaceConstructorTables();
				if (!lduInterfaceConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "GAMGInterface" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addlduInterfaceConstructorToTable() { destroylduInterfaceConstructorTables(); }
		};

		template <class GAMGInterfaceType>
		class addRemovablelduInterfaceConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<GAMGInterface> New(const label index, const lduInterfacePtrsList& coarseInterfaces,
			                                  const lduInterface& fineInterface, const labelField& localRestrictAddressing,
			                                  const labelField& neighbourRestrictAddressing, const label fineLevelIndex,
			                                  const label coarseComm)
			{
				return autoPtr<GAMGInterface>(new GAMGInterfaceType(index, coarseInterfaces, fineInterface, localRestrictAddressing,
				                                                    neighbourRestrictAddressing, fineLevelIndex, coarseComm));
			}

			addRemovablelduInterfaceConstructorToTable(const word& lookup = GAMGInterfaceType::typeName) : lookup_(lookup)
			{
				constructlduInterfaceConstructorTables();
				lduInterfaceConstructorTablePtr_->set(lookup, New);
			}

			~addRemovablelduInterfaceConstructorToTable()
			{
				if (lduInterfaceConstructorTablePtr_) { lduInterfaceConstructorTablePtr_->erase(lookup_); }
			}
		};;

		/*declareRunTimeSelectionTable
		(
			autoPtr,
			GAMGInterface,
			Istream,
			(
				const label index,
				const lduInterfacePtrsList& coarseInterfaces,
				Istream& is
				),
				(
					index,
					coarseInterfaces,
					is
					)
		);*/

		typedef autoPtr<GAMGInterface> (*IstreamConstructorPtr)(const label index,
		                                                        const lduInterfacePtrsList& coarseInterfaces, Istream& is);
		typedef HashTable<IstreamConstructorPtr, word, string::hash> IstreamConstructorTable;
		static FoamBase_EXPORT IstreamConstructorTable* IstreamConstructorTablePtr_;
		static FoamBase_EXPORT void constructIstreamConstructorTables();
		static FoamBase_EXPORT void destroyIstreamConstructorTables();

		template <class GAMGInterfaceType>
		class addIstreamConstructorToTable
		{
		public:
			static autoPtr<GAMGInterface> New(const label index, const lduInterfacePtrsList& coarseInterfaces, Istream& is)
			{
				return autoPtr<GAMGInterface>(new GAMGInterfaceType(index, coarseInterfaces, is));
			}

			addIstreamConstructorToTable(const word& lookup = GAMGInterfaceType::typeName)
			{
				constructIstreamConstructorTables();
				if (!IstreamConstructorTablePtr_->insert(lookup, New))
				{
					std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "GAMGInterface" << std::endl;
					error::safePrintStack(std::cerr);
				}
			}

			~addIstreamConstructorToTable() { destroyIstreamConstructorTables(); }
		};

		template <class GAMGInterfaceType>
		class addRemovableIstreamConstructorToTable
		{
			const word& lookup_;
		public:
			static autoPtr<GAMGInterface> New(const label index, const lduInterfacePtrsList& coarseInterfaces, Istream& is)
			{
				return autoPtr<GAMGInterface>(new GAMGInterfaceType(index, coarseInterfaces, is));
			}

			addRemovableIstreamConstructorToTable(const word& lookup = GAMGInterfaceType::typeName) : lookup_(lookup)
			{
				constructIstreamConstructorTables();
				IstreamConstructorTablePtr_->set(lookup, New);
			}

			~addRemovableIstreamConstructorToTable()
			{
				if (IstreamConstructorTablePtr_) { IstreamConstructorTablePtr_->erase(lookup_); }
			}
		};;


		// Selectors

			//- Return a pointer to a new interface created on freestore given
			//  the fine interface
		static FoamBase_EXPORT autoPtr<GAMGInterface> New
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			const lduInterface& fineInterface,
			const labelField& localRestrictAddressing,
			const labelField& neighbourRestrictAddressing,
			const label fineLevelIndex,
			const label coarseComm
		);

		//- Return a pointer to a new interface created on freestore given
		//  the fine interface
		static FoamBase_EXPORT autoPtr<GAMGInterface> New
		(
			const word& coupleType,
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			Istream& is
		);


		// Constructors

			//- Construct from interfaces, restrict addressing set later on
		GAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces
		)
			:
			index_(index),
			coarseInterfaces_(coarseInterfaces)
		{}


		//- Construct from interfaces and restrict addressing
		GAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			const labelUList& faceCells,
			const labelUList& faceRestrictAddressing
		)
			:
			index_(index),
			coarseInterfaces_(coarseInterfaces),
			faceCells_(faceCells),
			faceRestrictAddressing_(faceRestrictAddressing)
		{}


		//- Construct from Istream
		FoamBase_EXPORT GAMGInterface
		(
			const label index,
			const lduInterfacePtrsList& coarseInterfaces,
			Istream& is
		);

		//- Disallow default bitwise copy construction
		FoamBase_EXPORT GAMGInterface(const GAMGInterface&) = delete;


		// Member Functions

			// Access

				//- Return size
		virtual label size() const
		{
			return faceCells_.size();
		}

		virtual label index() const
		{
			return index_;
		}

		virtual const lduInterfacePtrsList& coarseInterfaces() const
		{
			return coarseInterfaces_;
		}

		//- Return faceCell addressing
		virtual const labelUList& faceCells() const
		{
			return faceCells_;
		}

		//- Return (local)face restrict addressing
		virtual const labelList& faceRestrictAddressing() const
		{
			return faceRestrictAddressing_;
		}

		//- Return non-const access to face restrict addressing
		virtual labelList& faceRestrictAddressing()
		{
			return faceRestrictAddressing_;
		}

		//- Return the interface internal field of the given field
		template<class Type>
		tmp<Field<Type>> interfaceInternalField
		(
			const UList<Type>& internalData
		) const;

		//- Get the interface internal field of the given field
		template<class Type>
		void interfaceInternalField
		(
			const UList<Type>& internalData,
			List<Type>&
		) const;

		//- Return the values of the given internal data adjacent to
		//  the interface as a field
		FoamBase_EXPORT virtual tmp<labelField> interfaceInternalField
		(
			const labelUList& internalData
		) const;


		// Agglomeration

			//- Merge the next level with this level
			//  combining the face-restrict addressing
			//  and copying the face-cell addressing
		FoamBase_EXPORT void combine(const GAMGInterface&);

		//- Agglomerating the given fine-level coefficients and return
		FoamBase_EXPORT virtual tmp<scalarField> agglomerateCoeffs
		(
			const scalarField& fineCoeffs
		) const;


		// I/O

			//- Write to stream
		FoamBase_EXPORT virtual void write(Ostream&) const = 0;


		// Member Operators

			//- Disallow default bitwise assignment
		FoamBase_EXPORT void operator=(const GAMGInterface&) = delete;
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <GAMGInterfaceTemplatesI.hxx>

//#ifdef NoRepository
//#include <GAMGInterfaceTemplates.cxx>
//#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_GAMGInterface_Header
