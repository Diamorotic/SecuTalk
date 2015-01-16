#include <list>

template <typename DataT>
class MonitorList : boost::noncopyable
{
public:
    bool push(const DataT& newData)
    {
        boost::mutex::scoped_lock lock(m_monitorMutex);
        //find duplicate
        typename list<DataT>::iterator temp=m_list.begin();
        while(temp!=m_list.end())
        {
            if(static_cast<User*>(*temp)!=NULL)
            {
                if(((User*)(*temp))->numer==((User*)newData)->numer)
                    return false;
            }

            temp++;
        }
        m_list.push_back(newData);
        m_itemAvailable.notify_one();
        return true;
    }

    DataT popWait()
    {
        boost::mutex::scoped_lock lock(m_monitorMutex);

        if(m_list.empty())
        {
            m_itemAvailable.wait(lock);
        }

        DataT temp(m_list.front());
        m_list.pop_front();
        return temp;
    }

    typename list<DataT>::iterator begin()
    {
        boost::mutex::scoped_lock lock(m_monitorMutex);
        typename list<DataT>::iterator temp=m_list.begin();
        m_itemAvailable.notify_one();
        return temp;
    }
    typename list<DataT>::iterator end()
    {
        boost::mutex::scoped_lock lock(m_monitorMutex);
        typename list<DataT>::iterator temp=m_list.end();
        m_itemAvailable.notify_one();
        return temp;
    }
private:
    std::list<DataT> m_list;

    boost::mutex m_monitorMutex;
    boost::condition m_itemAvailable;
};

