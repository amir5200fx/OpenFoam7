#include <STARCDMeshWriter.hxx>

#include <Time.hxx>
#include <SortableList.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* tnbLib::meshWriters::STARCD::defaultBoundaryName =
"Default_Boundary_Region";

const tnbLib::label tnbLib::meshWriters::STARCD::foamToStarFaceAddr[4][6] =
{
	{ 4, 5, 2, 3, 0, 1 },     // 11 = pro-STAR hex
	{ 0, 1, 4, 5, 2, -1 },    // 12 = pro-STAR prism
	{ 5, 4, 2, 0, -1, -1 },   // 13 = pro-STAR tetra
	{ 0, 4, 3, 5, 2, -1 }     // 14 = pro-STAR pyramid
};


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::label tnbLib::meshWriters::STARCD::findDefaultBoundary() const
{
	const polyBoundaryMesh& patches = mesh_.boundaryMesh();

	label id = -1;

	// find Default_Boundary_Region if it exists
	forAll(patches, patchi)
	{
		if (defaultBoundaryName == patches[patchi].name())
		{
			id = patchi;
			break;
		}
	}
	return id;
}


void tnbLib::meshWriters::STARCD::getCellTable()
{
	// read constant/polyMesh/propertyName
	IOList<label> ioList
	(
		IOobject
		(
			"cellTableId",
			mesh_.time().constant(),
			polyMesh::meshSubDir,
			mesh_,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE,
			false
		)
	);

	bool useCellZones = false;
	cellTableId_.setSize(mesh_.nCells(), -1);

	// get information from constant/polyMesh/cellTableId if possible
	if (ioList.headerOk())
	{
		if (ioList.size() == mesh_.nCells())
		{
			cellTableId_.transfer(ioList);

			if (cellTable_.empty())
			{
				Info << "no cellTable information available" << endl;
			}
		}
		else
		{
			WarningInFunction
				<< ioList.objectPath() << " has incorrect number of cells "
				<< " - use cellZone information"
				<< endl;

			ioList.clear();
			useCellZones = true;
		}
	}
	else
	{
		useCellZones = true;
	}


	if (useCellZones)
	{
		if (cellTable_.empty())
		{
			Info << "created cellTable from cellZones" << endl;
			cellTable_ = mesh_;
		}

		// track if there are unzoned cells
		label nUnzoned = mesh_.nCells();

		// get the cellZone <-> cellTable correspondence
		Info << "matching cellZones to cellTable" << endl;

		forAll(mesh_.cellZones(), zoneI)
		{
			const cellZone& cZone = mesh_.cellZones()[zoneI];
			if (cZone.size())
			{
				nUnzoned -= cZone.size();

				label tableId = cellTable_.findIndex(cZone.name());
				if (tableId < 0)
				{
					dictionary dict;

					dict.add("Label", cZone.name());
					dict.add("MaterialType", "fluid");
					tableId = cellTable_.append(dict);
				}

				forAll(cZone, i)
				{
					cellTableId_[cZone[i]] = tableId;
				}
			}
		}

		if (nUnzoned)
		{
			dictionary dict;

			dict.add("Label", "__unZonedCells__");
			dict.add("MaterialType", "fluid");
			label tableId = cellTable_.append(dict);

			forAll(cellTableId_, i)
			{
				if (cellTableId_[i] < 0)
				{
					cellTableId_[i] = tableId;
				}
			}
		}
	}
}


void tnbLib::meshWriters::STARCD::writeHeader(Ostream& os, const char* filetype)
{
	os << "PROSTAR_" << filetype << nl
		<< 4000
		<< " " << 0
		<< " " << 0
		<< " " << 0
		<< " " << 0
		<< " " << 0
		<< " " << 0
		<< " " << 0
		<< endl;
}


