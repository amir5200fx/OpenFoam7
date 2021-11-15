#pragma once
#ifndef _cellSizeCalculationType_Header
#define _cellSizeCalculationType_Header

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2019 OpenFOAM Foundation
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
    tnbLib::cellSizeCalculationType

Description
    Abstract base class for specifying target cell sizes

SourceFiles
    cellSizeCalculationType.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <autoPtr.hxx>
#include <runTimeSelectionTables.hxx>
#include <triSurfaceFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

    class triSurfaceMesh;

    /*---------------------------------------------------------------------------*\
                         Class cellSizeCalculationType Declaration
    \*---------------------------------------------------------------------------*/

    class cellSizeCalculationType
    {

    protected:

        const dictionary& cellSizeCalculationTypeDict_;

        //- Reference to the triSurfaceMesh
        const triSurfaceMesh& surface_;

        const scalar& defaultCellSize_;


    public:

        //- Runtime type information
        /*TypeName("cellSizeCalculationType");*/
        static const char* typeName_() { return "cellSizeCalculationType"; }
        static FoamFoamyMesh_EXPORT const ::tnbLib::word typeName;
        static FoamFoamyMesh_EXPORT int debug;
        virtual const word& type() const { return typeName; };


        // Declare run-time constructor selection table

        /*declareRunTimeSelectionTable
        (
            autoPtr,
            cellSizeCalculationType,
            dictionary,
            (
                const dictionary& cellSizeCalculationTypeDict,
                const triSurfaceMesh& surface,
                const scalar& defaultCellSize
                ),
            (cellSizeCalculationTypeDict, surface, defaultCellSize)
        );*/
        typedef autoPtr<cellSizeCalculationType> (*dictionaryConstructorPtr)(
	        const dictionary& cellSizeCalculationTypeDict, const triSurfaceMesh& surface,
	        const scalar& defaultCellSize);
        typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
        static FoamFoamyMesh_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
        static FoamFoamyMesh_EXPORT void constructdictionaryConstructorTables();
        static FoamFoamyMesh_EXPORT void destroydictionaryConstructorTables();

        template <class cellSizeCalculationTypeType>
        class adddictionaryConstructorToTable
        {
        public:
	        static autoPtr<cellSizeCalculationType> New(const dictionary& cellSizeCalculationTypeDict,
	                                                    const triSurfaceMesh& surface, const scalar& defaultCellSize)
	        {
		        return autoPtr<cellSizeCalculationType>(
			        new cellSizeCalculationTypeType(cellSizeCalculationTypeDict, surface, defaultCellSize));
	        }

	        adddictionaryConstructorToTable(const word& lookup = cellSizeCalculationTypeType::typeName)
	        {
		        constructdictionaryConstructorTables();
		        if (!dictionaryConstructorTablePtr_->insert(lookup, New))
		        {
			        std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
				        "cellSizeCalculationType" << std::endl;
			        error::safePrintStack(std::cerr);
		        }
	        }

	        ~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
        };

        template <class cellSizeCalculationTypeType>
        class addRemovabledictionaryConstructorToTable
        {
	        const word& lookup_;
        public:
	        static autoPtr<cellSizeCalculationType> New(const dictionary& cellSizeCalculationTypeDict,
	                                                    const triSurfaceMesh& surface, const scalar& defaultCellSize)
	        {
		        return autoPtr<cellSizeCalculationType>(
			        new cellSizeCalculationTypeType(cellSizeCalculationTypeDict, surface, defaultCellSize));
	        }

	        addRemovabledictionaryConstructorToTable(
		        const word& lookup = cellSizeCalculationTypeType::typeName) : lookup_(lookup)
	        {
		        constructdictionaryConstructorTables();
		        dictionaryConstructorTablePtr_->set(lookup, New);
	        }

	        ~addRemovabledictionaryConstructorToTable()
	        {
		        if (dictionaryConstructorTablePtr_) { dictionaryConstructorTablePtr_->erase(lookup_); }
	        }
        };;


        // Constructors

            //- Construct from components
        FoamFoamyMesh_EXPORT cellSizeCalculationType
        (
            const word& type,
            const dictionary& cellSizeCalculationTypeDict,
            const triSurfaceMesh& surface,
            const scalar& defaultCellSize
        );

        //- Disallow default bitwise copy construction
        cellSizeCalculationType(const cellSizeCalculationType&) = delete;


        // Selectors

            //- Return a reference to the selected cellSizeCalculationType
        static FoamFoamyMesh_EXPORT autoPtr<cellSizeCalculationType> New
        (
            const dictionary& cellSizeCalculationTypeDict,
            const triSurfaceMesh& surface,
            const scalar& defaultCellSize
        );


        //- Destructor
        FoamFoamyMesh_EXPORT virtual ~cellSizeCalculationType();


        // Member Functions

            //- Load the cell size
        virtual tmp<triSurfacePointScalarField> load() = 0;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const cellSizeCalculationType&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif // !_cellSizeCalculationType_Header
