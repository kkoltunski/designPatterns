#include "pch.h"
#include "CppUnitTest.h"
#include <functional>
#include "..\memento.Library\settings.h"
#include "..\memento.Library\settingsMemento.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mementoUnitTests
{
	std::shared_ptr<settings> pToSettings{ nullptr };
	settingsStruct* pToAuxiliaryStruct{ nullptr };
	std::string auxiliaryString{""};

	TEST_CLASS(settingsUnitTests){
	private:
		TEST_CLASS_INITIALIZE(TestClassTearUp) {
			pToSettings = settings::getInstance();
			pToAuxiliaryStruct = new settingsStruct;
			auxiliaryString = "testProfile";
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


		TEST_CLASS_INITIALIZE(testClassTearsUp) {
			pToSettings = settings::getInstance();
			pToAuxiliaryStruct = new settingsStruct;
			pToAuxiliaryStruct->profileName = "testProfile";
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
			settingsStruct snapshot{};

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
	};
}
