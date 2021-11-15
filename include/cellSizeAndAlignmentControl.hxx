#pragma once
#ifndef _cellSizeAndAlignmentControl_Header
#define _cellSizeAndAlignmentControl_Header

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
    tnbLib::cellSizeAndAlignmentControl

Description

SourceFiles
    cellSizeAndAlignmentControlI.H
    cellSizeAndAlignmentControl.C

\*---------------------------------------------------------------------------*/

#include <FoamyMesh_Module.hxx>

#include <dictionary.hxx>
#include <conformationSurfaces.hxx>
#include <Time.hxx>
#include <quaternion.hxx>
#include <triadField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{


    /*---------------------------------------------------------------------------*\
                    Class cellSizeAndAlignmentControl Declaration
    \*---------------------------------------------------------------------------*/

    class cellSizeAndAlignmentControl
    {
    protected:

        const Time& runTime_;

        const scalar& defaultCellSize_;

        Switch forceInitialPointInsertion_;


    private:

        // Private Data

        const word name_;


    public:

        //- Runtime type information
        /*TypeName("cellSizeAndAlignmentControl");*/
        static const char* typeName_() { return "cellSizeAndAlignmentControl"; }
        static FoamFoamyMesh_EXPORT const ::tnbLib::word typeName;
        static FoamFoamyMesh_EXPORT int debug;
        virtual const word& type() const { return typeName; };


        // Declare run-time constructor selection table

        /*declareRunTimeSelectionTable
        (
            autoPtr,
            cellSizeAndAlignmentControl,
            dictionary,
            (
                const Time& runTime,
                const word& name,
                const dictionary& controlFunctionDict,
                const conformationSurfaces& geometryToConformTo,
                const scalar& defaultCellSize
                ),
            (
                runTime,
                name,
                controlFunctionDict,
                geometryToConformTo,
                defaultCellSize
                )
        );*/
        typedef autoPtr<cellSizeAndAlignmentControl> (*dictionaryConstructorPtr)(
	        const Time& runTime, const word& name, const dictionary& controlFunctionDict,
	        const conformationSurfaces& geometryToConformTo, const scalar& defaultCellSize);
        typedef HashTable<dictionaryConstructorPtr, word, string::hash> dictionaryConstructorTable;
        static FoamFoamyMesh_EXPORT dictionaryConstructorTable* dictionaryConstructorTablePtr_;
        static FoamFoamyMesh_EXPORT void constructdictionaryConstructorTables();
        static FoamFoamyMesh_EXPORT void destroydictionaryConstructorTables();

        template <class cellSizeAndAlignmentControlType>
        class adddictionaryConstructorToTable
        {
        public:
	        static autoPtr<cellSizeAndAlignmentControl> New(const Time& runTime, const word& name,
	                                                        const dictionary& controlFunctionDict,
	                                                        const conformationSurfaces& geometryToConformTo,
	                                                        const scalar& defaultCellSize)
	        {
		        return autoPtr<cellSizeAndAlignmentControl>(
			        new cellSizeAndAlignmentControlType(runTime, name, controlFunctionDict, geometryToConformTo,
			                                            defaultCellSize));
	        }

	        adddictionaryConstructorToTable(const word& lookup = cellSizeAndAlignmentControlType::typeName)
	        {
		        constructdictionaryConstructorTables();
		        if (!dictionaryConstructorTablePtr_->insert(lookup, New))
		        {
			        std::cerr << "Duplicate entry " << lookup << " in runtime selection table " <<
				        "cellSizeAndAlignmentControl" << std::endl;
			        error::safePrintStack(std::cerr);
		        }
	        }

	        ~adddictionaryConstructorToTable() { destroydictionaryConstructorTables(); }
        };

        template <class cellSizeAndAlignmentControlType>
        class addRemovabledictionaryConstructorToTable
        {
	        const word& lookup_;
        public:
	        static autoPtr<cellSizeAndAlignmentControl> New(const Time& runTime, const word& name,
	                                                        const dictionary& controlFunctionDict,
	                                                        const conformationSurfaces& geometryToConformTo,
	                                                        const scalar& defaultCellSize)
	        {
		        return autoPtr<cellSizeAndAlignmentControl>(
			        new cellSizeAndAlignmentControlType(runTime, name, controlFunctionDict, geometryToConformTo,
			                                            defaultCellSize));
	        }

	        addRemovabledictionaryConstructorToTable(
		        const word& lookup = cellSizeAndAlignmentControlType::typeName) : lookup_(lookup)
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

            //- Construct from dictionary and references to conformalVoronoiMesh and
            //  searchableSurfaces
        FoamFoamyMesh_EXPORT cellSizeAndAlignmentControl
        (
            const Time& runTime,
            const word& name,
            const dictionary& controlFunctionDict,
            const conformationSurfaces& geometryToConformTo,
            const scalar& defaultCellSize
        );

        //- Disallow default bitwise copy construction
        cellSizeAndAlignmentControl
        (
            const cellSizeAndAlignmentControl&
        ) = delete;


        // Selectors

            //- Return a reference to the selected cellShapeControl
        static FoamFoamyMesh_EXPORT autoPtr<cellSizeAndAlignmentControl> New
        (
            const Time& runTime,
            const word& name,
            const dictionary& controlFunctionDict,
            const conformationSurfaces& geometryToConformTo,
            const scalar& defaultCellSize
        );


        //- Destructor
        FoamFoamyMesh_EXPORT virtual ~cellSizeAndAlignmentControl();


        // Member Functions

            // Access

        const word& name() const
        {
            return name_;
        }

        const Switch& forceInitialPointInsertion() const
        {
            return forceInitialPointInsertion_;
        }


        // Query

        virtual label maxPriority() const = 0;

        virtual void cellSizeFunctionVertices
        (
            DynamicList<tnbLib::point>& pts,
            DynamicList<scalar>& sizes
        ) const = 0;

        virtual void initialVertices
        (
            pointField& pts,
            scalarField& sizes,
            triadField& alignments
        ) const = 0;


        // Member Operators

            //- Disallow default bitwise assignment
        void operator=(const cellSizeAndAlignmentControl&) = delete;
    };


    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
#endif // !_cellSizeAndAlignmentControl_Header
