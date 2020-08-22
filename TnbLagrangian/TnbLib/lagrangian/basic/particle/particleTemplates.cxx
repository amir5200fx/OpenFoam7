#include <particle.hxx>

#include <IOPosition.hxx>
#include <cyclicPolyPatch.hxx>
#include <cyclicAMIPolyPatch.hxx>
#include <cyclicACMIPolyPatch.hxx>
#include <cyclicRepeatAMIPolyPatch.hxx>
#include <processorPolyPatch.hxx>
#include <symmetryPlanePolyPatch.hxx>
#include <symmetryPolyPatch.hxx>
#include <wallPolyPatch.hxx>
#include <wedgePolyPatch.hxx>
#include <meshTools.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TrackCloudType>
void tnbLib::particle::readFields(TrackCloudType& c)
{
	bool valid = c.size();

	IOobject procIO(c.fieldIOobject("origProcId", IOobject::MUST_READ));

	bool haveFile = procIO.typeHeaderOk<IOField<label>>(true);

	IOField<label> origProcId(procIO, valid && haveFile);
	c.checkFieldIOobject(c, origProcId);
	IOField<label> origId
	(
		c.fieldIOobject("origId", IOobject::MUST_READ),
		valid && haveFile
	);
	c.checkFieldIOobject(c, origId);

	label i = 0;
	forAllIter(typename TrackCloudType, c, iter)
	{
		particle& p = iter();

		p.origProc_ = origProcId[i];
		p.origId_ = origId[i];
		i++;
	}
}


template<class TrackCloudType>
void tnbLib::particle::writeFields(const TrackCloudType& c)
{
	label np = c.size();

	IOPosition<TrackCloudType> ioP(c);
	ioP.write(np > 0);

	IOField<label> origProc
	(
		c.fieldIOobject("origProcId", IOobject::NO_READ),
		np
	);
	IOField<label> origId
	(
		c.fieldIOobject("origId", IOobject::NO_READ),
		np
	);

	label i = 0;
	forAllConstIter(typename TrackCloudType, c, iter)
	{
		origProc[i] = iter().origProc_;
		origId[i] = iter().origId_;
		i++;
	}

	origProc.write(np > 0);
	origId.write(np > 0);
}


template<class TrackCloudType>
void tnbLib::particle::hitFace
(
	const vector& displacement,
	const scalar fraction,
	TrackCloudType& cloud,
	trackingData& td
)
{
	if (debug)
	{
		Info << "Particle " << origId() << nl << FUNCTION_NAME << nl << endl;
	}

	if (onBoundaryFace())
	{
		changeToMasterPatch();
	}

	hitFaceNoChangeToMasterPatch(displacement, fraction, cloud, td);
}


template<class TrackCloudType>
void tnbLib::particle::hitFaceNoChangeToMasterPatch
(
	const vector& displacement,
	const scalar fraction,
	TrackCloudType& cloud,
	trackingData& td
)
{
	if (debug)
	{
		Info << "Particle " << origId() << nl << FUNCTION_NAME << nl << endl;
	}

	typename TrackCloudType::particleType& p =
		static_cast<typename TrackCloudType::particleType&>(*this);
	typename TrackCloudType::particleType::trackingData& ttd =
		static_cast<typename TrackCloudType::particleType::trackingData&>(td);

	if (!onFace())
	{
		return;
	}
	else if (onInternalFace())
	{
		changeCell();
	}
	else if (onBoundaryFace())
	{
		if (!p.hitPatch(cloud, ttd))
		{
			const polyPatch& patch = mesh_.boundaryMesh()[p.patch()];

			if (isA<wedgePolyPatch>(patch))
			{
				p.hitWedgePatch(cloud, ttd);
			}
			else if (isA<symmetryPlanePolyPatch>(patch))
			{
				p.hitSymmetryPlanePatch(cloud, ttd);
			}
			else if (isA<symmetryPolyPatch>(patch))
			{
				p.hitSymmetryPatch(cloud, ttd);
			}
			else if (isA<cyclicPolyPatch>(patch))
			{
				p.hitCyclicPatch(cloud, ttd);
			}
			else if (isA<cyclicACMIPolyPatch>(patch))
			{
				p.hitCyclicACMIPatch(displacement, fraction, cloud, ttd);
			}
			else if (isA<cyclicAMIPolyPatch>(patch))
			{
				p.hitCyclicAMIPatch(displacement, fraction, cloud, ttd);
			}
			else if (isA<cyclicRepeatAMIPolyPatch>(patch))
			{
				p.hitCyclicRepeatAMIPatch(displacement, fraction, cloud, ttd);
			}
			else if (isA<processorPolyPatch>(patch))
			{
				p.hitProcessorPatch(cloud, ttd);
			}
			else if (isA<wallPolyPatch>(patch))
			{
				p.hitWallPatch(cloud, ttd);
			}
			else
			{
				td.keepParticle = false;
			}
		}
	}
}


