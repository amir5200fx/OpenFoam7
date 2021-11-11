#pragma once
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2012-2018 OpenFOAM Foundation
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

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::dictionary& tnbLib::cvControls::foamyHexMeshDict() const
{
    return foamyHexMeshDict_;
}


inline tnbLib::scalar tnbLib::cvControls::pointPairDistanceCoeff() const
{
    return pointPairDistanceCoeff_;
}


inline tnbLib::scalar tnbLib::cvControls::mixedFeaturePointPPDistanceCoeff() const
{
    return mixedFeaturePointPPDistanceCoeff_;
}


inline tnbLib::scalar tnbLib::cvControls::featurePointExclusionDistanceCoeff() const
{
    return featurePointExclusionDistanceCoeff_;
}


inline tnbLib::scalar tnbLib::cvControls::featureEdgeExclusionDistanceCoeff() const
{
    return featureEdgeExclusionDistanceCoeff_;
}


inline tnbLib::Switch tnbLib::cvControls::guardFeaturePoints() const
{
    return guardFeaturePoints_;
}

inline tnbLib::Switch tnbLib::cvControls::edgeAiming() const
{
    return edgeAiming_;
}

inline tnbLib::Switch tnbLib::cvControls::snapFeaturePoints() const
{
    return snapFeaturePoints_;
}

inline tnbLib::Switch tnbLib::cvControls::circulateEdges() const
{
    return circulateEdges_;
}


inline tnbLib::scalar tnbLib::cvControls::surfacePtExclusionDistanceCoeff() const
{
    return surfacePtExclusionDistanceCoeff_;
}

inline tnbLib::Switch tnbLib::cvControls::specialiseFeaturePoints() const
{
    return specialiseFeaturePoints_;
}

inline tnbLib::scalar tnbLib::cvControls::surfaceSearchDistanceCoeff() const
{
    return surfaceSearchDistanceCoeff_;
}


inline tnbLib::scalar tnbLib::cvControls::maxSurfaceProtrusionCoeff() const
{
    return maxSurfaceProtrusionCoeff_;
}


inline tnbLib::scalar tnbLib::cvControls::maxQuadAngle() const
{
    return maxQuadAngle_;
}


inline tnbLib::label tnbLib::cvControls::surfaceConformationRebuildFrequency() const
{
    return surfaceConformationRebuildFrequency_;
}


inline tnbLib::scalar tnbLib::cvControls::edgeSearchDistCoeffSqr() const
{
    return edgeSearchDistCoeffSqr_;
}


inline tnbLib::scalar tnbLib::cvControls::surfacePtReplaceDistCoeffSqr() const
{
    return surfacePtReplaceDistCoeffSqr_;
}


inline tnbLib::label tnbLib::cvControls::maxConformationIterations() const
{
    return maxConformationIterations_;
}


inline tnbLib::scalar tnbLib::cvControls::iterationToInitialHitRatioLimit() const
{
    return iterationToInitialHitRatioLimit_;
}


inline tnbLib::scalar tnbLib::cvControls::defaultCellSize() const
{
    return defaultCellSize_;
}


inline tnbLib::scalar tnbLib::cvControls::minimumCellSize() const
{
    return minimumCellSize_;
}


inline tnbLib::Switch tnbLib::cvControls::objOutput() const
{
    return objOutput_;
}


inline tnbLib::Switch tnbLib::cvControls::timeChecks() const
{
    return timeChecks_;
}


inline tnbLib::Switch tnbLib::cvControls::printVertexInfo() const
{
    return printVertexInfo_;
}


inline tnbLib::scalar tnbLib::cvControls::maxLoadUnbalance() const
{
    return maxLoadUnbalance_;
}


inline tnbLib::scalar tnbLib::cvControls::cosAlignmentAcceptanceAngle() const
{
    return cosAlignmentAcceptanceAngle_;
}


inline tnbLib::scalar tnbLib::cvControls::insertionDistCoeff() const
{
    return insertionDistCoeff_;
}


inline tnbLib::scalar tnbLib::cvControls::faceAreaRatioCoeff() const
{
    return faceAreaRatioCoeff_;
}


inline tnbLib::scalar tnbLib::cvControls::cosInsertionAcceptanceAngle() const
{
    return cosInsertionAcceptanceAngle_;
}


inline tnbLib::scalar tnbLib::cvControls::removalDistCoeff() const
{
    return removalDistCoeff_;
}


inline tnbLib::Switch tnbLib::cvControls::filterEdges() const
{
    return filterEdges_;
}

inline tnbLib::Switch tnbLib::cvControls::filterFaces() const
{
    return filterFaces_;
}

inline tnbLib::Switch tnbLib::cvControls::writeTetDualMesh() const
{
    return writeTetDualMesh_;
}

inline tnbLib::Switch tnbLib::cvControls::writeCellShapeControlMesh() const
{
    return writeCellShapeControlMesh_;
}

inline tnbLib::Switch tnbLib::cvControls::writeBackgroundMeshDecomposition() const
{
    return writeBackgroundMeshDecomposition_;
}


// ************************************************************************* //
