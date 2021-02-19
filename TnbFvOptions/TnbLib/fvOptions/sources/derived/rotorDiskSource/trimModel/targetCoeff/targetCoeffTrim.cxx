#include <targetCoeffTrim.hxx>

#include <geometricOneField.hxx>
#include <addToRunTimeSelectionTable.hxx>

using namespace tnbLib::constant;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(targetCoeffTrim, 0);

	addToRunTimeSelectionTable(trimModel, targetCoeffTrim, dictionary);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class RhoFieldType>
tnbLib::vector tnbLib::targetCoeffTrim::calcCoeffs
(
	const RhoFieldType& rho,
	const vectorField& U,
	const scalarField& thetag,
	vectorField& force
) const
{
	rotor_.calculate(rho, U, thetag, force, false, false);

	const labelList& cells = rotor_.cells();
	const vectorField& C = rotor_.mesh().C();
	const List<point>& x = rotor_.x();

	const vector& origin = rotor_.coordSys().origin();
	const vector& rollAxis = rotor_.coordSys().R().e1();
	const vector& pitchAxis = rotor_.coordSys().R().e2();
	const vector& yawAxis = rotor_.coordSys().R().e3();

	scalar coeff1 = alpha_ * sqr(rotor_.omega())*mathematical::pi;

	vector cf(Zero);
	forAll(cells, i)
	{
		label celli = cells[i];

		vector fc = force[celli];
		vector mc = fc ^ (C[celli] - origin);

		if (useCoeffs_)
		{
			scalar radius = x[i].x();
			scalar coeff2 = rho[celli] * coeff1*pow4(radius);

			// add to coefficient vector
			cf[0] += (fc & yawAxis) / (coeff2 + rootVSmall);
			cf[1] += (mc & pitchAxis) / (coeff2*radius + rootVSmall);
			cf[2] += (mc & rollAxis) / (coeff2*radius + rootVSmall);
		}
		else
		{
			cf[0] += fc & yawAxis;
			cf[1] += mc & pitchAxis;
			cf[2] += mc & rollAxis;
		}
	}

	reduce(cf, sumOp<vector>());

	return cf;
}


template<class RhoFieldType>
void tnbLib::targetCoeffTrim::correctTrim
(
	const RhoFieldType& rho,
	const vectorField& U,
	vectorField& force
)
{
	if (rotor_.mesh().time().timeIndex() % calcFrequency_ == 0)
	{
		word calcType = "forces";
		if (useCoeffs_)
		{
			calcType = "coefficients";
		}

		Info << type() << ":" << nl
			<< "    solving for target trim " << calcType << nl;

		const scalar rhoRef = rotor_.rhoRef();

		// iterate to find new pitch angles to achieve target force
		scalar err = great;
		label iter = 0;
		tensor J(Zero);

		vector old = Zero;
		while ((err > tol_) && (iter < nIter_))
		{
			// cache initial theta vector
			vector theta0(theta_);

			// set initial values
			old = calcCoeffs(rho, U, thetag(), force);

			// construct Jacobian by perturbing the pitch angles
			// by +/-(dTheta_/2)
			for (label pitchI = 0; pitchI < 3; pitchI++)
			{
				theta_[pitchI] -= dTheta_ / 2.0;
				vector cf0 = calcCoeffs(rho, U, thetag(), force);

				theta_[pitchI] += dTheta_;
				vector cf1 = calcCoeffs(rho, U, thetag(), force);

				vector ddTheta = (cf1 - cf0) / dTheta_;

				J[pitchI + 0] = ddTheta[0];
				J[pitchI + 3] = ddTheta[1];
				J[pitchI + 6] = ddTheta[2];

				theta_ = theta0;
			}

			// calculate the change in pitch angle vector
			vector dt = inv(J) & (target_ / rhoRef - old);

			// update pitch angles
			vector thetaNew = theta_ + relax_ * dt;

			// update error
			err = mag(thetaNew - theta_);

			// update for next iteration
			theta_ = thetaNew;
			iter++;
		}

		if (iter == nIter_)
		{
			Info << "    solution not converged in " << iter
				<< " iterations, final residual = " << err
				<< "(" << tol_ << ")" << endl;
		}
		else
		{
			Info << "    final residual = " << err << "(" << tol_
				<< "), iterations = " << iter << endl;
		}

		Info << "    current and target " << calcType << nl
			<< "        thrust  = " << old[0] * rhoRef << ", " << target_[0] << nl
			<< "        pitch   = " << old[1] * rhoRef << ", " << target_[1] << nl
			<< "        roll    = " << old[2] * rhoRef << ", " << target_[2] << nl
			<< "    new pitch angles [deg]:" << nl
			<< "        theta0  = " << radToDeg(theta_[0]) << nl
			<< "        theta1c = " << radToDeg(theta_[1]) << nl
			<< "        theta1s = " << radToDeg(theta_[2]) << nl
			<< endl;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::targetCoeffTrim::targetCoeffTrim
(
	const fv::rotorDiskSource& rotor,
	const dictionary& dict
)
	:
	trimModel(rotor, dict, typeName),
	calcFrequency_(-1),
	useCoeffs_(true),
	target_(Zero),
	theta_(Zero),
	nIter_(50),
	tol_(1e-8),
	relax_(1.0),
	dTheta_(degToRad(0.1)),
	alpha_(1.0)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

tnbLib::targetCoeffTrim::~targetCoeffTrim()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::targetCoeffTrim::read(const dictionary& dict)
{
	trimModel::read(dict);

	const dictionary& targetDict(coeffs_.subDict("target"));
	useCoeffs_ = targetDict.lookupOrDefault<bool>("useCoeffs", true);
	word ext = "";
	if (useCoeffs_)
	{
		ext = "Coeff";
	}

	target_[0] = readScalar(targetDict.lookup("thrust" + ext));
	target_[1] = readScalar(targetDict.lookup("pitch" + ext));
	target_[2] = readScalar(targetDict.lookup("roll" + ext));

	const dictionary& pitchAngleDict(coeffs_.subDict("pitchAngles"));
	theta_[0] = degToRad(readScalar(pitchAngleDict.lookup("theta0Ini")));
	theta_[1] = degToRad(readScalar(pitchAngleDict.lookup("theta1cIni")));
	theta_[2] = degToRad(readScalar(pitchAngleDict.lookup("theta1sIni")));

	coeffs_.lookup("calcFrequency") >> calcFrequency_;

	coeffs_.readIfPresent("nIter", nIter_);
	coeffs_.readIfPresent("tol", tol_);
	coeffs_.readIfPresent("relax", relax_);

	if (coeffs_.readIfPresent("dTheta", dTheta_))
	{
		dTheta_ = degToRad(dTheta_);
	}

	alpha_ = readScalar(coeffs_.lookup("alpha"));
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::targetCoeffTrim::thetag() const
{
	const List<vector>& x = rotor_.x();

	tmp<scalarField> ttheta(new scalarField(x.size()));
	scalarField& t = ttheta.ref();

	forAll(t, i)
	{
		scalar psi = x[i].y();
		t[i] = theta_[0] + theta_[1] * cos(psi) + theta_[2] * sin(psi);
	}

	return ttheta;
}


void tnbLib::targetCoeffTrim::correct
(
	const vectorField& U,
	vectorField& force
)
{
	correctTrim(geometricOneField(), U, force);
}


void tnbLib::targetCoeffTrim::correct
(
	const volScalarField rho,
	const vectorField& U,
	vectorField& force
)
{
	correctTrim(rho, U, force);
}


// ************************************************************************* //