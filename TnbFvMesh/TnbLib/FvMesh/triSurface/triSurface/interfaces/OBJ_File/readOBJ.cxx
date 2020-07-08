#include <triSurface.hxx>

#include <IFstream.hxx>
#include <IStringStream.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::triSurface::readOBJ(const fileName& OBJfileName)
{
	IFstream OBJfile(OBJfileName);

	if (!OBJfile.good())
	{
		FatalErrorInFunction
			<< "Cannot read file " << OBJfileName
			<< exit(FatalError);
	}

	DynamicList<point> points;
	DynamicList<labelledTri> faces;
	HashTable<label> groupToPatch;

	label groupID = 0;
	label maxGroupID = 0;

	while (OBJfile.good())
	{
		string line = getLineNoComment(OBJfile);

		label sz = line.size();

		if (sz && line[sz - 1] == '\\')
		{
			line.substr(0, sz - 1);
			line += getLineNoComment(OBJfile);
		}

		// Read first word
		IStringStream lineStream(line);
		word cmd;
		lineStream >> cmd;

		if (cmd == "v")
		{
			scalar x, y, z;

			lineStream >> x >> y >> z;

			points.append(point(x, y, z));
		}
		else if (cmd == "g")
		{
			word group;

			lineStream >> group;

			HashTable<label>::const_iterator findGroup =
				groupToPatch.find(group);

			if (findGroup != groupToPatch.end())
			{
				groupID = findGroup();
			}
			else
			{
				groupID = maxGroupID;

				groupToPatch.insert(group, groupID);

				maxGroupID++;
			}
		}
		else if (cmd == "f")
		{
			DynamicList<label> verts;

			// Assume 'f' is followed by space.
			string::size_type endNum = 1;

			while (true)
			{
				string::size_type startNum =
					line.find_first_not_of(" \r", endNum);

				if (startNum == string::npos)
				{
					break;
				}

				endNum = line.find(' ', startNum);

				string vertexSpec;
				if (endNum != string::npos)
				{
					vertexSpec = line.substr(startNum, endNum - startNum);
				}
				else
				{
					vertexSpec = line.substr(startNum, line.size() - startNum);
				}

				string::size_type slashPos = vertexSpec.find('/');

				label vertI = 0;
				if (slashPos != string::npos)
				{
					IStringStream intStream(vertexSpec.substr(0, slashPos));

					intStream >> vertI;
				}
				else
				{
					IStringStream intStream(vertexSpec);

					intStream >> vertI;
				}
				verts.append(vertI - 1);
			}

			verts.shrink();

			// Do simple face triangulation around f[0].
			// Cannot use face::triangulation since no complete points yet.
			for (label fp = 1; fp < verts.size() - 1; fp++)
			{
				label fp1 = verts.fcIndex(fp);

				labelledTri tri(verts[0], verts[fp], verts[fp1], groupID);

				faces.append(tri);
			}
		}
	}

	points.shrink();
	faces.shrink();

	// Convert groupToPatch to patchList.
	geometricSurfacePatchList patches(maxGroupID);

	if (maxGroupID == 0)
	{
		// Generate default patch
		patches.setSize(1);
		patches[0] = geometricSurfacePatch("empty", "patch0", 0);
	}
	else
	{
		forAllConstIter(HashTable<label>, groupToPatch, iter)
		{
			patches[iter()] = geometricSurfacePatch
			(
				"empty",
				iter.key(),
				iter()
			);
		}
	}


	// Transfer DynamicLists to straight ones.
	pointField allPoints(move(points));

	// Create triSurface
	*this = triSurface(faces, patches, allPoints, true);

	return true;
}


// ************************************************************************* //