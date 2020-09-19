#pragma once
#ifndef _test_Header
#define _test_Header

namespace tnbLib
{

	void Test_BinSum();

	void Test_callback();

	void Test_Circulator();

	void Test_CompactIOList(int argc, char *argv[]);

	void Test_cyclic(int argc, char *argv[]);

	void Test_DLList();

	void Test_DynamicField();

	void Test_List();

	void Test_cubicEqn();

	void Test_CompactListList();

	void Test_dimensionedType();

	void Test_Dictionary();

	void Test_dictionary(int argc, char *argv[]);

	void Test_Distribution(int argc, char *argv[]);

	void Test_dynamicIndexedOctree(int argc, char *argv[]);

	void Test_DynamicList();

	void Test_error();

	void Test_fieldDependency(int argc, char *argv[]);

	void Test_fileName();

	void Test_fileNameClean(int argc, char* argv[]);

	void Test_findCell_octree(int argc, char* argv[]);

	void Test_findSphereFeatureEdges_octree(int argc, char* argv[]);

	void Test_findTimes(int argc, char* argv[]);

	void Test_FixedList(int argc, char* argv[]);

	void Test_tnbVersion();

	// int Test_Function1(int argc, char* argv[]); //Compiled with link error

	void Test_fvc(int argc, char* argv[]);

	int Test_fvSolutionCombine(int argc, char* argv[]);

	int Test_GAMGAgglomeration(int argc, char* argv[]);

	int Test_globalIndex(int argc, char* argv[]);

	int Test_globalMeshData(int argc, char* argv[]);

	void Test_graph();

	void Test_graph2();

	void Test_graphXi();

	void Test_Hashing();

	void Test_HashPtrTable();

	void Test_HashSet();

	void Test_HashTable();

	void Test_HashTable2();

	void Test_HashTable3();

	int Test_hexRef8(int argc, char* argv[]);

	void Test_IndirectList();

	void Test_io();

	int Test_IOField(int argc, char* argv[]);

	void Test_ISLList();

	void Test_IStringStream();

	int Test_labelRanges(int argc, char* argv[]);

	void Test_liquid();

	void Test_ListHashTable();

	void Test_ListOps();

	void Test_Map();

	int Test_mappedPatch(int argc, char* argv[]);

	void Test_Matrix();

	void Test_memInfo();

	int Test_mesh(int argc, char* argv[]);

	void Test_mkdir();

	int Test_momentOfInertia(int argc, char* argv[]);

	int Test_mvBak(int argc, char* argv[]);

	void Test_NamedEnum();

	void Test_nullObject();

	int Test_ODE(int argc, char* argv[]);

	void Test_OStringStream();

	int Test_PackedList(int argc, char* argv[]);

	void Test_PackedList1();

	//void Test_PackedList2(); // <StaticHashTable.hxx> was not found

	void Test_PackedList3();

	void Test_PackedList4();

	int Test_parallel(int argc, char* argv[]);

	int Test_parallel_communicators(int argc, char* argv[]);

	int Test_parallel_nonBlocking(int argc, char* argv[]);

	int Test_passiveParticle(int argc, char* argv[]);

	int Test_PatchEdgeFaceWave(int argc, char* argv[]);

	int Test_patchRegion(int argc, char* argv[]);

	int Test_PatchTools(int argc, char* argv[]);

	//int Test_PointEdgeWave(int argc, char* argv[]); // Compiled with link error

	//int Test_pointField(int argc, char* argv[]); // error "'const TestType *': invalid target type for dynamic_cast	"

	void Test_Polynomial();

	void Test_POSIX();

	int Test_prefixOSstream(int argc, char* argv[]);

	int Test_primitivePatch(int argc, char* argv[]);

	void Test_pTraits();

	void Test_PtrList();

	void Test_PtrListDictionary();

	void Test_quaternion(); // compiled with error

	int Test_reconstruct(int argc, char* argv[]);

	void Test_regex();

	//int Test_rigidBodyDynamics(int argc, char* argv[]); // <rigidBodyMotion.hxx> was not found

	void Test_sha1(); // compiled with error

	void Test_simpleMatrix();

	void Test_sizeof();

	int Test_slicedField(int argc, char* argv[]);

	void Test_SLList();

	void Test_sort();

	void Test_scalarSpeed();

	void Test_vectorSpeed();

	void Test_sphericalTensorField();

	int Test_spline(int argc, char* argv[]);

	void Test_string(); // compiled with error

	void Test_stringList();

	void Test_symmTensorField();

	int Test_syncTools(int argc, char* argv[]);

	void Test_tensor();

	void Test_tensor2D();

	void Test_tetTetOverlap();

	//void Test_thermoMixture(); // Compiled with link error

	void Test_tmpField();

	int Test_tokenize(int argc, char* argv[]);

	void Test_triTet();

	void Test_Tuple2();

	void Test_UDictionary();

	void Test_UIndirectList();

	void Test_UniformField();

	void Test_vector();

	// void Test_vectorTools(); // <vectorTools.hxx> was not found

	int Test_volField(int argc, char* argv[]);

	//int Test_volPointInterpolation(int argc, char* argv[]); // Compiled with link error

	//int Test_wallDist(int argc, char* argv[]); // Compiled with link error

	void Test_wordRe();
}

#endif // !_test_Header
