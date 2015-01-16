

//#define BOOST_USE_WINDOWS_H
#include <boost\thread\mutex.hpp>
#include <boost\thread\condition.hpp>


class Monitor
{
protected:
    boost::mutex monitor_mutex;
    boost::condition monitor_condition;
    boost::mutex::scoped_lock sync;

public:
    Monitor() { }
    virtual ~Monitor() { }

    void wait()
    {
        monitor_condition.wait(monitor_mutex);
    }

    bool timed_wait_ms(int i_duration_ms)
    {
        boost::xtime::xtime_nsec_t total_ns(i_duration_ms * 1000000);
        boost::xtime::xtime_sec_t seconds(total_ns / 1000000000);
        boost::xtime::xtime_nsec_t remainder_ns(total_ns % 1000000000);

        boost::xtime xt;
        boost::xtime_get(&xt, boost::TIME_UTC_);
        xt.sec += seconds;
        xt.nsec += remainder_ns;
        return monitor_condition.timed_wait(monitor_mutex, xt);
    }

    void notify_one()
    {
        monitor_condition.notify_one();
    }

    void notify_all()
    {
        monitor_condition.notify_one();
    }
    ///typedef boost::mutex::scoped_lock Synchronize;
};

