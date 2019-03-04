#include <event.hpp>
#include <trace.hpp>

namespace MetaSim {
    using namespace std;

    const char * const Trace::Exc::_NO_OPEN = "File is not open";

    Trace::Trace(const char *filename, Type type, bool tof) 
        :_filename(filename), toFile(tof)
    {
        if (tof == false) return;
        if (type == _ASCII_TRACE) 
            _os.open(_filename.c_str(), ios::out);
        else
            _os.open(_filename.c_str(), ios::binary | ios::out);
    } 

    Trace::Trace(const string &filename, Type type, bool tof)
        : _filename(filename)
    {
        if (tof == false) return;
        if (type == _ASCII_TRACE) 
            _os.open(_filename.c_str(), ios::out);
        else
            _os.open(_filename.c_str(), ios::binary | ios::out);
    }

    Trace::~Trace() 
    {
        if (_os.is_open()) close();
    }

    void Trace::open(bool type)
    {
        _os.close();
        if (type == _ASCII_TRACE) 
            _os.open(_filename.c_str(), ios::out);
        else
            _os.open(_filename.c_str(), ios::binary | ios::out);
        if (_os.bad()) throw Exc();
    }

    void Trace::close()
    {
        _os.close();
    }

} // namespace MetaSim  
