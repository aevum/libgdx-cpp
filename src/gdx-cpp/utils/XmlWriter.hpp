
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#ifndef GDX_CPP_UTILS_XMLWRITER_HPP_
#define GDX_CPP_UTILS_XMLWRITER_HPP_

#include <string>
#include <fstream>
#include <list>

#include "XmlReader.hpp"

namespace gdx {

class XmlWriter {
public:
    XmlWriter(std::ofstream& writer);
    
    XmlWriter& element (const std::string& name);
    XmlWriter& element (const std::string& name, const XmlReader::Element* text);
    XmlWriter& attribute (const std::string& name, const XmlReader::Element* value);
    XmlWriter& text (const XmlReader::Element* text);
    XmlWriter& pop ();
    void close ();
    void write (const char* cbuf, int off, int len);
    void flush ();

    int indent;

private:
    void _indent ();
    bool startElementContent ();
    std::ofstream& writer;

    std::list<std::string> stack;
    std::string currentElement;
    bool indentNextClose;
};

} // namespace gdx

#endif // GDX_CPP_UTILS_XMLWRITER_HPP_
