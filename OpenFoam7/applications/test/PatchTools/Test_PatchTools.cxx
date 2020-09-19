#include <test.hxx>

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

Application
    testPatchTools

Description
    Test app for PatchTools functionality

\*---------------------------------------------------------------------------*/

#include <PatchTools.hxx>
#include <argList.hxx>
#include <fvMesh.hxx>
#include <volFields.hxx>
#include <Time.hxx>
#include <OBJstream.hxx>

int tnbLib::Test_PatchTools(int argc, char* argv[])
{
#include <addTimeOptions.lxx>
	argList::validArgs.append("patch");
#include <setRootCase.lxx>
#include <createTime.lxx>

#include <createMesh.lxx>

	const word patchName = args[1];
	label patchi = mesh.boundaryMesh().findPatchID(patchName);
	const polyPatch& pp = mesh.boundaryMesh()[patchi];

	const indirectPrimitivePatch& cpp = mesh.globalData().coupledPatch();

	{
		OBJstream str(runTime.path() / "edgePatchNormals.obj");

		labelList patchEdges;
		labelList coupledEdges;
		PackedBoolList sameEdgeOrientation;
		PatchTools::matchEdges
		(
			pp,
			cpp,
			patchEdges,
			coupledEdges,
			sameEdgeOrientation
		);

		const pointField en
		(
			PatchTools::edgeNormals
			(
				mesh,
				pp,
				patchEdges,
				coupledEdges
			)
		);

		forAll(en, patchEdgeI)
		{
			const edge& patchE = pp.edges()[patchEdgeI];
			// str.write(pp.localPoints()[pointi], en[pointi]);
			const point pt = patchE.centre(pp.localPoints());
			str.write(linePointRef(pt, pt + 0.1 * en[patchEdgeI]));
		}
	}

	Pout << "End\n" << endl;

	return 0;
}