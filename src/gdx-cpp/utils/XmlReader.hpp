
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

#ifndef GDX_CPP_UTILS_XMLREADER_HPP_
#define GDX_CPP_UTILS_XMLREADER_HPP_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "gdx-cpp/files/FileHandle.hpp"
#include "gdx-cpp/internal/memory"
#include <unordered_map>

namespace gdx {

class FileHandle;

class XmlReader {
       
public:

    /** Hurray for copy eliding!
     * HURRAY!
     * HURRAY!
     * HURRAY!
     */
    class Element {
    public:        
        typedef ref_ptr_maker<Element>::shared_ptr_t ptr;
        typedef std::vector<Element::ptr> ElementVector;
        typedef std::unordered_map<std::string, std::string> AttributesMap;
        
        bool operator==(const Element& other) {
            return other.name == this->name;
        }

        bool operator!=(const Element& other) {
            return !(*this == other);
        }

        Element() {
        }

        virtual ~Element() {}
        
        Element (const std::string& name) ;
        std::string getName () ;
        std::string getAttribute (const std::string& name) ;
        std::string getAttribute (const std::string& name, const std::string& defaultValue) ;
        void setAttribute (const std::string& name, const std::string& value) ;
        int getChildCount () ;
        Element::ptr const getChild (int i) ;
        void addChild (const XmlReader::Element::ptr& element) ;
        const std::string& getText () ;
        void setText (const std::string& text) ;
        std::string toString () const;
        std::string toString (const std::string& indent) const ;
        Element::ptr const getChildByName (const std::string& name);
        Element::ptr const getChildByNameRecursive (const std::string& name);
        std::vector<Element::ptr> getChildrenByName (const std::string& name);
        float getFloatAttribute (const std::string& name);
        float getFloatAttribute (const std::string& name, float defaultValue);
        int getIntAttribute (const std::string& name) ;
        int getIntAttribute (const std::string& name, int defaultValue) ;
        bool getBooleanAttribute (const std::string& name) ;
        bool getBooleanAttribute (const std::string& name, bool defaultValue) ;
        std::string get (const std::string& name) ;
        std::string get (const std::string& name, const std::string& defaultValue) ;
        int getInt (const std::string& name) ;
        int getInt (const std::string& name, int defaultValue) ;
        float getFloat (const std::string& name) ;
        float getFloat (const std::string& name, float defaultValue) ;
        bool getBolean (const std::string& name) ;
        bool getBoolean (const std::string& name, bool defaultValue) ;

        ///returns the amount of atributes on the current node element
        int getAttributeCount() const;

        AttributesMap::const_iterator getAttributesBegin();
        AttributesMap::const_iterator getAttributesEnd();
        
        bool hasAttribute(const std::string& attributeName);

    private:
        std::string name;
        AttributesMap attributes;
        ElementVector children;
        std::string text;
    };

    XmlReader();
    
    Element::ptr parse (const std::string& xml);
    Element::ptr parse (std::ifstream& reader);
    Element::ptr parse (FileHandle& file);
    Element::ptr parse (const char* data, int offset, int length);

protected:
    void open (const std::string& name);
    void attribute (std::string name, std::string value);
    std::string entity (const std::string& name);
    void text (std::string text);
    void close ();

private:
    static const char _xml_actions[26];
    static const char _xml_key_offsets[36];
    static const char _xml_trans_keys[116];
    static const char _xml_single_lengths[36];
    static const char _xml_range_lengths[36];
    static const short _xml_index_offsets[36];
    static const char _xml_indicies[129];
    static const char _xml_trans_targs[63];
    static const char _xml_trans_actions[63];

    static const int xml_start;
    static const int xml_first_final;
    static const int xml_error;
    
    static const int xml_en_elementBody;
    static const int xml_en_main;

    Element::ptr root;
    Element::ptr current;
    std::string name;
    std::stringstream textBuffer;
    Element::ElementVector elements;
};

} // namespace gdx

#endif // GDX_CPP_UTILS_XMLREADER_HPP_
