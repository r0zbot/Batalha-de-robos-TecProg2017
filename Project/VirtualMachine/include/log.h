#ifndef VIRTUALMACHINE_LOG_H
#define VIRTUALMACHINE_LOG_H

#include <string>

using namespace std;

/**
 * The <b>Log</b> class takes control over the internal logging events.
 * These events fall into one of four priority categories:
 * <ul>
 * <li><b>DEBUG</b> = Use the <b>DEBUG</b> level priority for log messages that convey extra information regarding
 *                    life-cycle events. Developer or in depth information required for support is the basis
 *                    for this priority.
 *
 * <li><b>ERROR</b> = Use the <b>ERROR</b> level priority for events that indicate a critical service failure.
 *                    If a service issues a <b>ERROR</b> it is completely unable to service requests of any kind.
 *
 * <li><b>INFO</b>  = Use the <b>INFO</b> level priority for service life-cycle events and other crucial related
 *                    information. Looking at the <b>INFO</b> messages for a given service category should tell
 *                    you exactly what state the service is in.
 *
 * <li><b>WARN</b>  = Use the <b>WARN</b> level priority for events that may indicate a non-critical service error.
 *                    Resumable errors, or minor breaches in request expectations fall into this category.
 * </ul>
 */
class Log {

    public:
        /**
         * 	Log a message with debug priority.
         *
         * @param [msg] The string to be write in the log standard output.
         */
        static void debug(const string &msg);

        /**
         * 	Log a message with error priority.
         *
         * @param [msg] The string to be write in the log standard output.
         */
        static void error(const string &msg);

        /**
         * 	Log a message with info priority.
         *
         * @param [msg] The string to be write in the log standard output.
         */
        static void info(const string &msg);

        /**
         * 	Log a message with warn priority.
         *
         * @param [msg] The string to be write in the log standard output.
         */
        static void warn(const string &msg);
};

#endif
