#include "pch.h"
#include "CppUnitTest.h"
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

		TEST_CLASS_INITIALIZE(variablesInitialization) {
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
	};

	TEST_CLASS(settingsMementoUnitTests) {
private:
	TEST_CLASS_INITIALIZE(variablesInitialization) {
		pToSettings = settings::getInstance();
		auxiliaryString = "testProfile";
	}

	TEST_METHOD_CLEANUP(variablesCleanup) {
		result = false;
	}

	settingsMemento memento{ pToSettings };
		bool result{false};

	public:
		TEST_METHOD(getMemento_whenCall_snapshotOfSettingsValuesIsAddToList){
			result = memento.getMemento(auxiliaryString);
			Assert::IsTrue(result);
		}
	};
}
