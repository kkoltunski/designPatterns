#include "pch.h"
#include "CppUnitTest.h"
#include <functional>
#include "..\memento.Library\settings.h"
#include "..\memento.Library\settingsMemento.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mementoUnitTests
{
	std::shared_ptr<settings> pToSettings{ nullptr };
	std::string auxiliaryString{""};

	TEST_CLASS(settingsUnitTests){
	private:
		settingsStruct snapshot;

		TEST_CLASS_INITIALIZE(TestClassTearUp) {
			pToSettings = settings::getInstance();
			auxiliaryString = "testProfile";
		}

	public:
		TEST_METHOD(getInstance_returnAddressIsDifferentThanNullptr){
			Assert::IsFalse(pToSettings == nullptr);
		}

		TEST_METHOD(makeSnapshot_ifCalledWhenInstanceIsAlreadyCreated_snapshotProfilNameIsEqualToGivenName) {
			snapshot = pToSettings->makeSnapshot(auxiliaryString);
			Assert::AreEqual(auxiliaryString, snapshot.profileName);
		}

		TEST_METHOD(setSnapshot_afterCall_newSettingsAreLoaded) {
			settingsMemento memento{ pToSettings.get() };

			pToSettings->makeSnapshot(auxiliaryString + std::to_string(1));
			pToSettings->makeSnapshot(auxiliaryString + std::to_string(2));
			pToSettings->makeSnapshot(auxiliaryString + std::to_string(3));
			pToSettings->makeSnapshot(auxiliaryString + std::to_string(4));
			
			pToSettings->tryToSetSnapshot(auxiliaryString + std::to_string(3));
			snapshot = pToSettings->makeSnapshot();

			Assert::AreEqual((auxiliaryString + std::to_string(3)), snapshot.profileName);
		}
	};

	TEST_CLASS(settingsMementoUnitTests) {
	private:
		std::size_t mementoSizeBefore{}, mementoSizeAfter{};

		TEST_CLASS_INITIALIZE(testClassTearsUp) {
			pToSettings = settings::getInstance();
			auxiliaryString = "testProfile";
		}

		TEST_METHOD_CLEANUP(TestMethodTearsDown) {
			mementoSizeBefore = 0;
			mementoSizeAfter = 0;
		}

	public:
		TEST_METHOD(append_afterCallForUniqueMementoName_differenceBetweenMementoContainerSizesIsExactlyOne){
			settingsMemento memento{ pToSettings.get() };
			
			mementoSizeBefore = memento.size();
			memento.append(pToSettings->makeSnapshot(auxiliaryString));
			mementoSizeAfter = memento.size();

			Assert::AreEqual(static_cast<std::size_t>(1), (mementoSizeAfter - mementoSizeBefore));
		}

		TEST_METHOD(append_afterCallForNotUniqueName_differenceBetweenMementoContainerSizesIsTheSame) {
			settingsMemento memento{ pToSettings.get() };

			memento.append(pToSettings->makeSnapshot(auxiliaryString));
			mementoSizeBefore = memento.size();
			memento.append(pToSettings->makeSnapshot(auxiliaryString));
			mementoSizeAfter = memento.size();

			Assert::AreEqual(static_cast<std::size_t>(0), (mementoSizeAfter - mementoSizeBefore));
		}

		TEST_METHOD(getProfile_whenCalledForNameWhichExistInContainer_returnsSettings) {
			settingsMemento memento{ pToSettings.get() };
			settingsStruct snapshot{};

			memento.append(pToSettings->makeSnapshot(auxiliaryString + std::to_string(1)));
			memento.append(pToSettings->makeSnapshot(auxiliaryString + std::to_string(2)));
			memento.append(pToSettings->makeSnapshot(auxiliaryString + std::to_string(3)));

			snapshot = memento.getProfile(pToSettings.get(), auxiliaryString + std::to_string(2));

			Assert::AreEqual(auxiliaryString + std::to_string(2), snapshot.profileName);
		}

		TEST_METHOD(getProfile_whenCalledForNameWhichNotExistInContainer_throwsException) {
			settingsMemento memento{ pToSettings.get() };
			std::function<void(void)> functionWhichRaisesException = [&]() {memento.getProfile(pToSettings.get(), "NameWhichNotExist"); };
			Assert::ExpectException<std::exception>(functionWhichRaisesException);
		}
	};
}
