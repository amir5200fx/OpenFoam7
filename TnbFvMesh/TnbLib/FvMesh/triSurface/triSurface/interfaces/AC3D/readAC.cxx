#include <triSurface.hxx>

/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
	\\  /    A nd           | Copyright (C) 2011-2019 OpenFOAM Foundation
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

Description
	Reader for .ac files generated by AC3D.

	See http://www.ac3d.org/ac3d/man/ac3dfileformat.html

\*---------------------------------------------------------------------------*/

#include <IFstream.hxx>
#include <IStringStream.hxx>
#include <transform.hxx>
#include <tensor.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

	static label parseInt(const string& str)
	{
		IStringStream intStream(str);

		label a;

		intStream >> a;

		return a;
	}


	static bool readCmd(IFstream& ACfile, string& cmd, string& args)
	{
		if (ACfile.good())
		{
			string line;
			ACfile.getLine(line);

			string::size_type space = line.find(' ');

			if (space != string::npos)
			{
				cmd = line.substr(0, space);
				args = line.substr(space + 1);

				return true;
			}
		}
		return false;
	}


	// Read up to line starting with cmd. Sets args to rest of line.
	// Returns true if found, false if stream is not good anymore.
	static bool readUpto
	(
		const string& cmd,
		IFstream& ACfile,
		string& args
	)
	{
		while (ACfile.good())
		{
			string line;
			ACfile.getLine(line);

			string::size_type space = line.find(' ');

			if (space != string::npos && line.substr(0, space) == cmd)
			{
				args = line.substr(space + 1);
				return true;
			}
		}
		return false;
	}


	// Likewise but throws error if cmd not found
	static void readUpto
	(
		const string& cmd,
		IFstream& ACfile,
		string& args,
		const string errorMsg
	)
	{
		if (!readUpto(cmd, ACfile, args))
		{
			FatalErrorInFunction
				<< "Cannot find command " << cmd
				<< errorMsg << exit(FatalError);
		}
	}


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	bool triSurface::readAC(const fileName& ACfileName)
	{
		IFstream ACfile(ACfileName);

		if (!ACfile.good())
		{
			FatalErrorInFunction
				<< "Cannot read file " << ACfileName
				<< exit(FatalError);
		}

		string line;
		ACfile.getLine(line);

		string version = line.substr(4);

		if (version != "b")
		{
			WarningInFunction
				<< "When reading AC3D file " << ACfileName
				<< " read header " << line << " with version " << version
				<< endl << "Only tested reading with version 'b'."
				<< " This might give problems" << endl;
		}

		string cmd;

		string args;

		if (!readUpto("OBJECT", ACfile, args) || (args != "world"))
		{
			FatalErrorInFunction
				<< "Cannot find \"OBJECT world\" in file " << ACfileName
				<< exit(FatalError);
		}

		// Number of kids = patches

		readUpto("kids", ACfile, args, "");

		label nPatches = parseInt(args);

		// Storage for patches and unmerged points and faces

		DynamicList<point> points;
		DynamicList<labelledTri> faces;
		geometricSurfacePatchList patches(nPatches);


		// Start of vertices for object/patch
		label patchStartVert = 0;

		for (label patchi = 0; patchi < nPatches; patchi++)
		{
			readUpto
			(
				"OBJECT",
				ACfile,
				args,
				" while reading patch " + tnbLib::name(patchi)
			);

			// Object global values
			string patchName = string("patch") + name(patchi);
			label nVerts = 0;
			tensor rot(I);
			vector loc(0, 0, 0);

			// Read all info for current patch
			while (ACfile.good())
			{
				// Read line and get first word. If end of file break since
				// patch should always end with 'kids' command ?not sure.
				if (!readCmd(ACfile, cmd, args))
				{
					FatalErrorInFunction
						<< "Did not read up to \"kids 0\" while reading patch "
						<< patchi << " from file " << ACfileName
						<< exit(FatalError);
				}

				if (cmd == "name")
				{
					IStringStream nameStream(args);

					nameStream >> patchName;
				}
				else if (cmd == "rot")
				{
					// rot %f %f %f  %f %f %f  %f %f %f
					IStringStream lineStream(args);

					lineStream
						>> rot.xx() >> rot.xy() >> rot.xz()
						>> rot.yx() >> rot.yy() >> rot.yz()
						>> rot.zx() >> rot.zy() >> rot.zz();

					WarningInFunction
						<< "rot (rotation tensor) command not implemented"
						<< "Line:" << cmd << ' ' << args << endl
						<< "while reading patch " << patchi << endl;
				}
				else if (cmd == "loc")
				{
					IStringStream lineStream(args);

					lineStream >> loc.x() >> loc.y() >> loc.z();
				}
				else if (cmd == "numvert")
				{
					nVerts = parseInt(args);

					for (label vertI = 0; vertI < nVerts; vertI++)
					{
						ACfile.getLine(line);

						IStringStream lineStream(line);

						point pt;

						lineStream >> pt.x() >> pt.y() >> pt.z();

						// Offset with current translation vector
						points.append(pt + loc);
					}
				}
				else if (cmd == "numsurf")
				{
					label nTris = parseInt(args);

					for (label triI = 0; triI < nTris; triI++)
					{
						static string errorMsg =
							string(" while reading face ")
							+ name(triI) + " on patch " + name(patchi)
							+ " from file " + ACfileName;

						readUpto("SURF", ACfile, args, errorMsg);
						readUpto("mat", ACfile, args, errorMsg);
						readUpto("refs", ACfile, args, errorMsg);

						label size = parseInt(args);

						if (size != 3)
						{
							FatalErrorInFunction
								<< "Can only read surfaces with 3 vertices."
								<< endl
								<< "Detected " << size << " when reading triangle "
								<< triI << " of patch " << patchi
								<< exit(FatalError);
						}

						ACfile.getLine(line);

						label v0 = parseInt(line);

						ACfile.getLine(line);

						label v1 = parseInt(line);

						ACfile.getLine(line);

						label v2 = parseInt(line);

						faces.append
						(
							labelledTri
							(
								v0 + patchStartVert,
								v1 + patchStartVert,
								v2 + patchStartVert,
								patchi
							)
						);
					}

					// Done the current patch. Increment the offset vertices are
					// stored at
					patchStartVert += nVerts;
				}
				else if (cmd == "kids")
				{
					// 'kids' denotes the end of the current patch.

					label nKids = parseInt(args);

					if (nKids != 0)
					{
						FatalErrorInFunction
							<< "Can only read objects without kids."
							<< " Encountered " << nKids << " kids when"
							<< " reading patch " << patchi
							<< exit(FatalError);
					}

					patches[patchi] =
						geometricSurfacePatch
						(
							"empty",
							word(patchName),
							patchi
						);

					// Stop reading current patch
					break;
				}
			}
		}

		faces.shrink();

		// Transfer DynamicLists to straight ones.
		pointField allPoints(move(points));

		*this = triSurface(faces, patches, allPoints, true);

		stitchTriangles();

		return true;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //