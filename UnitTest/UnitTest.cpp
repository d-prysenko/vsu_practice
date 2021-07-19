#include "pch.h"
#include "CppUnitTest.h"
#include "../vsu_practice/Graph.h"
#include "../vsu_practice/Graph.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Graph g("../vsu_practice/graph1.txt");
			
			if (g)
			{
				Assert::AreEqual(g.getDiameter(), FLT_MAX);
				Assert::AreEqual(g.getRadius(), 7.0f);
			}
			else
			{
				Assert::Fail(L"Cannot init graph!");
			}
		}
	};
}
