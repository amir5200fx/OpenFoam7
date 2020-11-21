#pragma once
#ifndef _graph_Header
#define _graph_Header

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
	tnbLib::graph

Description
	Class to create, store and output qgraph files.

SourceFiles
	graph.C

\*---------------------------------------------------------------------------*/

#include <tnbString.hxx>
#include <point.hxx>
#include <HashPtrTable.hxx>
#include <curve.hxx>

#include <runTimeSelectionTables.hxx>  // added by amir
#include <typeInfo.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// Forward declaration of friend functions and operators

	class graph;

	Ostream& operator<<(Ostream&, const graph&);


	/*---------------------------------------------------------------------------*\
							   Class graph Declaration
	\*---------------------------------------------------------------------------*/

	class graph
		:
		public HashPtrTable<curve>
	{
		// private data

		string title_;
		string xName_;
		string yName_;

		scalarField x_;


		struct xy
		{
			scalar x_, y_;

			xy()
			{}

			// Friend Operators

			friend bool operator==(const xy& a, const xy& b)
			{
				return equal(a.x_, b.x_) && equal(a.y_, b.y_);
			}

			friend bool operator!=(const xy& a, const xy& b)
			{
				return !(a == b);
			}

			friend Istream& operator>>(Istream& is, xy& xyd)
			{
				is >> xyd.x_ >> xyd.y_;
				return is;
			}

			friend Ostream& operator<<(Ostream& os, const xy& xyd)
			{
				os << xyd.x_ << ' ' << xyd.y_;
				return os;
			}
		};


		// Private Member Functions

		FoamBase_EXPORT void readCurves(Istream&);


	public:

		// Constructors

			//- Construct from title and labels (no curves)
		FoamBase_EXPORT graph
		(
			const string& title,
			const string& xName,
			const string& yName,
			const scalarField& x
		);

		//- Construct from title, labels and y data for 1 curve
		FoamBase_EXPORT graph
		(
			const string& title,
			const string& xName,
			const string& yName,
			const scalarField& x,
			const scalarField& y
		);

		//- Construct from Istream given title and labels
		FoamBase_EXPORT graph
		(
			const string& title,
			const string& xName,
			const string& yName,
			Istream& is
		);

		//- Construct from Istream
		FoamBase_EXPORT graph(Istream& is);


		// Member Functions

			// Access

		const string& title() const
		{
			return title_;
		}

		const string& xName() const
		{
			return xName_;
		}

		const string& yName() const
		{
			return yName_;
		}


		const scalarField& x() const
		{
			return x_;
		}

		scalarField& x()
		{
			return x_;
		}


		FoamBase_EXPORT const scalarField& y() const;

		FoamBase_EXPORT scalarField& y();


		// Write

			//- Abstract base class for a graph writer
		class writer
		{

		protected:

			FoamBase_EXPORT void writeXY
			(
				const scalarField& x,
				const scalarField& y,
				Ostream&
			) const;

		public:

			//- Runtime type information
			//TypeName("writer");
			static const char* typeName_() { return "writer"; }
			static FoamBase_EXPORT const ::tnbLib::word typeName;
			static FoamBase_EXPORT int debug;
			virtual const word& type() const { return typeName; };

			//- Declare run-time constructor selection table
			/*declareRunTimeSelectionTable
			(
				autoPtr,
				writer,
				word,
				(),
				()
			);*/

			typedef autoPtr<writer> (*wordConstructorPtr)();
			typedef HashTable<wordConstructorPtr, word, string::hash> wordConstructorTable;
			static FoamBase_EXPORT wordConstructorTable* wordConstructorTablePtr_;
			static FoamBase_EXPORT void constructwordConstructorTables();
			static FoamBase_EXPORT void destroywordConstructorTables();

			template <class writerType>
			class addwordConstructorToTable
			{
			public:
				static autoPtr<writer> New() { return autoPtr<writer>(new writerType()); }

				addwordConstructorToTable(const word& lookup = writerType::typeName)
				{
					constructwordConstructorTables();
					if (!wordConstructorTablePtr_->insert(lookup, New))
					{
						std::cerr << "Duplicate entry " << lookup << " in runtime selection table " << "writer" << std::endl;
						error::safePrintStack(std::cerr);
					}
				}

				~addwordConstructorToTable() { destroywordConstructorTables(); }
			};

			template <class writerType>
			class addRemovablewordConstructorToTable
			{
				const word& lookup_;
			public:
				static autoPtr<writer> New() { return autoPtr<writer>(new writerType()); }

				addRemovablewordConstructorToTable(const word& lookup = writerType::typeName) : lookup_(lookup)
				{
					constructwordConstructorTables();
					wordConstructorTablePtr_->set(lookup, New);
				}

				~addRemovablewordConstructorToTable()
				{
					if (wordConstructorTablePtr_) { wordConstructorTablePtr_->erase(lookup_); }
				}
			};;


			// Selectors

				//- Return a reference to the selected writer
			static FoamBase_EXPORT autoPtr<writer> New
			(
				const word& writeFormat
			);


			// Constructors

				//- Construct null
			writer()
			{}


			//- Destructor
			virtual ~writer()
			{}


			// Member Functions

				// Access

					//- Return the appropriate fileName extension
					//  for this graph format
			FoamBase_EXPORT virtual const word& ext() const = 0;


			// Write

				//- Write graph in appropriate format
			FoamBase_EXPORT virtual void write(const graph&, Ostream&) const = 0;
		};

		//- Write out graph data as a simple table
		FoamBase_EXPORT void writeTable(Ostream&) const;

		//- Write graph to stream in given format
		FoamBase_EXPORT void write(Ostream&, const word& format) const;

		//- Write graph to file in given path-name and format
		FoamBase_EXPORT void write(const fileName& pName, const word& format) const;

		//- Write graph to file in given path, name and format
		FoamBase_EXPORT void write
		(
			const fileName& path,
			const word& name,
			const word& format
		) const;

		//- Helper function to convert string name into appropriate word
		static FoamBase_EXPORT word wordify(const string& sname);


		// Friend operators

			//- Ostream Operator
		friend Ostream& operator<<(Ostream&, const graph&);
	};


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_graph_Header
