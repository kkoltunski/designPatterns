#include "pch.h"
#include "CppUnitTest.h"

#include "timer.h"
#include "mousePress.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace mediatorUnitTests
{
	bool startAfterConstructionFlagFalse{ false }, startAfterConstructionFlagTrue{ true };
	char exampleCharToMonitor1{};
	size_t exampleTimeInterval{};

	TEST_CLASS(timerUnitTests)	{
	public:
		TEST_CLASS_INITIALIZE(classTearsUp) {
			exampleTimeInterval = 2000;
		}
		TEST_METHOD(isActive_afterInstanceConstruction_resultDependOnStartAfterConstructionFlag){
			timer testTimer1(exampleTimeInterval);
			timer testTimer2(exampleTimeInterval);
			
			testTimer1.activate();
			bool result = testTimer1.isActivated();
			testTimer1.deactivate();

			Assert::IsTrue(result);
			Assert::IsFalse(testTimer2.isActivated());
		}

		TEST_METHOD(deactivate_whenCalledWhileTimerIsRunning_isActivatedResultIsFalse) {
			timer testTimer(exampleTimeInterval);

			testTimer.activate();
			testTimer.deactivate();
			
			Assert::IsFalse(testTimer.isActivated());
		}
	};

	TEST_CLASS(keyboardButtonMonitoringUnitTests)	{
	public:
		TEST_CLASS_INITIALIZE(classTearsUp) {
			exampleCharToMonitor1 = 't';
		}

		TEST_METHOD(isActive_aafterInstanceConstruction_resultDependOnActivatetAfterConstructionFlag) {
			mousePress testEvent1;
			mousePress testEvent2;
			
			testEvent1.activate();
			bool result = testEvent1.isActivated();
			testEvent1.deactivate();

			Assert::IsTrue(result);
			Assert::IsFalse(testEvent2.isActivated());
		}

		TEST_METHOD(deactivate_whenCalledWhileMonitoringIsActive_isActivatedResultIsFalse) {
			mousePress testEvent;

			testEvent.activate();
			testEvent.deactivate();
			
			Assert::IsFalse(testEvent.isActivated());
		}
	};
}