void tnbLib::meshWriters::STARCD::writePoints(const fileName& prefix) const
{
	OFstream os(prefix + ".vrt");
	writeHeader(os, "VERTEX");

	// Set the precision of the points data to 10
	os.precision(10);

	// force decimal point for Fortran input
	os.setf(std::ios::showpoint);

	const pointField& points = mesh_.points();

	Info << "Writing " << os.name() << " : "
		<< points.size() << " points" << endl;

	forAll(points, ptI)
	{
		// convert [m] -> [mm]
		os
			<< ptI + 1 << " "
			<< scaleFactor_ * points[ptI].x() << " "
			<< scaleFactor_ * points[ptI].y() << " "
			<< scaleFactor_ * points[ptI].z() << nl;
	}
	os.flush();

}


void tnbLib::meshWriters::STARCD::writeCells(const fileName& prefix) const
{
	OFstream os(prefix + ".cel");
	writeHeader(os, "CELL");

	// this is what we seem to need
	// map foam cellModeller index -> star shape
	Map<label> shapeLookupIndex;
	shapeLookupIndex.insert(hexModel->index(), 11);
	shapeLookupIndex.insert(prismModel->index(), 12);
	shapeLookupIndex.insert(tetModel->index(), 13);
	shapeLookupIndex.insert(pyrModel->index(), 14);

	const cellShapeList& shapes = mesh_.cellShapes();
	const cellList& cells = mesh_.cells();
	const faceList& faces = mesh_.faces();
	const labelList& owner = mesh_.faceOwner();

	Info << "Writing " << os.name() << " : "
		<< cells.size() << " cells" << endl;

	forAll(cells, cellId)
	{
		label tableId = cellTableId_[cellId];
		label materialType = 1;        // 1(fluid)
		if (cellTable_.found(tableId))
		{
			const dictionary& dict = cellTable_[tableId];
			if (dict.found("MaterialType"))
			{
				word matType;
				dict.lookup("MaterialType") >> matType;
				if (matType == "solid")
				{
					materialType = 2;
				}

			}
		}

		const cellShape& shape = shapes[cellId];
		label mapIndex = shape.model().index();

		// a registered primitive type
		if (shapeLookupIndex.found(mapIndex))
		{
			label shapeId = shapeLookupIndex[mapIndex];
			const labelList& vrtList = shapes[cellId];

			os << cellId + 1
				<< " " << shapeId
				<< " " << vrtList.size()
				<< " " << tableId
				<< " " << materialType;

			// primitives have <= 8 vertices, but prevent overrun anyhow
			// indent following lines for ease of reading
			label count = 0;
			forAll(vrtList, i)
			{
				if ((count % 8) == 0)
				{
					os << nl
						<< "  " << cellId + 1;
				}
				os << " " << vrtList[i] + 1;
				count++;
			}
			os << endl;

		}
		else
		{
			label shapeId = 255;        // treat as general polyhedral
			const labelList& cFaces = cells[cellId];

			// create (beg,end) indices
			List<label> indices(cFaces.size() + 1);
			indices[0] = indices.size();

			label count = indices.size();
			// determine the total number of vertices
			forAll(cFaces, facei)
			{
				count += faces[cFaces[facei]].size();
				indices[facei + 1] = count;
			}

			os << cellId + 1
				<< " " << shapeId
				<< " " << count
				<< " " << tableId
				<< " " << materialType;

			// write indices - max 8 per line
			// indent following lines for ease of reading
			count = 0;
			forAll(indices, i)
			{
				if ((count % 8) == 0)
				{
					os << nl
						<< "  " << cellId + 1;
				}
				os << " " << indices[i];
				count++;
			}

			// write faces - max 8 per line
			forAll(cFaces, facei)
			{
				label meshFace = cFaces[facei];
				face f;

				if (owner[meshFace] == cellId)
				{
					f = faces[meshFace];
				}
				else
				{
					f = faces[meshFace].reverseFace();
				}

				forAll(f, i)
				{
					if ((count % 8) == 0)
					{
						os << nl
							<< "  " << cellId + 1;
					}

					os << " " << f[i] + 1;
					count++;
				}
			}

			os << endl;
		}
	}
}


