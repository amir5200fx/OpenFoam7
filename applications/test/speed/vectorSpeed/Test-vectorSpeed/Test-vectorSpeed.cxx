
#include <includeAllModules.hxx>

#include <primitiveFields.hxx>
#include <cpuTime.hxx>
#include <IOstreams.hxx>
#include <OFstream.hxx>

using namespace tnbLib;

int main()
{
    const label nIter = 100;
    const label size = 1000000;

    Info << "Initialising fields" << endl;

    vectorField
        vf1(size, vector::one),
        vf2(size, vector::one),
        vf3(size, vector::one),
        vf4(size);

    Info << "Done\n" << endl;

    {
        cpuTime executionTime;

        Info << "vectorField algebra" << endl;

        for (int j = 0; j < nIter; j++)
        {
            vf4 = vf1 + vf2 - vf3;
        }

        Info << "ExecutionTime = "
            << executionTime.elapsedCpuTime()
            << " s\n" << endl;

        Snull << vf4[1] << endl << endl;
    }
}
