#include <IATETwoPhase.hxx>

#include <IATEsourceTwoPhase.hxx>
#include <fvcAverage.hxx>
#include <fvcDdt.hxx>
#include <fvcDiv.hxx>
#include <fvOptions.hxx>
#include <fvMatrices.hxx>
#include <fvmDdt.hxx>
#include <fvmDiv.hxx>
#include <fvmSup.hxx>
#include <fvm.hxx>

void tnbLib::diameterModels::IATE::correct()
{
    // Initialise the accumulated source term to the dilatation effect
    volScalarField R
    (
        (
            (1.0 / 3.0)
            / max
            (
                0.5 * fvc::average(phase_ + phase_.oldTime()),
                residualAlpha_
            )
            )
        * (fvc::ddt(phase_) + fvc::div(phase_.alphaPhi()))
    );

    // Accumulate the run-time selectable sources
    forAll(sources_, j)
    {
        R -= sources_[j].R();
    }

    fv::options& fvOptions(fv::options::New(phase_.mesh()));

    // Construct the interfacial curvature equation
    fvScalarMatrix kappaiEqn
    (
        fvm::ddt(kappai_) + fvm::div(phase_.phi(), kappai_)
        - fvm::Sp(fvc::div(phase_.phi()), kappai_)
        ==
        -fvm::SuSp(R, kappai_)
        //+ Rph() // Omit the nucleation/condensation term
        + fvOptions(kappai_)
    );

    kappaiEqn.relax();

    fvOptions.constrain(kappaiEqn);

    kappaiEqn.solve();

    // Update the Sauter-mean diameter
    d_ = dsm();
}

bool tnbLib::diameterModels::IATE::read(const dictionary& phaseProperties)
{
    diameterModel::read(phaseProperties);

    diameterProperties_.lookup("dMax") >> dMax_;
    diameterProperties_.lookup("dMin") >> dMin_;

    // Re-create all the sources updating number, type and coefficients
    PtrList<IATEsource>
        (
            diameterProperties_.lookup("sources"),
            IATEsource::iNew(*this)
            ).transfer(sources_);

    return true;
}