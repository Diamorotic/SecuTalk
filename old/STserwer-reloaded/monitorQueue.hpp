#include <queue>
#include <boost\thread\mutex.hpp>
#include <boost\thread\condition.hpp>

using namespace std;
template <typename DataT>
class MonitorQueue : boost::noncopyable
{
public:
    void push(const DataT& newData)
    {
        boost::mutex::scoped_lock lock(m_monitorMutex);
        m_queue.push(newData);
        m_itemAvailable.notify_one();
    }

    DataT popWait()
    {
        boost::mutex::scoped_lock lock(m_monitorMutex);

        if(m_queue.empty())
        {
            m_itemAvailable.wait(lock);
        }

        DataT temp(m_queue.front());
        m_queue.pop();
        return temp;
    }

    bool empty()
    {
        boost::mutex::scoped_lock lock(m_monitorMutex);
        return m_queue.empty();
        m_itemAvailable.notify_one();
    }
private:
    std::queue<DataT> m_queue;
    boost::mutex m_monitorMutex;
    boost::condition m_itemAvailable;
};
