#include "pch.h"
#include "CppUnitTest.h"
#include "directory.h"
#include "commander.h"
#include "commandInvoker.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace commandUnitTests
{
	LPCSTR testDirectoryPath{ R"(..\command.UnitTests\testDirectory)" };
	LPCSTR testFilePath{R"(..\command.UnitTests\testFile.txt)"};

	TEST_CLASS(fileUnitTests){
	private:
		bool result{ false };
		file testFile{testFilePath};

		TEST_METHOD_INITIALIZE(codeInitialization) {
			testFile.tryToCreate();
		}

		TEST_METHOD_CLEANUP(codeCleanup) {
			testFile.tryToRemove();
			result = false;
		}
	public:
		TEST_METHOD(isFileExisting_whenCalledAfterSuccesfullFileCreation_resultIsTrue) {
			result = testFile.isFileExisting(FILE_ATTRIBUTE_ARCHIVE);

			Assert::IsTrue(result);
		}

		TEST_METHOD(isFileNameEqual_whenCalledWithFileNameTheSameLikeObject_resultIsTrue){
			std::string fileNameToCompare{ "testFile.txt" };

			result = testFile.isFileNameEqual(fileNameToCompare);

			Assert::IsTrue(result);
		}

		TEST_METHOD(isFileNameEqual_whenCalledWithFileNameTheSameLikeObject_resultIsFalse) {
			std::string fileNameToCompare{ "testFile11.txt" };

			result = testFile.isFileNameEqual("testFile11.txt");

			Assert::IsFalse(result);
		}
		TEST_METHOD(tryToRemoveFile_whenCalledForExistingFile_directoryIsRemoved) {
			Assert::IsTrue(testFile.tryToRemove());
		}
	};

	TEST_CLASS(directoryUnitTests) {
	private:
		bool result{ false };
		directory testDirectory{ testDirectoryPath };

		TEST_METHOD_INITIALIZE(codeInitialization) {
			testDirectory.tryToCreate();
		}

		TEST_METHOD_CLEANUP(codeCleanup) {
			testDirectory.tryToRemove();
			result = false;
		}

	public:
		TEST_METHOD(isFileExisting_whenCalledAfterSuccesfullDirectoryCreation_resultIsTrue) {
			result = testDirectory.isFileExisting(FILE_ATTRIBUTE_DIRECTORY);

			Assert::IsTrue(result);
		}

		TEST_METHOD(isFileNameEqual_whenCalledWithFileNameTheSameLikeObject_resultIsTrue) {
			std::string fileNameToCompare{ "testDirectory" };

			result = testDirectory.isFileNameEqual(fileNameToCompare);

			Assert::IsTrue(result);
		}

		TEST_METHOD(isFileNameEqual_whenCalledWithFileNameTheSameLikeObject_resultIsFalse) {
			std::string fileNameToCompare{ "testDirectory11" };

			result = testDirectory.isFileNameEqual(fileNameToCompare);

			Assert::IsFalse(result);
		}
		TEST_METHOD(tryToRemoveFile_whenCalledForEmptyExistingDirectory_directoryIsRemoved){
			Assert::IsTrue(testDirectory.tryToRemove());
		}

		TEST_METHOD(tryToAddFileToDirectory_whenCalledWithUniqeFileName_newFileIsAddedToDirectory){
			iFile* result{ false };
			std::string testFile{"newTestFile"};

			for(int i = 0; i < 4; ++i){
				result = testDirectory.tryToAddFileToDirectory((testFile + std::to_string(i)));

				if(result == nullptr){
					break;
				}
			}

			Assert::IsNotNull(result);
		}

		TEST_METHOD(tryToAddFolderToDirectory_whenCalledWithUniqeFolderName_newFolderIsAddedToDirectory){
			iFile* result{ nullptr };

			result = testDirectory.tryToAddFolderToDirectory("newTestDirectory");

			Assert::IsNotNull(result);
		}

		TEST_METHOD(searchForFile_whenCalledWithFileNameWhichExist_resultIsAddressToThisFile){
			iFile* result{ nullptr };
			std::string testFileName{"testFile"};

			for(std::size_t i = 0; i < 5; ++i){
				testDirectory.tryToAddFileToDirectory(testFileName + std::to_string(i));
			}

			result = testDirectory.searchForFile(testFileName + std::to_string(2));

			Assert::IsNotNull(result);
		}

		TEST_METHOD(searchForFile_whenCalledWithFileNameWhichNotExist_resultIsNullptr) {
			iFile* result{ nullptr };
			std::string testFileName{ "testFile" };

			for (std::size_t i = 0; i < 5; ++i) {
				testDirectory.tryToAddFileToDirectory(testFileName + std::to_string(i));
			}

			result = testDirectory.searchForFile(testFileName + std::to_string(10));

			Assert::IsNull(result);
		}
	};

	TEST_CLASS(commandUnitTests) {
	private:
		bool result{ false };
		directory testDirectory{ testDirectoryPath };
		fileCreator fileCreator{ &testDirectory };
		directoryCreator directoryCreator{ &testDirectory };
		fileRemover fileRemover{ &testDirectory };
		finisher finisher;
		
		TEST_METHOD_INITIALIZE(codeInitialization){
			testDirectory.tryToCreate();
		}

		TEST_METHOD_CLEANUP(codeCleanup){
			testDirectory.tryToRemove();
			result = false;
		}

	public:
		TEST_METHOD(fileCreatorDoCommand_afterCall_newFileIsCreatedInPointedDirectory) {
			std::string newFileName{ "newTestFile" };

			result = fileCreator.doCommand(static_cast<LPCSTR>(newFileName.c_str()));

			Assert::IsTrue(result);
		}

		TEST_METHOD(directoryCreatorDoCommand_afterCall_newDirectoryIsCreatedInPointedDirectory) {
			std::string newDirectoryName{ "newTestDirectory" };

			result = directoryCreator.doCommand(static_cast<LPCSTR>(newDirectoryName.c_str()));

			Assert::IsTrue(result);
		}

		TEST_METHOD(fileRemoverDoCommand_afterCall_existingFileIsRemovedFromPointedDirectory) {
			std::string testFile{ "testFile" };
			std::string nameToFind{ testFile + std::to_string(3) };

			for (std::size_t i = 0; i < 5; ++i) {
				testDirectory.tryToAddFileToDirectory(testFile + std::to_string(i));
			}

			result = fileRemover.doCommand(static_cast<LPCSTR>(nameToFind.c_str()));

			Assert::IsTrue(result);
		}

		TEST_METHOD(fileRemoverDoCommand_afterCall_existingFolderIsRemovedFromPointedDirectory) {
			std::string testFile{ "testFile" };
			std::string nameToFind{ testFile + std::to_string(3) };

			for (std::size_t i = 0; i < 5; ++i) {
				testDirectory.tryToAddFolderToDirectory(testFile + std::to_string(i));
			}

			result = fileRemover.doCommand(static_cast<LPCSTR>(nameToFind.c_str()));

			Assert::IsTrue(result);
		}

		TEST_METHOD(finisherDoCommand_afterCall_currentOperationIsFinished){
			std::string byebyeMessage{"Finish."};
			result = finisher.doCommand(static_cast<LPCSTR>(byebyeMessage.c_str()));
			
			Assert::IsTrue(result);
		}
	};

	TEST_CLASS(invokerUnitTests) {
	private:
		bool result{ false };
		commandInvoker commandInvoker;
		directory testDirectory{ testDirectoryPath };
		fileCreator fileCreator{ &testDirectory };
		directoryCreator directoryCreator{ &testDirectory };
		fileRemover fileRemover{ &testDirectory };
		std::string createdByCommandInvoker{ "createdByCommandInvoker" };

		TEST_METHOD_INITIALIZE(variableInitialization) {
			testDirectory.tryToCreate();

			commandInvoker.addCommand(0, &fileCreator);
			commandInvoker.addCommand(1, &directoryCreator);
			commandInvoker.addCommand(2, &fileRemover);

			testDirectory.tryToAddFileToDirectory("TestFile.txt");
			testDirectory.tryToAddFileToDirectory("TestFile1.txt");
			testDirectory.tryToAddFileToDirectory("TestFile2.txt");
			testDirectory.tryToAddFolderToDirectory("newTestFolder");
		}

		TEST_METHOD_CLEANUP(variableCleanup) {
			testDirectory.tryToRemove();
			result = false;
		}

	public:
		TEST_METHOD(callCommand_whenCalledWithValidIndex_operationResultIsTrue) {
			result = commandInvoker.callCommand(1, createdByCommandInvoker);

			Assert::IsTrue(result);
		}

		TEST_METHOD(callCommand_whenCalledWithInvalidIndex_operationResultIsFalse) {
			result = commandInvoker.callCommand(5, createdByCommandInvoker);

			Assert::IsFalse(result);
		}

		TEST_METHOD(changeDirectory_whenCalled_commandsAreExecutingInNewDirectory){
			iFile* pToDirectory{nullptr};

			commandInvoker.callCommand(1, createdByCommandInvoker);
			pToDirectory = testDirectory.searchForFile(createdByCommandInvoker);

			commandInvoker.reloadDirectory(dynamic_cast<directory*>(pToDirectory));
			commandInvoker.callCommand(1, createdByCommandInvoker);

			result = pToDirectory->isFileExisting(FILE_ATTRIBUTE_DIRECTORY);

			Assert::IsTrue(result);
		}
	};
}
