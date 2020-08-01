#include <fvcMeshPhi.hxx>

#include <fvMesh.hxx>
#include <ddtScheme.hxx>
#include <surfaceInterpolate.hxx>
 
#include <volFields.hxx>  // added by amir
#include <surfaceMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::meshPhi
(
	const volVectorField& vf
)
{
	return fv::ddtScheme<vector>::New
	(
		vf.mesh(),
		vf.mesh().ddtScheme("ddt(" + vf.name() + ')')
	).ref().meshPhi(vf);
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::meshPhi
(
	const dimensionedScalar& rho,
	const volVectorField& vf
)
{
	return fv::ddtScheme<vector>::New
	(
		vf.mesh(),
		vf.mesh().ddtScheme("ddt(" + rho.name() + ',' + vf.name() + ')')
	).ref().meshPhi(vf);
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::meshPhi
(
	const volScalarField& rho,
	const volVectorField& vf
)
{
	return fv::ddtScheme<vector>::New
	(
		vf.mesh(),
		vf.mesh().ddtScheme("ddt(" + rho.name() + ',' + vf.name() + ')')
	).ref().meshPhi(vf);
}


void tnbLib::fvc::makeRelative
(
	surfaceScalarField& phi,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi -= fvc::meshPhi(U);
	}
}

void tnbLib::fvc::makeRelative
(
	surfaceScalarField& phi,
	const dimensionedScalar& rho,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi -= rho * fvc::meshPhi(rho, U);
	}
}

void tnbLib::fvc::makeRelative
(
	surfaceScalarField& phi,
	const volScalarField& rho,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi -= fvc::interpolate(rho)*fvc::meshPhi(rho, U);
	}
}


void tnbLib::fvc::makeAbsolute
(
	surfaceScalarField& phi,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi += fvc::meshPhi(U);
	}
}

void tnbLib::fvc::makeAbsolute
(
	surfaceScalarField& phi,
	const dimensionedScalar& rho,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi += rho * fvc::meshPhi(rho, U);
	}
}

void tnbLib::fvc::makeAbsolute
(
	surfaceScalarField& phi,
	const volScalarField& rho,
	const volVectorField& U
)
{
	if (phi.mesh().moving())
	{
		phi += fvc::interpolate(rho)*fvc::meshPhi(rho, U);
	}
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::relative
(
	const tmp<surfaceScalarField>& tphi,
	const volVectorField& U
)
{
	if (tphi().mesh().moving())
	{
		return tphi - fvc::meshPhi(U);
	}
	else
	{
		return tmp<surfaceScalarField>(tphi, true);
	}
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::relative
(
	const tmp<surfaceScalarField>& tphi,
	const volScalarField& rho,
	const volVectorField& U
)
{
	if (tphi().mesh().moving())
	{
		return tphi - fvc::interpolate(rho)*fvc::meshPhi(rho, U);
	}
	else
	{
		return tmp<surfaceScalarField>(tphi, true);
	}
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::absolute
(
	const tmp<surfaceScalarField>& tphi,
	const volVectorField& U
)
{
	if (tphi().mesh().moving())
	{
		return tphi + fvc::meshPhi(U);
	}
	else
	{
		return tmp<surfaceScalarField>(tphi, true);
	}
}


tnbLib::tmp<tnbLib::surfaceScalarField> tnbLib::fvc::absolute
(
	const tmp<surfaceScalarField>& tphi,
	const volScalarField& rho,
	const volVectorField& U
)
{
	if (tphi().mesh().moving())
	{
		return tphi + fvc::interpolate(rho)*fvc::meshPhi(rho, U);
	}
	else
	{
		return tmp<surfaceScalarField>(tphi, true);
	}
}


void tnbLib::fvc::correctUf
(
	autoPtr<surfaceVectorField>& Uf,
	const volVectorField& U,
	const surfaceScalarField& phi
)
{
	const fvMesh& mesh = U.mesh();

	if (mesh.dynamic())
	{
		Uf() = fvc::interpolate(U);
		surfaceVectorField n(mesh.Sf() / mesh.magSf());
		Uf() += n * (phi / mesh.magSf() - (n & Uf()));
	}
}


void tnbLib::fvc::correctRhoUf
(
	autoPtr<surfaceVectorField>& rhoUf,
	const volScalarField& rho,
	const volVectorField& U,
	const surfaceScalarField& phi
)
{
	const fvMesh& mesh = U.mesh();

	if (mesh.dynamic())
	{
		rhoUf() = fvc::interpolate(rho*U);
		surfaceVectorField n(mesh.Sf() / mesh.magSf());
		rhoUf() += n * (fvc::absolute(phi, rho, U) / mesh.magSf() - (n & rhoUf()));
	}
}


// ************************************************************************* //