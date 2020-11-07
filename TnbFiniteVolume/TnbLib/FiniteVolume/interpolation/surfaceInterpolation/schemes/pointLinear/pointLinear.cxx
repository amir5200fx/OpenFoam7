#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <pointLinear.hxx>

#include <fvMesh.hxx>
#include <volPointInterpolation.hxx>
#include <triangle.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::pointLinear<Type>::
correction
(
	const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
	const fvMesh& mesh = this->mesh();

	GeometricField<Type, pointPatchField, pointMesh> pvf
	(
		volPointInterpolation::New(mesh).interpolate(vf)
	);

	tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsfCorr =
		linearInterpolate(vf);

	Field<Type>& sfCorr = tsfCorr.ref().primitiveFieldRef();

	const pointField& points = mesh.points();
	const pointField& C = mesh.C();
	const faceList& faces = mesh.faces();
	const scalarField& w = mesh.weights();
	const labelList& owner = mesh.owner();
	const labelList& neighbour = mesh.neighbour();

	forAll(sfCorr, facei)
	{
		point pi =
			w[owner[facei]] * C[owner[facei]]
			+ (1.0 - w[owner[facei]])*C[neighbour[facei]];

		const face& f = faces[facei];

		scalar at = triangle<point, const point&>
			(
				pi,
				points[f[0]],
				points[f[f.size() - 1]]
				).mag();

		scalar sumAt = at;
		Type sumPsip = at * (1.0 / 3.0)*
			(
				sfCorr[facei]
				+ pvf[f[0]]
				+ pvf[f[f.size() - 1]]
				);

		for (label pointi = 1; pointi < f.size(); pointi++)
		{
			at = triangle<point, const point&>
				(
					pi,
					points[f[pointi]],
					points[f[pointi - 1]]
					).mag();

			sumAt += at;
			sumPsip += at * (1.0 / 3.0)*
				(
					sfCorr[facei]
					+ pvf[f[pointi]]
					+ pvf[f[pointi - 1]]
					);

		}

		sfCorr[facei] = sumPsip / sumAt - sfCorr[facei];
	}


	typename GeometricField<Type, fvsPatchField, surfaceMesh>::
		Boundary& bSfCorr = tsfCorr.ref().boundaryFieldRef();

	forAll(bSfCorr, patchi)
	{
		fvsPatchField<Type>& pSfCorr = bSfCorr[patchi];

		if (pSfCorr.coupled())
		{
			const fvPatch& fvp = mesh.boundary()[patchi];
			const scalarField& pWghts = mesh.weights().boundaryField()[patchi];
			const labelUList& pOwner = fvp.faceCells();
			const vectorField& pNbrC = mesh.C().boundaryField()[patchi];

			forAll(pOwner, facei)
			{
				label own = pOwner[facei];

				point pi =
					pWghts[facei] * C[own]
					+ (1.0 - pWghts[facei])*pNbrC[facei];

				const face& f = faces[facei + fvp.start()];

				scalar at = triangle<point, const point&>
					(
						pi,
						points[f[0]],
						points[f[f.size() - 1]]
						).mag();

				scalar sumAt = at;
				Type sumPsip = at * (1.0 / 3.0)*
					(
						pSfCorr[facei]
						+ pvf[f[0]]
						+ pvf[f[f.size() - 1]]
						);

				for (label pointi = 1; pointi < f.size(); pointi++)
				{
					at = triangle<point, const point&>
						(
							pi,
							points[f[pointi]],
							points[f[pointi - 1]]
							).mag();

					sumAt += at;
					sumPsip += at * (1.0 / 3.0)*
						(
							pSfCorr[facei]
							+ pvf[f[pointi]]
							+ pvf[f[pointi - 1]]
							);

				}

				pSfCorr[facei] = sumPsip / sumAt - pSfCorr[facei];
			}
		}
		else
		{
			pSfCorr = Zero;
		}
	}

	return tsfCorr;
}


namespace tnbLib
{
	makeSurfaceInterpolationScheme(pointLinear);
}

// ************************************************************************* //