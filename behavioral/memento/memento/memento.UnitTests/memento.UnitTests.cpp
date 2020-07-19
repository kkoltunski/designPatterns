#include "pch.h"
#include "CppUnitTest.h"
#include <functional>
#include "..\memento.Library\settings.h"
#include "..\memento.Library\settingsMemento.h"
#include "..\memento.Library\userInterface.h"
#include "..\memento.Library\limit.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mementoUnitTests
{
	std::shared_ptr<settings> pToSettings{ nullptr };
	settingsStruct* pToAuxiliaryStruct{ nullptr };
	std::string auxiliaryString{"testProfile"};

	TEST_CLASS(settingsUnitTests){
	private:
		TEST_CLASS_INITIALIZE(TestClassTearUp) {
			pToSettings = settings::getInstance();
			pToAuxiliaryStruct = new settingsStruct;
		}

		TEST_CLASS_CLEANUP(testClassTearsDown) {
			delete pToAuxiliaryStruct;
		}

	public:
		TEST_METHOD(getInstance_returnAddressIsDifferentThanNullptr){
			Assert::IsFalse(pToSettings == nullptr);
		}

		TEST_METHOD(makeSnapshot_ifCalledWhenInstanceIsAlreadyCreated_snapshotProfilNameIsEqualToGivenName) {
			*pToAuxiliaryStruct = pToSettings->makeSnapshot(auxiliaryString);
			Assert::AreEqual(auxiliaryString, pToAuxiliaryStruct->profileName);
		}

		TEST_METHOD(setSnapshot_afterCall_newSettingsAreLoaded) {
			pToSettings->makeSnapshot(auxiliaryString + std::to_string(1));
			pToSettings->makeSnapshot(auxiliaryString + std::to_string(2));
			pToSettings->makeSnapshot(auxiliaryString + std::to_string(3));
			pToSettings->makeSnapshot(auxiliaryString + std::to_string(4));
			
			pToSettings->tryToSetSnapshot(auxiliaryString + std::to_string(3));
			*pToAuxiliaryStruct = pToSettings->makeSnapshot();

			Assert::AreEqual((auxiliaryString + std::to_string(3)), pToAuxiliaryStruct->profileName);
		}
	};

	TEST_CLASS(settingsMementoUnitTests) {
	private:
		std::size_t mementoSizeBefore{}, mementoSizeAfter{};
		settingsStruct snapshot{};

		TEST_CLASS_INITIALIZE(testClassTearsUp) {
			pToSettings = settings::getInstance();
			pToAuxiliaryStruct = new settingsStruct;
		}

		TEST_METHOD_INITIALIZE(testMethodTearsUp) {
			pToAuxiliaryStruct->profileName = auxiliaryString;
		}

		TEST_CLASS_CLEANUP(testClassTearsDown) {
			delete pToAuxiliaryStruct;
		}

		TEST_METHOD_CLEANUP(TestMethodTearsDown) {
			mementoSizeBefore = 0;
			mementoSizeAfter = 0;
		}

	public:
		TEST_METHOD(append_afterCallForUniqueMementoName_settingsProfileIsAddedToContainer){
			settingsMemento memento{ pToSettings.get() };

			mementoSizeBefore = memento.size();
			memento.append(pToSettings.get(), *pToAuxiliaryStruct);
			mementoSizeAfter = memento.size();

			Assert::AreEqual(static_cast<std::size_t>(1), (mementoSizeAfter - mementoSizeBefore));
		}

		TEST_METHOD(append_afterCallForNotUniqueName_settingsProfileIsNotAddedToContainer) {
			settingsMemento memento{ pToSettings.get() };

			memento.append(pToSettings.get(), *pToAuxiliaryStruct);
			mementoSizeBefore = memento.size();
			memento.append(pToSettings.get(), *pToAuxiliaryStruct);
			mementoSizeAfter = memento.size();

			Assert::AreEqual(static_cast<std::size_t>(0), (mementoSizeAfter - mementoSizeBefore));
		}

		TEST_METHOD(getProfile_whenCalledForNameWhichExistInContainer_returnsSettings) {
			settingsMemento memento{ pToSettings.get() };

			pToAuxiliaryStruct->profileName += std::to_string(1);
			memento.append(pToSettings.get(), *pToAuxiliaryStruct);
			pToAuxiliaryStruct->profileName += std::to_string(2);
			memento.append(pToSettings.get(), *pToAuxiliaryStruct);
			pToAuxiliaryStruct->profileName += std::to_string(3);
			memento.append(pToSettings.get(), *pToAuxiliaryStruct);

			snapshot = memento.getProfile(pToSettings.get(), pToAuxiliaryStruct->profileName);

			Assert::AreEqual(pToAuxiliaryStruct->profileName, snapshot.profileName);
		}

		TEST_METHOD(getProfile_whenCalledForNameWhichNotExistInContainer_throwsException) {
			settingsMemento memento{ pToSettings.get() };
			std::function<void(void)> functionWhichRaisesException = [&]() {memento.getProfile(pToSettings.get(), "NameWhichNotExist"); };
			Assert::ExpectException<std::exception>(functionWhichRaisesException);
		}

		TEST_METHOD(getProfile_whenCalledWithValidIndex_returnsNameOfProfile) {
			settingsMemento memento{ pToSettings.get() };

			pToAuxiliaryStruct->profileName += std::to_string(1);
			memento.append(pToSettings.get(), *pToAuxiliaryStruct);
			pToAuxiliaryStruct->profileName += std::to_string(2);
			memento.append(pToSettings.get(), *pToAuxiliaryStruct);
			pToAuxiliaryStruct->profileName += std::to_string(3);
			memento.append(pToSettings.get(), *pToAuxiliaryStruct);

			snapshot.profileName = memento.getProfile(1);

			Assert::AreEqual((auxiliaryString + std::to_string(12)), snapshot.profileName);
		}

		TEST_METHOD(getProfile_whenCalledWithInvalidIndex_throwsException) {
			settingsMemento memento{ pToSettings.get() };
			std::function<void(void)> shouldThrowException = [&]() {memento.getProfile(111); };
			Assert::ExpectException<std::exception>(shouldThrowException);
		}
	};

	/*TEST_CLASS(userInterfaceUnitTests) {
	private:
		userInterface UI{ pToSettings.get() };

		TEST_METHOD_INITIALIZE(testClassTearsUp) {
			pToSettings = settings::getInstance();
			auxiliaryString = "uniqeName";
		}

	public:
		TEST_METHOD(showOptions_whenCalled_coutRdbufContentProfileName) {
			std::string expectedResult = " uniqeName1\n uniqueName2\n uniqueName3\n";
			std::ostringstream localStream{};

			auto coutRdbuf = std::cout.rdbuf();
			std::cout.rdbuf(localStream.rdbuf());

			pToSettings->makeSnapshot(auxiliaryString + std::to_string(1));
			pToSettings->makeSnapshot(auxiliaryString + std::to_string(2));
			pToSettings->makeSnapshot(auxiliaryString + std::to_string(3));
			UI.showOptions();

			//get string position
			std::size_t totalSize = localStream.str().size();
			std::size_t begining = (totalSize - expectedResult.size());

			std::cout.rdbuf(coutRdbuf);
			Assert::AreEqual(expectedResult, localStream.str().substr(begining, std::string::npos));
		}
	};*/

	TEST_CLASS(limitUnitTests) {
	private:
		limit<signed int> testLimit{ 0, 10 };
		bool result{false};

		TEST_METHOD_INITIALIZE(tearsUp) {
			result = false;
		}

	public:
		TEST_METHOD(compareTo_afterCallForValueInLimitRange_returnTrue) {
			result = testLimit.checkIfFit(8);
			Assert::IsTrue(result);
		}

		TEST_METHOD(compareTo_afterCallForValueOutOfLimitRange_returnFalse) {
			result = testLimit.checkIfFit(17);
			Assert::IsFalse(result);
		}

		TEST_METHOD(adjustIfDoesntMatch_afterCallForVariableWhichIsInRange_returnFalseAndVariableValueIsTheSame) {
			signed int testVariable{ 5 };
			result = testLimit.adjustIfDoesnttMatch(testVariable);

			Assert::IsFalse(result);
		}

		TEST_METHOD(adjustIfDoesntMatch_afterCallForVariableWhichIsInRange_returnTrueAndVariableValueIsChanged) {
			signed int testVariable{ 15 };
			auto variableMemory = testVariable;

			result = testLimit.adjustIfDoesnttMatch(testVariable);

			Assert::IsTrue(result);
			Assert::AreNotEqual(variableMemory, testVariable);
		}
	};
}
