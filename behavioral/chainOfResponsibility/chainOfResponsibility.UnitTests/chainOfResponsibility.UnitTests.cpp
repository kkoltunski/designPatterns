#include "pch.h"
#include "CppUnitTest.h"
#include "account.h"
#include "taskHandler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace chainOfResponsibilityUnitTests
{
	TEST_CLASS(chainOfResponsibilityUnitTests) {
	public:
		//accountConstructor_whenCalled_correctLoginAssigment
		TEST_METHOD(TestMethod1) {
			std::string testLogin{ "testLogin" };
			account testAccount(testLogin);

			Assert::AreEqual(testLogin, testAccount.getLogin());
		}
	};
}