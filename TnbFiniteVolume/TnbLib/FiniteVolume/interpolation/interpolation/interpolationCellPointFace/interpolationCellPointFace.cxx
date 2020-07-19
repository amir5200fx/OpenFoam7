#include <interpolationCellPointFace.hxx>

#include <volFields.hxx>
#include <polyMesh.hxx>
#include <volPointInterpolation.hxx>
#include <linear.hxx>
#include <findCellPointFaceTet.hxx>
#include <findCellPointFaceTriangle.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::interpolationCellPointFace<Type>::interpolationCellPointFace
(
	const GeometricField<Type, fvPatchField, volMesh>& psi
)
	:
	interpolation<Type>(psi),
	psip_
	(
		volPointInterpolation::New(psi.mesh()).interpolate
		(
			psi,
			"volPointInterpolate(" + psi.name() + ')',
			true        // use cache
		)
	),
	psis_(linearInterpolate(psi))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
Type tnbLib::interpolationCellPointFace<Type>::interpolate
(
	const vector& position,
	const label celli,
	const label facei
) const
{
	Type ts[4];
	vector tetPoints[4];
	scalar phi[4], phiCandidate[4];
	label tetLabelCandidate[2], tetPointLabels[2];

	Type t = Zero;

	// only use face information when the position is on a face
	if (facei < 0)
	{
		const vector& cellCentre = this->pMesh_.cellCentres()[celli];
		const labelList& cellFaces = this->pMesh_.cells()[celli];

		vector projection = position - cellCentre;
		tetPoints[3] = cellCentre;

		// *********************************************************************
		// project the cell-center through the point onto the face
		// and get the closest face, ...
		// *********************************************************************

		bool foundTet = false;
		label closestFace = -1;
		scalar minDistance = great;

		forAll(cellFaces, facei)
		{
			label nFace = cellFaces[facei];

			vector normal = this->pMeshFaceAreas_[nFace];
			normal /= mag(normal);

			const vector& faceCentreTmp = this->pMeshFaceCentres_[nFace];

			scalar multiplierNumerator = (faceCentreTmp - cellCentre) & normal;
			scalar multiplierDenominator = projection & normal;

			// if normal and projection are not orthogonal this could
			// be the one...
			if (mag(multiplierDenominator) > small)
			{
				scalar multiplier = multiplierNumerator / multiplierDenominator;
				vector iPoint = cellCentre + multiplier * projection;
				scalar dist = mag(position - iPoint);

				if (dist < minDistance)
				{
					closestFace = nFace;
					minDistance = dist;
				}
			}
		}

		// *********************************************************************
		// find the tetrahedron containing 'position'
		// from the cell center, face center and
		// two other points on the face
		// *********************************************************************

		minDistance = great;
		if (closestFace != -1)
		{
			label nFace = closestFace;
			foundTet = findTet
			(
				position,
				nFace,
				tetPoints,
				tetLabelCandidate,
				tetPointLabels,
				phi,
				phiCandidate,
				closestFace,
				minDistance
			);
		}

		if (!foundTet)
		{
			// check if the position is 'just' outside a tet
			if (minDistance < 1.0e-5)
			{
				foundTet = true;
				for (label i = 0; i < 4; i++)
				{
					phi[i] = phiCandidate[i];
				}
				tetPointLabels[0] = tetLabelCandidate[0];
				tetPointLabels[1] = tetLabelCandidate[1];
			}
		}

		// *********************************************************************
		// if the search failed check all the cell-faces
		// *********************************************************************

		if (!foundTet)
		{
			minDistance = great;

			label facei = 0;
			while (facei < cellFaces.size() && !foundTet)
			{
				label nFace = cellFaces[facei];
				if (nFace < this->pMeshFaceAreas_.size())
				{
					foundTet = findTet
					(
						position,
						nFace,
						tetPoints,
						tetLabelCandidate,
						tetPointLabels,
						phi,
						phiCandidate,
						closestFace,
						minDistance
					);
				}
				facei++;
			}
		}

		if (!foundTet)
		{
			// check if the position is 'just' outside a tet
			// this time with a more tolerant limit
			if (minDistance < 1.0e-3)
			{
				foundTet = true;
				for (label i = 0; i < 4; i++)
				{
					phi[i] = phiCandidate[i];
				}
				tetPointLabels[0] = tetLabelCandidate[0];
				tetPointLabels[1] = tetLabelCandidate[1];
			}
		}

		// *********************************************************************
		// if the tet was found do the interpolation,
		// otherwise use the closest face value
		// *********************************************************************

		if (foundTet)
		{
			for (label i = 0; i < 2; i++)
			{
				ts[i] = psip_[tetPointLabels[i]];
			}

			if (closestFace < psis_.size())
			{
				ts[2] = psis_[closestFace];
			}
			else
			{
				label patchi =
					this->pMesh_.boundaryMesh().whichPatch(closestFace);

				// If the boundary patch is not empty use the face value
				// else use the cell value
				if (this->psi_.boundaryField()[patchi].size())
				{
					ts[2] = this->psi_.boundaryField()[patchi]
						[
							this->pMesh_.boundaryMesh()[patchi].whichFace
							(
								closestFace
							)
						];
				}
				else
				{
					ts[2] = this->psi_[celli];
				}
			}

			ts[3] = this->psi_[celli];

			for (label n = 0; n < 4; n++)
			{
				phi[n] = min(1.0, phi[n]);
				phi[n] = max(0.0, phi[n]);

				t += phi[n] * ts[n];
			}
		}
		else
		{
			InfoInFunction
				<< "search failed; using closest cellFace value" << endl
				<< "cell number " << celli << tab
				<< "position " << position << endl;

			if (closestFace < psis_.size())
			{
				t = psis_[closestFace];
			}
			else
			{
				label patchi =
					this->pMesh_.boundaryMesh().whichPatch(closestFace);

				// If the boundary patch is not empty use the face value
				// else use the cell value
				if (this->psi_.boundaryField()[patchi].size())
				{
					t = this->psi_.boundaryField()[patchi]
						[
							this->pMesh_.boundaryMesh()[patchi].whichFace
							(
								closestFace
							)
						];
				}
				else
				{
					t = this->psi_[celli];
				}
			}
		}
	}
	else
	{
		bool foundTriangle = findTriangle
		(
			position,
			facei,
			tetPointLabels,
			phi
		);

		if (foundTriangle)
		{
			// add up the point values ...
			for (label i = 0; i < 2; i++)
			{
				Type vel = psip_[tetPointLabels[i]];
				t += phi[i] * vel;
			}

			// ... and the face value
			if (facei < psis_.size())
			{
				t += phi[2] * psis_[facei];
			}
			else
			{
				label patchi = this->pMesh_.boundaryMesh().whichPatch(facei);

				// If the boundary patch is not empty use the face value
				// else use the cell value
				if (this->psi_.boundaryField()[patchi].size())
				{
					t += phi[2] * this->psi_.boundaryField()[patchi]
						[this->pMesh_.boundaryMesh()[patchi].whichFace(facei)];
				}
				else
				{
					t += phi[2] * this->psi_[celli];
				}
			}
		}
		else
		{
			// use face value only
			if (facei < psis_.size())
			{
				t = psis_[facei];
			}
			else
			{
				label patchi = this->pMesh_.boundaryMesh().whichPatch(facei);

				// If the boundary patch is not empty use the face value
				// else use the cell value
				if (this->psi_.boundaryField()[patchi].size())
				{
					t = this->psi_.boundaryField()[patchi]
						[this->pMesh_.boundaryMesh()[patchi].whichFace(facei)];
				}
				else
				{
					t = this->psi_[celli];
				}
			}
		}
	}

	return t;
}


// ************************************************************************* //