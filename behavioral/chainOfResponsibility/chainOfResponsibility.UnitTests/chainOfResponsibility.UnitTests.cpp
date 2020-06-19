#include "pch.h"
#include "CppUnitTest.h"
#include "account.h"
#include "taskHandler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace chainOfResponsibilityUnitTests
{
	accountsManagement manager;
	account testAccount{ "testLogin" };

	//whichMethod_conditions_expectedResult
	TEST_CLASS(accountUnitTests) {
	public:
		TEST_METHOD(accountConstructor_whenCalled_correctLoginAssigment) {
			std::string testLogin{ "testLogin" };
			Assert::AreEqual(testLogin, testAccount.getLogin());
		}
	};

	TEST_CLASS(accountManagementUnitTests) {
	private:
		TEST_CLASS_INITIALIZE(managerAuthorizedAccountListInitialization) {
			manager.addAccount("rand1");
			manager.addAccount("rand2");
			manager.addAccount("rand3");
			manager.addAccount("rand4");
		}

	public:
		TEST_METHOD(isLoginUnique_whileCalledWithUniqeLogin_resultIsTrue) {
			Assert::IsTrue(manager.isLoginUnique("rand5"));
		}
		TEST_METHOD(isLoginUnique_whileCalledWithNotUniqueLogin_resultIsFalse){
			Assert::IsFalse(manager.isLoginUnique("rand4"));
		}
		TEST_METHOD(getAccoutn_whileCalledWithExistedLogin_resultIsNotNullptr){
			Assert::IsNotNull(manager.tryToGetAccoutn("rand4"));
		}
		TEST_METHOD(getAccoutn_whileCalledWithNotExistedLogin_resultIsNullptr) {
			Assert::IsNull(manager.tryToGetAccoutn("rand5"));
		}
	};

	//Currently not enough experience in unit tests to test this part
	TEST_CLASS(testHandlerUnitTests) {
	private:
	public:
	};

}