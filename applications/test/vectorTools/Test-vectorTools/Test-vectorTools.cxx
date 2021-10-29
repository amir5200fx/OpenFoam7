//
//#include <includeAllModules.hxx>
//
//#include <vector.hxx>
//#include <IOstreams.hxx>
//#include <vectorTools.hxx>
//#include <unitConversion.hxx>
//
//using namespace tnbLib;
//
//
//void test(const vector& a, const vector& b, const scalar tolerance)
//{
//    Info << "Vectors " << a << " and " << b
//        << " are (to tolerance of " << tolerance << "): ";
//
//    if (vectorTools::areParallel(a, b, tolerance))
//        Info << " parallel ";
//
//    if (vectorTools::areOrthogonal(a, b, tolerance))
//        Info << " orthogonal ";
//
//    if (vectorTools::areAcute(a, b))
//        Info << " acute ";
//
//    if (vectorTools::areObtuse(a, b))
//        Info << " obtuse ";
//
//    Info << ", angle = " << vectorTools::degAngleBetween(a, b);
//
//    Info << endl;
//}
//
//
//int main()
//{
//    vector a(1.0, 1.0, 1.0);
//    vector b(2.0, 2.0, 2.0);
//
//    test(a, b, 0.0);
//    test(a, b, vSmall);
//    test(a, b, small);
//    test(a, b, 1e-3);
//    test(a, b, 1e-1);
//
//    a = vector(1, 0, 0);
//    b = vector(0, 2, 0);
//
//    test(a, b, 0.0);
//    test(a, b, vSmall);
//    test(a, b, small);
//    test(a, b, 1e-3);
//    test(a, b, 1e-1);
//
//    a = vector(1, 0, 0);
//    b = vector(-1, 0, 0);
//
//    test(a, b, 0.0);
//    test(a, b, vSmall);
//    test(a, b, small);
//    test(a, b, 1e-3);
//    test(a, b, 1e-1);
//
//    a = vector(1, 0, 0);
//    b = vector(-1, 2, 0);
//
//    test(a, b, 0.0);
//    test(a, b, vSmall);
//    test(a, b, small);
//    test(a, b, 1e-3);
//    test(a, b, 1e-1);
//
//    return 0;
//}