template<class TrackCloudType>
tnbLib::scalar tnbLib::particle::trackToAndHitFace
(
	const vector& displacement,
	const scalar fraction,
	TrackCloudType& cloud,
	trackingData& td
)
{
	if (debug)
	{
		Info << "Particle " << origId() << nl << FUNCTION_NAME << nl << endl;
	}

	const scalar f = trackToFace(displacement, fraction);

	hitFace(displacement, fraction, cloud, td);

	return f;
}


template<class TrackCloudType>
bool tnbLib::particle::hitPatch(TrackCloudType&, trackingData&)
{
	return false;
}


template<class TrackCloudType>
void tnbLib::particle::hitWedgePatch(TrackCloudType& cloud, trackingData& td)
{
	FatalErrorInFunction
		<< "Hitting a wedge patch should not be possible."
		<< abort(FatalError);

	hitSymmetryPatch(cloud, td);
}


template<class TrackCloudType>
void tnbLib::particle::hitSymmetryPlanePatch
(
	TrackCloudType& cloud,
	trackingData& td
)
{
	hitSymmetryPatch(cloud, td);
}


template<class TrackCloudType>
void tnbLib::particle::hitSymmetryPatch(TrackCloudType&, trackingData&)
{
	const vector nf = normal();
	transformProperties(I - 2.0*nf*nf);
}


template<class TrackCloudType>
void tnbLib::particle::hitCyclicPatch(TrackCloudType&, trackingData&)
{
	const cyclicPolyPatch& cpp =
		static_cast<const cyclicPolyPatch&>(mesh_.boundaryMesh()[patch()]);
	const cyclicPolyPatch& receiveCpp = cpp.neighbPatch();
	const label receiveFacei = receiveCpp.whichFace(facei_);

	// Set the topology
	facei_ = tetFacei_ = cpp.transformGlobalFace(facei_);
	celli_ = mesh_.faceOwner()[facei_];
	// See note in correctAfterParallelTransfer for tetPti addressing ...
	tetPti_ = mesh_.faces()[tetFacei_].size() - 1 - tetPti_;

	// Reflect to account for the change of triangle orientation in the new cell
	reflect();

	// Transform the properties
	if (!receiveCpp.parallel())
	{
		const tensor& T =
			(
				receiveCpp.forwardT().size() == 1
				? receiveCpp.forwardT()[0]
				: receiveCpp.forwardT()[receiveFacei]
				);
		transformProperties(T);
	}
	else if (receiveCpp.separated())
	{
		const vector& s =
			(
			(receiveCpp.separation().size() == 1)
				? receiveCpp.separation()[0]
				: receiveCpp.separation()[receiveFacei]
				);
		transformProperties(-s);
	}
}


