#include "filestructure/logger/logging.hpp"
#include "filestructure/logger/stringprintf.hpp"


class SystemTestingEnvironment : public testing::Environment
{
    public:



        void initial_logging(std::string filename_prefix) {

            InitializeLogger(StringPrintf("%s.INFO", filename_prefix.c_str()),
                    StringPrintf("%s.WARN", filename_prefix.c_str()),
                    StringPrintf("%s.ERROR", filename_prefix.c_str()));
        }


        explicit SystemTestingEnvironment(int argc,char **argv) {
#ifdef _WIN32
            initial_logging("E:\\workspacecpp\\filestructure\\log");
#elif __linux__
            initial_logging("//home//chatsiri//workspacecpp//pthread_sync_ocl//log");
#endif
            LOG(INFO)<<"Init System logger start : SystemTestingEnvironment";
        }
};


