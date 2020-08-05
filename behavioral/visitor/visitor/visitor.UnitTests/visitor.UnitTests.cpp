#include "pch.h"
#include "CppUnitTest.h"
#include "concreteNumericStrings.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace visitorUnitTests
{	
	double exampleFactor{}, testTolerance{};


	TEST_CLASS(numericStringUnitTests) {
	private:
		TEST_CLASS_INITIALIZE(tearsUp) {
			exampleFactor = 1.5;
		}

		aritmeticString testStringA{ 0, exampleFactor };
		geometricString testStringG{ 1.23, exampleFactor };

	public:
		TEST_METHOD(getFactor_afterCreateNumericString_returnsFactor) {
			Assert::AreEqual(exampleFactor, testStringA.shareFactor());
			Assert::AreEqual(exampleFactor, testStringG.shareFactor());
		}
	};

	TEST_CLASS(aritmeticStromgUnitTests) {
	private:
		TEST_CLASS_INITIALIZE(terasUp) {
			exampleFactor = 8;
			testTolerance = 0.00001;
		}

		aritmeticString testString{ 0, exampleFactor };

	public:
		TEST_METHOD(getN_returnsNelementOfStringWhichIsEqualNfactors) {
			double elementIndex = 3;
			Assert::AreEqual(16.0, testString.getN(elementIndex));
		}

		TEST_METHOD(getSum_returnsSumOfNelements) {
			size_t firstElementIndexToSum = 0;
			size_t elementsToSum = 4;

			Assert::AreEqual(48.0, testString.getSum(firstElementIndexToSum, elementsToSum), testTolerance);
		}
	};
	TEST_CLASS(geometricStringUnitTests) {
	private:

		TEST_CLASS_INITIALIZE(tearsUp) {
			exampleFactor = 0.34;
			testTolerance = 0.00001;
		}

		geometricString testString{ 1.23, exampleFactor };

	public:
		//No sens of this test because computations are the same what method does
		TEST_METHOD(getN_returnsNelementOfStringWhichIsEqualNfactors) {
			double elementIndex = 3;
			double result{ testString.getN(0) };

			for (size_t i = 1; i < elementIndex; ++i) {
				result *= exampleFactor;
			}

			Assert::AreEqual(result, testString.getN(elementIndex));
		}

		TEST_METHOD(getSum_returnsSumOfNelements) {
			size_t firstElementIndexToSum = 0;
			size_t elementsToSum = 3;

			Assert::AreEqual(1.790388, testString.getSum(firstElementIndexToSum, elementsToSum), testTolerance);
		}
	};
}