void tnbLib::meshWriters::STARCD::writeBoundary(const fileName& prefix) const
{
	OFstream os(prefix + ".bnd");
	writeHeader(os, "BOUNDARY");

	const cellShapeList& shapes = mesh_.cellShapes();
	const cellList& cells = mesh_.cells();
	const faceList& faces = mesh_.faces();
	const labelList& owner = mesh_.faceOwner();
	const polyBoundaryMesh& patches = mesh_.boundaryMesh();

	// this is what we seem to need
	// these MUST correspond to foamToStarFaceAddr
	//
	Map<label> faceLookupIndex;
	faceLookupIndex.insert(hexModel->index(), 0);
	faceLookupIndex.insert(prismModel->index(), 1);
	faceLookupIndex.insert(tetModel->index(), 2);
	faceLookupIndex.insert(pyrModel->index(), 3);

	Info << "Writing " << os.name() << " : "
		<< (mesh_.nFaces() - patches[0].start()) << " boundaries" << endl;


	label defaultId = findDefaultBoundary();

	//
	// write boundary faces - skip Default_Boundary_Region entirely
	//
	label boundId = 0;
	forAll(patches, patchi)
	{
		label regionId = patchi;
		if (regionId == defaultId)
		{
			continue;  // skip - already written
		}
		else if (defaultId == -1 || regionId < defaultId)
		{
			regionId++;
		}

		label patchStart = patches[patchi].start();
		label patchSize = patches[patchi].size();
		word  bndType = boundaryRegion_.boundaryType(patches[patchi].name());

		for
			(
				label facei = patchStart;
				facei < (patchStart + patchSize);
				++facei
				)
		{
			label cellId = owner[facei];
			const labelList& cFaces = cells[cellId];
			const cellShape& shape = shapes[cellId];
			label cellFaceId = findIndex(cFaces, facei);

			//      Info<< "cell " << cellId + 1 << " face " << facei
			//          << " == " << faces[facei]
			//          << " is index " << cellFaceId << " from " << cFaces;

			// Unfortunately, the order of faces returned by
			//   primitiveMesh::cells() is not necessarily the same
			//   as defined by primitiveMesh::cellShapes()
			// Thus, for registered primitive types, do the lookup ourselves.
			// Finally, the cellModel face number is re-mapped to the
			// STAR-CD local face number

			label mapIndex = shape.model().index();

			// a registered primitive type
			if (faceLookupIndex.found(mapIndex))
			{
				const faceList sFaces = shape.faces();
				forAll(sFaces, sFacei)
				{
					if (faces[facei] == sFaces[sFacei])
					{
						cellFaceId = sFacei;
						break;
					}
				}

				mapIndex = faceLookupIndex[mapIndex];
				cellFaceId = foamToStarFaceAddr[mapIndex][cellFaceId];
			}
			// Info<< endl;

			boundId++;

			os
				<< boundId
				<< " " << cellId + 1
				<< " " << cellFaceId + 1
				<< " " << regionId
				<< " " << 0
				<< " " << bndType.c_str()
				<< endl;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::meshWriters::STARCD::STARCD
(
	const polyMesh& mesh,
	const scalar scaleFactor
)
	:
	meshWriter(mesh, scaleFactor)
{
	boundaryRegion_.readDict(mesh_);
	cellTable_.readDict(mesh_);
	getCellTable();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::meshWriters::STARCD::~STARCD()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::meshWriters::STARCD::rmFiles(const fileName& baseName) const
{
	rm(baseName + ".vrt");
	rm(baseName + ".cel");
	rm(baseName + ".bnd");
	rm(baseName + ".inp");
}


bool tnbLib::meshWriters::STARCD::write(const fileName& meshName) const
{
	fileName baseName(meshName);

	if (baseName.empty())
	{
		baseName = meshWriter::defaultMeshName;

		if
			(
				mesh_.time().timeName() != "0"
				&& mesh_.time().timeName() != mesh_.time().constant()
				)
		{
			baseName += "_" + mesh_.time().timeName();
		}
	}

	rmFiles(baseName);
	writePoints(baseName);
	writeCells(baseName);

	if (writeBoundary_)
	{
		writeBoundary(baseName);
	}

	return true;
}


// ************************************************************************* //