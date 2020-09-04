#include <extendedFeatureEdgeMesh.hxx>

#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(extendedFeatureEdgeMesh, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extendedFeatureEdgeMesh::extendedFeatureEdgeMesh(const IOobject& io)
	:
	regIOobject(io),
	extendedEdgeMesh()
{
	if
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		// Warn for MUST_READ_IF_MODIFIED
		warnNoRereading<extendedFeatureEdgeMesh>();

		readStream(typeName) >> *this;
		close();

		{
			// Calculate edgeDirections

			const edgeList& eds(edges());

			const pointField& pts(points());

			edgeDirections_.setSize(eds.size());

			forAll(eds, eI)
			{
				edgeDirections_[eI] = eds[eI].vec(pts);
			}

			edgeDirections_ /= (mag(edgeDirections_) + small);
		}
	}

	if (debug)
	{
		Pout << "extendedFeatureEdgeMesh::extendedFeatureEdgeMesh :"
			<< " constructed from IOobject :"
			<< " points:" << points().size()
			<< " edges:" << edges().size()
			<< endl;
	}
}


tnbLib::extendedFeatureEdgeMesh::extendedFeatureEdgeMesh
(
	const IOobject& io,
	const extendedEdgeMesh& em
)
	:
	regIOobject(io),
	extendedEdgeMesh(em)
{}


tnbLib::extendedFeatureEdgeMesh::extendedFeatureEdgeMesh
(
	const surfaceFeatures& sFeat,
	const objectRegistry& obr,
	const fileName& sFeatFileName,
	const boolList& surfBaffleRegions
)
	:
	regIOobject
	(
		IOobject
		(
			sFeatFileName,
			obr.time().constant(),
			"extendedFeatureEdgeMesh",
			obr,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		)
	),
	extendedEdgeMesh(sFeat, surfBaffleRegions)
{}


tnbLib::extendedFeatureEdgeMesh::extendedFeatureEdgeMesh
(
	const IOobject& io,
	const PrimitivePatch<faceList, pointField>& surf,
	const labelList& featureEdges,
	const labelList& regionFeatureEdges,
	const labelList& featurePoints
)
	:
	regIOobject(io),
	extendedEdgeMesh(surf, featureEdges, regionFeatureEdges, featurePoints)
{}


tnbLib::extendedFeatureEdgeMesh::extendedFeatureEdgeMesh
(
	const IOobject& io,
	const pointField& pts,
	const edgeList& eds,
	label concaveStart,
	label mixedStart,
	label nonFeatureStart,
	label internalStart,
	label flatStart,
	label openStart,
	label multipleStart,
	const vectorField& normals,
	const List<sideVolumeType>& normalVolumeTypes,
	const vectorField& edgeDirections,
	const labelListList& normalDirections,
	const labelListList& edgeNormals,
	const labelListList& featurePointNormals,
	const labelListList& featurePointEdges,
	const labelList& regionEdges
)
	:
	regIOobject(io),
	extendedEdgeMesh
	(
		pts,
		eds,
		concaveStart,
		mixedStart,
		nonFeatureStart,
		internalStart,
		flatStart,
		openStart,
		multipleStart,
		normals,
		normalVolumeTypes,
		edgeDirections,
		normalDirections,
		edgeNormals,
		featurePointNormals,
		featurePointEdges,
		regionEdges
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::extendedFeatureEdgeMesh::~extendedFeatureEdgeMesh()
{}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::extendedFeatureEdgeMesh::readData(Istream& is)
{
	is >> *this;
	return !is.bad();
}


bool tnbLib::extendedFeatureEdgeMesh::writeData(Ostream& os) const
{
	os << *this;

	return os.good();
}



//bool tnbLib::extendedFeatureEdgeMesh::writeData(Ostream& os) const
//{
//    os  << "// points" << nl
//        << points() << nl
//        << "// edges" << nl
//        << edges() << nl
//        << "// concaveStart mixedStart nonFeatureStart" << nl
//        << concaveStart_ << token::SPACE
//        << mixedStart_ << token::SPACE
//        << nonFeatureStart_ << nl
//        << "// internalStart flatStart openStart multipleStart" << nl
//        << internalStart_ << token::SPACE
//        << flatStart_ << token::SPACE
//        << openStart_ << token::SPACE
//        << multipleStart_ << nl
//        << "// normals" << nl
//        << normals_ << nl
//        << "// normal volume types" << nl
//        << normalVolumeTypes_ << nl
//        << "// normalDirections" << nl
//        << normalDirections_ << nl
//        << "// edgeNormals" << nl
//        << edgeNormals_ << nl
//        << "// featurePointNormals" << nl
//        << featurePointNormals_ << nl
//        << "// featurePointEdges" << nl
//        << featurePointEdges_ << nl
//        << "// regionEdges" << nl
//        << regionEdges_
//        << endl;
//
//    return os.good();
//}

//
//tnbLib::Istream& tnbLib::operator>>
//(
//    Istream& is,
//    tnbLib::extendedFeatureEdgeMesh::sideVolumeType& vt
//)
//{
//    label type;
//    is  >> type;
//
//    vt = static_cast<tnbLib::extendedFeatureEdgeMesh::sideVolumeType>(type);
//
//    // Check state of Istream
//    is.check("operator>>(Istream&, sideVolumeType&)");
//
//    return is;
//}
//
//
//tnbLib::Ostream& tnbLib::operator<<
//(
//    Ostream& os,
//    const tnbLib::extendedFeatureEdgeMesh::sideVolumeType& vt
//)
//{
//    os  << static_cast<label>(vt);
//
//    return os;
//}
//

// ************************************************************************* //