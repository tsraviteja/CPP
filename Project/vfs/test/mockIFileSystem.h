#include "IFileSystem.h"
#include <gmock/gmock.h>

class MockIFileSystem : public IFileSystem
{
public:
    MOCK_METHOD(std::shared_ptr<IFileSystemComponent>, getCurrentDirectory, (), (override));
    MOCK_METHOD(bool, setCurrentDirectory, (std::shared_ptr<IFileSystemComponent>), (override));
    MOCK_METHOD(absolutePath, getAbsolutePathOfCurrentDirectory, (), (override));
};
