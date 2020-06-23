#include <wedgePolyPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <SubField.hxx>
#include <transform.hxx>
#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(wedgePolyPatch, 0);

	addToRunTimeSelectionTable(polyPatch, wedgePolyPatch, word);
	addToRunTimeSelectionTable(polyPatch, wedgePolyPatch, dictionary);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::wedgePolyPatch::calcGeometry(PstreamBuffers&)
{
	if (axis_ != vector::rootMax)
	{
		return;
	}

	if (returnReduce(size(), sumOp<label>()))
	{
		const vectorField& nf(faceNormals());
		n_ = gAverage(nf);

		if (debug)
		{
			Info << "Patch " << name() << " calculated average normal "
				<< n_ << endl;
		}


		// Check the wedge is planar
		forAll(nf, facei)
		{
			if (magSqr(n_ - nf[facei]) > small)
			{
				// only issue warning instead of error so that the case can
				// still be read for post-processing
				WarningInFunction
					<< "Wedge patch '" << name() << "' is not planar." << nl
					<< "At local face at "
					<< primitivePatch::faceCentres()[facei]
					<< " the normal " << nf[facei]
					<< " differs from the average normal " << n_
					<< " by " << magSqr(n_ - nf[facei]) << nl
					<< "Either correct the patch or split it into planar parts"
					<< endl;
			}
		}

		centreNormal_ =
			vector
			(
				sign(n_.x())*(max(mag(n_.x()), 0.5) - 0.5),
				sign(n_.y())*(max(mag(n_.y()), 0.5) - 0.5),
				sign(n_.z())*(max(mag(n_.z()), 0.5) - 0.5)
			);
		centreNormal_ /= mag(centreNormal_);

		cosAngle_ = centreNormal_ & n_;

		const scalar cnCmptSum =
			centreNormal_.x() + centreNormal_.y() + centreNormal_.z();

		if (mag(cnCmptSum) < (1 - small))
		{
			FatalErrorInFunction
				<< "wedge " << name()
				<< " centre plane does not align with a coordinate plane by "
				<< 1 - mag(cnCmptSum)
				<< exit(FatalError);
		}

		axis_ = centreNormal_ ^ n_;
		scalar magAxis = mag(axis_);

		if (magAxis < small)
		{
			FatalErrorInFunction
				<< "wedge " << name()
				<< " plane aligns with a coordinate plane." << nl
				<< "    The wedge plane should make a small angle (~2.5deg)"
				" with the coordinate plane" << nl
				<< "    and the pair of wedge planes should be symmetric"
				<< " about the coordinate plane." << nl
				<< "    Normal of wedge plane is " << n_
				<< " , implied coordinate plane direction is " << centreNormal_
				<< exit(FatalError);
		}

		axis_ /= magAxis;

		faceT_ = rotationTensor(centreNormal_, n_);
		cellT_ = faceT_ & faceT_;
	}
}


// * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * * * * //

tnbLib::wedgePolyPatch::wedgePolyPatch
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, size, start, index, bm, patchType),
	axis_(vector::rootMax),
	centreNormal_(vector::rootMax),
	n_(vector::rootMax),
	cosAngle_(0.0),
	faceT_(Zero),
	cellT_(Zero)
{}


tnbLib::wedgePolyPatch::wedgePolyPatch
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyBoundaryMesh& bm,
	const word& patchType
)
	:
	polyPatch(name, dict, index, bm, patchType),
	axis_(vector::rootMax),
	centreNormal_(vector::rootMax),
	n_(vector::rootMax),
	cosAngle_(0.0),
	faceT_(Zero),
	cellT_(Zero)
{}


tnbLib::wedgePolyPatch::wedgePolyPatch
(
	const wedgePolyPatch& pp,
	const polyBoundaryMesh& bm
)
	:
	polyPatch(pp, bm),
	axis_(pp.axis_),
	centreNormal_(pp.centreNormal_),
	n_(pp.n_),
	cosAngle_(pp.cosAngle_),
	faceT_(pp.faceT_),
	cellT_(pp.cellT_)
{}


tnbLib::wedgePolyPatch::wedgePolyPatch
(
	const wedgePolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const label newSize,
	const label newStart
)
	:
	polyPatch(pp, bm, index, newSize, newStart),
	axis_(pp.axis_),
	centreNormal_(pp.centreNormal_),
	n_(pp.n_),
	cosAngle_(pp.cosAngle_),
	faceT_(pp.faceT_),
	cellT_(pp.cellT_)
{}


tnbLib::wedgePolyPatch::wedgePolyPatch
(
	const wedgePolyPatch& pp,
	const polyBoundaryMesh& bm,
	const label index,
	const labelUList& mapAddressing,
	const label newStart
)
	:
	polyPatch(pp, bm, index, mapAddressing, newStart),
	axis_(pp.axis_),
	centreNormal_(pp.centreNormal_),
	n_(pp.n_),
	cosAngle_(pp.cosAngle_),
	faceT_(pp.faceT_),
	cellT_(pp.cellT_)
{}


// ************************************************************************* //