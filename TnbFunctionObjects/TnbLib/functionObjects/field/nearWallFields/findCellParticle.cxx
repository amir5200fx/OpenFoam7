#include <findCellParticle.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::findCellParticle::findCellParticle
(
	const polyMesh& mesh,
	const barycentric& coordinates,
	const label celli,
	const label tetFacei,
	const label tetPtI,
	const vector& displacement,
	const label data
)
	:
	particle(mesh, coordinates, celli, tetFacei, tetPtI),
	displacement_(displacement),
	data_(data)
{}


tnbLib::findCellParticle::findCellParticle
(
	const polyMesh& mesh,
	const vector& position,
	const label celli,
	const vector& displacement,
	const label data
)
	:
	particle(mesh, position, celli),
	displacement_(displacement),
	data_(data)
{}


tnbLib::findCellParticle::findCellParticle
(
	const polyMesh& mesh,
	Istream& is,
	bool readFields
)
	:
	particle(mesh, is, readFields)
{
	if (readFields)
	{
		if (is.format() == IOstream::ASCII)
		{
			is >> displacement_;
			data_ = readLabel(is);
		}
		else
		{
			is.read
			(
				reinterpret_cast<char*>(&displacement_),
				sizeof(displacement_) + sizeof(data_)
			);
		}
	}

	// Check state of Istream
	is.check
	(
		"findCellParticle::findCellParticle"
		"(const Cloud<findCellParticle>&, Istream&, bool)"
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::findCellParticle::move
(
	Cloud<findCellParticle>& cloud,
	trackingData& td,
	const scalar maxTrackLen
)
{
	td.switchProcessor = false;
	td.keepParticle = true;

	while (td.keepParticle && !td.switchProcessor && stepFraction() < 1)
	{
		const scalar f = 1 - stepFraction();
		trackToAndHitFace(f*displacement_, f, cloud, td);
	}

	if (!td.switchProcessor)
	{
		// Hit endpoint or patch. If patch hit could do fancy stuff but just
		// to use the patch point is good enough for now.
		td.cellToData()[cell()].append(data());
		td.cellToEnd()[cell()].append(position());
	}

	return td.keepParticle;
}


bool tnbLib::findCellParticle::hitPatch(Cloud<findCellParticle>&, trackingData&)
{
	return false;
}


void tnbLib::findCellParticle::hitWedgePatch
(
	Cloud<findCellParticle>&,
	trackingData& td
)
{
	// Remove particle
	td.keepParticle = false;
}


void tnbLib::findCellParticle::hitSymmetryPlanePatch
(
	Cloud<findCellParticle>&,
	trackingData& td
)
{
	// Remove particle
	td.keepParticle = false;
}


void tnbLib::findCellParticle::hitSymmetryPatch
(
	Cloud<findCellParticle>&,
	trackingData& td
)
{
	// Remove particle
	td.keepParticle = false;
}


void tnbLib::findCellParticle::hitCyclicPatch
(
	Cloud<findCellParticle>&,
	trackingData& td
)
{
	// Remove particle
	td.keepParticle = false;
}


void tnbLib::findCellParticle::hitCyclicAMIPatch
(
	const vector&,
	const scalar,
	Cloud<findCellParticle>&,
	trackingData& td
)
{
	// Remove particle
	td.keepParticle = false;
}


void tnbLib::findCellParticle::hitCyclicACMIPatch
(
	const vector&,
	const scalar,
	Cloud<findCellParticle>&,
	trackingData& td
)
{
	// Remove particle
	td.keepParticle = false;
}


void tnbLib::findCellParticle::hitCyclicRepeatAMIPatch
(
	const vector&,
	const scalar,
	Cloud<findCellParticle>&,
	trackingData& td
)
{
	// Remove particle
	td.keepParticle = false;
}


void tnbLib::findCellParticle::hitProcessorPatch
(
	Cloud<findCellParticle>&,
	trackingData& td
)
{
	// Remove particle
	td.switchProcessor = true;
}


void tnbLib::findCellParticle::hitWallPatch
(
	Cloud<findCellParticle>&,
	trackingData& td
)
{
	// Remove particle
	td.keepParticle = false;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const findCellParticle& p)
{
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const particle&>(p)
			<< token::SPACE << p.displacement_
			<< token::SPACE << p.data_;
	}
	else
	{
		os << static_cast<const particle&>(p);
		os.write
		(
			reinterpret_cast<const char*>(&p.displacement_),
			sizeof(p.displacement_) + sizeof(p.data_)
		);
	}

	// Check state of Ostream
	os.check("Ostream& operator<<(Ostream&, const findCellParticle&)");

	return os;
}


// ************************************************************************* //