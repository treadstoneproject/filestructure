#include "filestructure/logger/logging.h"
#include "filestructure/logger/stringprintf.h"


class SystemTestingEnvironment : public testing::Environment
{
    public:



        void initial_logging(std::string filename_prefix) {

            InitializeLogger(StringPrintf("%s.INFO", filename_prefix.c_str()),
                    StringPrintf("%s.WARN", filename_prefix.c_str()),
                    StringPrintf("%s.ERROR", filename_prefix.c_str()));
        }


        explicit SystemTestingEnvironment(int argc,char **argv) {
				  	 initial_logging("/home/chatsiri/workspacecpp/pthread_sync_ocl/log");
					 	//Support Win32:initial_logging("E:\\workspacecpp\\filestructure\\log");

            LOG(INFO)<<"Init System logger start : SystemTestingEnvironment";
        }
};


