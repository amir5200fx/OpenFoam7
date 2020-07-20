#include <localEulerDdtScheme.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::word tnbLib::fv::localEulerDdt::rDeltaTName("rDeltaT");
tnbLib::word tnbLib::fv::localEulerDdt::rDeltaTfName("rDeltaTf");
tnbLib::word tnbLib::fv::localEulerDdt::rSubDeltaTName("rSubDeltaT");

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

bool tnbLib::fv::localEulerDdt::enabled(const fvMesh& mesh)
{
	return
		word(mesh.ddtScheme("default"))
		== fv::localEulerDdtScheme<scalar>::typeName;
}


const tnbLib::volScalarField& tnbLib::fv::localEulerDdt::localRDeltaT
(
	const fvMesh& mesh
)
{
	return mesh.objectRegistry::lookupObject<volScalarField>
		(
			mesh.time().subCycling() ? rSubDeltaTName : rDeltaTName
			);
}


const tnbLib::surfaceScalarField& tnbLib::fv::localEulerDdt::localRDeltaTf
(
	const fvMesh& mesh
)
{
	return mesh.objectRegistry::lookupObject<surfaceScalarField>
		(
			rDeltaTfName
			);
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::fv::localEulerDdt::localRSubDeltaT
(
	const fvMesh& mesh,
	const label nAlphaSubCycles
)
{
	return tmp<volScalarField>
		(
			new volScalarField
			(
				rSubDeltaTName,
				nAlphaSubCycles
				*mesh.objectRegistry::lookupObject<volScalarField>
				(
					rDeltaTName
					)
			)
			);
}


// ************************************************************************* //