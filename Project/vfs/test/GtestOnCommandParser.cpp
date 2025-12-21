#include <gtest/gtest.h>
#include "mockIFileSystem.h"
#include "Command.h"
#include "File.h"
#include "Directory.h"
#include "FileSystem.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class GivenCommandParser : public ::testing::Test
{

protected:
    MockIFileSystem *filesystem;
    std::shared_ptr<IFileSystemComponent> rootDirectory;

    void SetUp() override
    {
        filesystem = new MockIFileSystem();
        rootDirectory = std::make_shared<Directory>("root", component::componenttype::DIRECTORY, nullptr);
    }
    void TearDown() override
    {
        delete filesystem;
    }
};

TEST_F(GivenCommandParser, whenUserEnterTwoManyArgumentsForLsCommand)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).WillOnce(Return(rootDirectory));
    Command command(*filesystem);

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls cmd"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Two many arguments!\n");
}

TEST_F(GivenCommandParser, whenUserEnterLsCommandToDisplayEntriesForOneDirectory)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(3).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("mkdir ./cpp"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\x1B[34mcpp \x1B[0m\n");
}

TEST_F(GivenCommandParser, whenUserEnterLsCommandToDisplayEntriesForTwoDirectory)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(3).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("mkdir ./cpp cpp2"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\x1B[34mcpp \x1B[0m\x1B[34mcpp2 \x1B[0m\n");
}

TEST_F(GivenCommandParser, whenUserEnterLsCommandToDisplayEntriesForOneDirectoryOneFile)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(4).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("mkdir ./cpp"));
    command.parseCommand(std::string("touch 1.txt"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\x1B[34mcpp \x1B[0m\x1B[92m1.txt \x1B[0m\n");
}

TEST_F(GivenCommandParser, whenUserEnterLsCommandToDisplayEntriesForOneFile)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(3).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("touch 1.txt"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\x1B[92m1.txt \x1B[0m\n");
}

TEST_F(GivenCommandParser, whenUserEnterTouchForMultipleFileEntries)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(3).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("touch 1.txt 2.txt 3.txt"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\x1B[92m1.txt \x1B[0m\x1B[92m2.txt \x1B[0m\x1B[92m3.txt \x1B[0m\n");
}

TEST_F(GivenCommandParser, whenUserEnterTouchForMultipleDirectoryEntries)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(3).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("mkdir cpp cpp1 cpp2"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "\x1B[34mcpp \x1B[0m\x1B[34mcpp1 \x1B[0m\x1B[34mcpp2 \x1B[0m\n");
}

TEST_F(GivenCommandParser, whenUserEnterPwdCommandInOtherDirectory)
{
    absolutePath path;
    path.absoultePathOfCureentDirectory = "/cpp";

    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(3).WillRepeatedly((Return(rootDirectory)));
    EXPECT_CALL(*filesystem, getAbsolutePathOfCurrentDirectory()).Times(1).WillOnce(Return(path));
    EXPECT_CALL(*filesystem, setCurrentDirectory(_)).Times(1).WillRepeatedly(Return(true));
    Command command(*filesystem);

    command.parseCommand(std::string("mkdir cpp"));
    command.parseCommand(std::string("cd cpp"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("pwd"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "/cpp\n");
}

TEST_F(GivenCommandParser, whenUserEnterPwdCommandInCurrentDirectory)
{
    absolutePath path;
    path.absoultePathOfCureentDirectory = "/";

    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(1).WillRepeatedly((Return(rootDirectory)));
    EXPECT_CALL(*filesystem, getAbsolutePathOfCurrentDirectory()).Times(1).WillOnce(Return(path));
    Command command(*filesystem);

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("pwd"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "/\n");
}

TEST_F(GivenCommandParser, whenUserEnterPwdCommandToCheckCurrentPathAfterChangingPathByonce)
{
    absolutePath path;
    path.absoultePathOfCureentDirectory = "/cpp";

    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(3).WillRepeatedly((Return(rootDirectory)));
    EXPECT_CALL(*filesystem, getAbsolutePathOfCurrentDirectory()).Times(1).WillOnce(Return(path));
    EXPECT_CALL(*filesystem, setCurrentDirectory(_)).Times(1).WillRepeatedly(Return(true));
    Command command(*filesystem);

    command.parseCommand(std::string("mkdir cpp"));
    command.parseCommand(std::string("cd cpp"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("pwd"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "/cpp\n");
}

TEST_F(GivenCommandParser, whenUserEnterPwdCommandToCheckCurrentPathAfterChangingPathByTwice)
{
    absolutePath path;
    path.absoultePathOfCureentDirectory = "/cpp/cpp1";

    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(5).WillRepeatedly((Return(rootDirectory)));
    EXPECT_CALL(*filesystem, getAbsolutePathOfCurrentDirectory()).Times(1).WillOnce(Return(path));
    EXPECT_CALL(*filesystem, setCurrentDirectory(_)).Times(2).WillRepeatedly(Return(true));
    Command command(*filesystem);

    command.parseCommand(std::string("mkdir cpp"));
    command.parseCommand(std::string("cd cpp"));
    command.parseCommand(std::string("mkdir cpp1"));
    command.parseCommand(std::string("cd cpp1"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("pwd"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "/cpp/cpp1\n");
}

TEST_F(GivenCommandParser, whenUserEnterPwdCommandToCheckCurrentPathAfterChangingPathByThrice)
{
    absolutePath path;
    path.absoultePathOfCureentDirectory = "/cpp/cpp1/cpp2";

    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(7).WillRepeatedly((Return(rootDirectory)));
    EXPECT_CALL(*filesystem, getAbsolutePathOfCurrentDirectory()).Times(1).WillOnce(Return(path));
    EXPECT_CALL(*filesystem, setCurrentDirectory(_)).Times(3).WillRepeatedly(Return(true));
    Command command(*filesystem);

    command.parseCommand(std::string("mkdir cpp"));
    command.parseCommand(std::string("cd cpp"));
    command.parseCommand(std::string("mkdir cpp1"));
    command.parseCommand(std::string("cd cpp1"));
    command.parseCommand(std::string("mkdir cpp2"));
    command.parseCommand(std::string("cd cpp2"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("pwd"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "/cpp/cpp1/cpp2\n");
}

TEST_F(GivenCommandParser, whenUserEnterPwdCommandToCheckCurrentPathAfterChangingPathByFourTimes)
{
    absolutePath path;
    path.absoultePathOfCureentDirectory = "/cpp/cpp1/cpp2/cpp3";

    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(9).WillRepeatedly((Return(rootDirectory)));
    EXPECT_CALL(*filesystem, getAbsolutePathOfCurrentDirectory()).Times(1).WillOnce(Return(path));
    EXPECT_CALL(*filesystem, setCurrentDirectory(_)).Times(4).WillRepeatedly(Return(true));
    Command command(*filesystem);

    command.parseCommand(std::string("mkdir cpp"));
    command.parseCommand(std::string("cd cpp"));
    command.parseCommand(std::string("mkdir cpp1"));
    command.parseCommand(std::string("cd cpp1"));
    command.parseCommand(std::string("mkdir cpp2"));
    command.parseCommand(std::string("cd cpp2"));
    command.parseCommand(std::string("mkdir cpp3"));
    command.parseCommand(std::string("cd cpp3"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("pwd"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "/cpp/cpp1/cpp2/cpp3\n");
}

TEST_F(GivenCommandParser, whenUserPerformCatOperation)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(4).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("touch 1.txt"));
    command.parseCommand(std::string("echo \"hello world!\" > 1.txt"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("cat 1.txt"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "hello world!\n");
}

TEST_F(GivenCommandParser, whenUserPerformCatOperationNonExistingFile)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(4).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("touch 1.txt"));
    command.parseCommand(std::string("echo \"hello world!\" > 1.txt"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("cat 2.txt"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "File is not found!\n");
}

TEST_F(GivenCommandParser, whenUserPerformCatOperationWithNotSepecifyingFileName)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(4).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("touch 1.txt"));
    command.parseCommand(std::string("echo \"hello world!\" > 1.txt"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("cat"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "InSufficient command!\n");
}

TEST_F(GivenCommandParser, whenUserEntersFindCommandToSearchFileOfExistingFile)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(3).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("touch 1.txt"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("find ./ -name 1.txt"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "/1.txt\n");
}

TEST_F(GivenCommandParser, whenUserEntersFindCommandToSearchFileOfNonExistingFile)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(3).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("touch 1.txt"));

    testing::internal::CaptureStdout();
    command.parseCommand(std::string("find ./ -name 2.txt"));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "2.txt is not found\n");
}

TEST_F(GivenCommandParser, whenUserEntersRmCommandToRemoveFile)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(5).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("touch 1.txt 2.txt"));
    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls"));
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\x1B[92m1.txt \x1B[0m\x1B[92m2.txt \x1B[0m\n");

    command.parseCommand(std::string("rm 1.txt"));
    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls"));
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\x1B[92m2.txt \x1B[0m\n");
}

TEST_F(GivenCommandParser, whenUserEntersRmFlagDToremoveEmptyDirectory)
{
    EXPECT_CALL(*filesystem, getCurrentDirectory()).Times(5).WillRepeatedly((Return(rootDirectory)));
    Command command(*filesystem);

    command.parseCommand(std::string("mkdir cpp cpp1"));
    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls"));
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\x1B[34mcpp \x1B[0m\x1B[34mcpp1 \x1B[0m\n");

    command.parseCommand(std::string("rm -d cpp"));
    testing::internal::CaptureStdout();
    command.parseCommand(std::string("ls"));
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\x1B[34mcpp1 \x1B[0m\n");
}
