#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	// Update this with w2 if w2 nearer to pt.
	template<class TrackingData>
	inline bool wallPointYPlus::update
	(
		const point& pt,
		const wallPointYPlus& w2,
		const scalar tol,
		TrackingData& td
	)
	{
		scalar dist2 = magSqr(pt - w2.origin());

		if (valid(td))
		{
			scalar diff = distSqr() - dist2;

			if (diff < 0)
			{
				// already nearer to pt
				return false;
			}

			if ((diff < small) || ((distSqr() > small) && (diff / distSqr() < tol)))
			{
				// don't propagate small changes
				return false;
			}
		}


		// Either *this is not yet valid or w2 is closer
		{
			// only propagate if interesting (i.e. y+ < 100)
			scalar yPlus = tnbLib::sqrt(dist2) / w2.data();

			if (yPlus < yPlusCutOff)
			{
				// update with new values
				distSqr() = dist2;
				origin() = w2.origin();
				data() = w2.data();

				return true;
			}
			else
			{
				return false;
			}
		}
	}


	// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

	// Null constructor
	inline wallPointYPlus::wallPointYPlus()
		:
		wallPointData<scalar>()
	{
		// Important: value of yStar where meshWave does not come.
		data() = 1.0;
	}


	// Construct from components
	inline wallPointYPlus::wallPointYPlus
	(
		const point& origin,
		const scalar yStar,
		const scalar distSqr
	)
		:
		wallPointData<scalar>(origin, yStar, distSqr)
	{}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	// Update this with w2 if w2 nearer to pt.
	template<class TrackingData>
	inline bool wallPointYPlus::updateCell
	(
		const polyMesh& mesh,
		const label thisCelli,
		const label neighbourFacei,
		const wallPointYPlus& neighbourWallInfo,
		const scalar tol,
		TrackingData& td
	)
	{
		const vectorField& cellCentres = mesh.primitiveMesh::cellCentres();

		return update
		(
			cellCentres[thisCelli],
			neighbourWallInfo,
			tol,
			td
		);
	}


	// Update this with w2 if w2 nearer to pt.
	template<class TrackingData>
	inline bool wallPointYPlus::updateFace
	(
		const polyMesh& mesh,
		const label thisFacei,
		const label neighbourCelli,
		const wallPointYPlus& neighbourWallInfo,
		const scalar tol,
		TrackingData& td
	)
	{
		const vectorField& faceCentres = mesh.faceCentres();

		return update
		(
			faceCentres[thisFacei],
			neighbourWallInfo,
			tol,
			td
		);
	}


	// Update this with w2 if w2 nearer to pt.
	template<class TrackingData>
	inline bool wallPointYPlus::updateFace
	(
		const polyMesh& mesh,
		const label thisFacei,
		const wallPointYPlus& neighbourWallInfo,
		const scalar tol,
		TrackingData& td
	)
	{
		const vectorField& faceCentres = mesh.faceCentres();

		return update
		(
			faceCentres[thisFacei],
			neighbourWallInfo,
			tol,
			td
		);
	}


	// ************************************************************************* //

} // End namespace tnbLib

// ************************************************************************* //