template<class TrackCloudType>
void tnbLib::particle::hitCyclicAMIPatch
(
	const vector& displacement,
	const scalar fraction,
	TrackCloudType& cloud,
	trackingData& td
)
{
	const cyclicAMIPolyPatch& cpp =
		static_cast<const cyclicAMIPolyPatch&>(mesh_.boundaryMesh()[patch()]);
	const cyclicAMIPolyPatch& receiveCpp = cpp.neighbPatch();

	if (debug)
	{
		Info << "Particle " << origId() << " crossing AMI from " << cpp.name()
			<< " to " << receiveCpp.name() << endl << endl;
	}

	// Get the send patch data
	vector sendNormal, sendDisplacement;
	patchData(sendNormal, sendDisplacement);

	vector pos = position();

	const labelPair receiveIs =
		cpp.pointAMIAndFace
		(
			cpp.whichFace(facei_),
			displacement - fraction * sendDisplacement,
			pos
		);
	const label receiveAMIi = receiveIs.first();
	const label receiveFacei = receiveIs.second();

	// If the receiving face could not be found then issue a warning and remove
	// the particle
	if (receiveFacei < 0)
	{
		td.keepParticle = false;
		WarningInFunction
			<< "Particle transfer from " << cyclicAMIPolyPatch::typeName
			<< " patches " << cpp.name() << " to " << receiveCpp.name()
			<< " failed at position " << pos << " and with displacement "
			<< (displacement - fraction * sendDisplacement) << nl
			<< "    A receiving face could not be found" << nl
			<< "    The particle has been removed" << nl << endl;
		return;
	}

	// Set the topology
	facei_ = tetFacei_ = receiveFacei + receiveCpp.start();

	// Locate the particle on the receiving side
	locate
	(
		pos,
		mesh_.faceOwner()[facei_],
		false,
		"Particle crossed between " + cyclicAMIPolyPatch::typeName +
		" patches " + cpp.name() + " and " + receiveCpp.name() +
		" to a location outside of the mesh."
	);

	// The particle must remain associated with a face for the tracking to
	// register as incomplete
	facei_ = tetFacei_;

	// Transform the properties
	vector displacementT = displacement;

	const vectorTensorTransform AMITransform =
		receiveCpp.owner()
		? receiveCpp.AMITransforms()[receiveAMIi]
		: inv(cpp.AMITransforms()[receiveAMIi]);
	if (AMITransform.hasR())
	{
		transformProperties(AMITransform.R());
		displacementT = transform(AMITransform.R(), displacementT);
	}
	else if (AMITransform.t() != vector::zero)
	{
		transformProperties(AMITransform.t());
	}

	if (!receiveCpp.parallel())
	{
		const tensor& T =
			(
				receiveCpp.forwardT().size() == 1
				? receiveCpp.forwardT()[0]
				: receiveCpp.forwardT()[facei_]
				);
		transformProperties(T);
		displacementT = transform(T, displacementT);
	}
	else if (receiveCpp.separated())
	{
		const vector& s =
			(
			(receiveCpp.separation().size() == 1)
				? receiveCpp.separation()[0]
				: receiveCpp.separation()[facei_]
				);
		transformProperties(-s);
	}

	// If on a boundary and the displacement points into the receiving face
	// then issue a warning and remove the particle
	if (onBoundaryFace())
	{
		vector receiveNormal, receiveDisplacement;
		patchData(receiveNormal, receiveDisplacement);

		if (((displacementT - fraction * receiveDisplacement)&receiveNormal) > 0)
		{
			td.keepParticle = false;
			WarningInFunction
				<< "Particle transfer from " << cyclicAMIPolyPatch::typeName
				<< " patches " << cpp.name() << " to " << receiveCpp.name()
				<< " failed at position " << pos << " and with displacement "
				<< (displacementT - fraction * receiveDisplacement) << nl
				<< "    The displacement points into both the source and "
				<< "receiving faces, so the tracking cannot proceed" << nl
				<< "    The particle has been removed" << nl << endl;
			return;
		}
	}
}


template<class TrackCloudType>
void tnbLib::particle::hitCyclicACMIPatch
(
	const vector& displacement,
	const scalar fraction,
	TrackCloudType& cloud,
	trackingData& td
)
{
	typename TrackCloudType::particleType& p =
		static_cast<typename TrackCloudType::particleType&>(*this);

	const cyclicACMIPolyPatch& cpp =
		static_cast<const cyclicACMIPolyPatch&>(mesh_.boundaryMesh()[patch()]);

	vector patchNormal, patchDisplacement;
	patchData(patchNormal, patchDisplacement);

	const label localFacei = cpp.whichFace(facei_);

	// If the mask is within the patch tolerance at either end, then we can
	// assume an interaction with the appropriate part of the ACMI pair.
	const scalar mask = cpp.mask()[localFacei];
	bool couple = mask >= 1 - cpp.tolerance();
	bool nonOverlap = mask <= cpp.tolerance();

	// If the mask is an intermediate value, then we search for a location on
	// the other side of the AMI. If we can't find a location, then we assume
	// that we have hit the non-overlap patch.
	if (!couple && !nonOverlap)
	{
		vector pos = position();
		couple =
			cpp.pointAMIAndFace
			(
				localFacei,
				displacement - fraction * patchDisplacement,
				pos
			).first() >= 0;
		nonOverlap = !couple;
	}

	if (couple)
	{
		p.hitCyclicAMIPatch(displacement, fraction, cloud, td);
	}
	else
	{
		// Move to the face associated with the non-overlap patch and redo the
		// face interaction.
		tetFacei_ = facei_ = cpp.nonOverlapPatch().start() + localFacei;
		p.hitFaceNoChangeToMasterPatch(displacement, fraction, cloud, td);
	}
}


template<class TrackCloudType>
void tnbLib::particle::hitCyclicRepeatAMIPatch
(
	const vector& displacement,
	const scalar fraction,
	TrackCloudType& cloud,
	trackingData& td
)
{
	typename TrackCloudType::particleType& p =
		static_cast<typename TrackCloudType::particleType&>(*this);

	p.hitCyclicAMIPatch(displacement, fraction, cloud, td);
}


template<class TrackCloudType>
void tnbLib::particle::hitProcessorPatch(TrackCloudType&, trackingData&)
{}


template<class TrackCloudType>
void tnbLib::particle::hitWallPatch(TrackCloudType&, trackingData&)
{}


// ************************************************************************* //