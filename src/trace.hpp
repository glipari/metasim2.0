#ifndef __TRACE_HPP__
#define __TRACE_HPP__

#include <fstream>
#include <iostream>

#include <baseexc.hpp>

namespace MetaSim {
    class Event;

#define _BIN_TRACE 0
#define _ASCII_TRACE 1

    /**
       \ingroup metasim_stat

       This is just the basic interface for the tracing classes. By
       default, it opens a binary stream. 
    */
    class Trace { 
    protected:
        std::string _filename;
        std::ofstream _os;
        bool toFile;
    public:
        enum Type {BINARY = 0,
                   ASCII = 1};

        /**
           \ingroup metasim_exc
       
           Exceptions for the Trace classes.
        */
        class Exc : public BaseExc {
        public:
            static const char * const _NO_OPEN;
            Exc(const std::string msg = _NO_OPEN,
                const std::string c = "Trace", 
                const std::string mod = "trace.hpp") : BaseExc(msg, c, mod) {} ;
        };
  
        /**
           Constructor for the trace class. It opens a stream of name
           "filename" of type. Type can be binary or ascii (only for DOS
           based systems!).
        */
        Trace(const char *filename, Type type = BINARY, bool tof = true);

        Trace(const std::string &filename, Type type = BINARY, bool tof = true);

        /// Opens the file 
        void open(bool type = BINARY);

        /// Closes the file
        void close();

        /// Destructor
        virtual ~Trace();
    };


    /**
       \ingroup metasim_stat

       This is an ASCII stream used to monitor some internal variables.
    */
    class TraceAscii : public Trace {
    public:
        TraceAscii(const std::string &file) : Trace(file, ASCII){}

        /// Records the value on the file, one value per line.
        //@{
        void record(double value) { _os << value << std::endl; }
        void record(long double value){_os << value << std::endl;}
        void record(int value){_os << value << std::endl;}
        void record(const std::string &str){_os << str;}
        //@}
    };    

} // namespace MetaSim

#endif
